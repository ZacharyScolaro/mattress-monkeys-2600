#include "sprites.h"
#include "text.h"
#include "vcsLib.h"
#include <stdbool.h>

__attribute__((section(".noinit")))
static uint8_t playfieldBuffer[192*5]; // 00001111 11112222 22220000 11111111 22222222
__attribute__((section(".noinit")))
static uint8_t colupfBuffer[192];
__attribute__((section(".noinit")))
static uint8_t colubkBuffer[192];
__attribute__((section(".noinit")))
static uint8_t grp0Buffer[192];

static char scoreText[18] = { 0, 1, 2, 3, 10, 12, 12, 12, 10, 10, 12, 12, 12, 10, 6, 7, 8, 9 };
#define vcsWrite6(a,d) vcsLda2(d); vcsSta4(a);
void setPF(int x, int y);

int elf_main(uint32_t* args)
{
	int frame = 0;
	int fanFrame = 0;
	// Always reset PC first, cause it's going to be close to the end of the 6507 address space
	vcsJmp3();

	// Init TIA and RIOT RAM
	vcsLda2(0);
	for (int i = 0; i < 256; i++) {
		vcsSta3((unsigned char)i);
	}
	vcsCopyOverblankToRiotRam();

	vcsStartOverblank();

	// Init stuff here while RIOT RAM keeps 6502 busy
	for (int i = 0; i < sizeof(playfieldBuffer)/ sizeof(playfieldBuffer[0]); i++)
	{
		playfieldBuffer[i] = 0;
	}
	// Draw a diagnol line for testing
	uint8_t pf = 0x80;
	int k = 0;
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			playfieldBuffer[i * 20 + j * 5 + k] = pf;
		}
		pf >>= 1;
		if (!pf) {
			pf = 0x80;
			k++;
		}
	}
	// Draw place holders for wobble
	for (int i = 0; i < 3; i++)
	{
		int right = 36 - (i * 3);
		int left = right - 32 + (i * 6);
		for (int j = 0; j < 16; j++)
		{
			for (int k = 0; k <= j; k++)
			{
				setPF(right-k, j + 48 + (i * 64));
				setPF(left+k, j + 48 + (i * 64));
			}
		}
	}
	//Cycle background colors
	for (int i = 0; i < sizeof(colupfBuffer)/ sizeof(colupfBuffer[0]); i++)
	{
		colupfBuffer[i] = i;
		colubkBuffer[i] = (i ^ 0xff) & 0xe0;
	}

	// Render loop
	while (true) {

		PrintScore(scoreText);

		// Fan blade test
		if ((frame++ & 7) == 0) {
			fanFrame++;
		}
		if (fanFrame > 6)
		{
			fanFrame = 0;
		}
		for (int y = 0; y < 7; y++)
		{
			playfieldBuffer[(25 + y) * 5 + 1] = FanBladeGraphics[fanFrame][y * 2] >> 7;
			playfieldBuffer[(25 + y) * 5 + 2] = FanBladeGraphics[fanFrame][y * 2] << 1 | FanBladeGraphics[fanFrame][y * 2 + 1] >> 7;
			playfieldBuffer[(25 + y) * 5 + 3] = FanBladeGraphics[fanFrame][y * 2 + 1] << 1;
		}

		// Monkey Walking Test
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				grp0Buffer[i * 16 + j] = MonkeyWalkingGraphics[(frame >> 3) & 1][j];
			}
		}
		// Monkey Idle Test
		for (int j = 0; j < 12; j++)
		{
			grp0Buffer[2 * 16 + j] = MonkeyIdleGraphics[j];
		}

		vcsEndOverblank();
		vcsSta3(WSYNC); vcsSta3(WSYNC); vcsSta3(WSYNC); vcsSta3(WSYNC); vcsSta3(WSYNC); vcsSta3(WSYNC);
		
		DisplayText();
		
		vcsSta3(WSYNC);
		vcsSta3(HMOVE);
		vcsWrite5(COLUPF, 0x0f);
		vcsWrite5(COLUBK, 0x0f);
		vcsWrite5(COLUP0, 0xe8);
		vcsWrite5(NUSIZ0, 0);
		vcsNop2n(10);
		vcsWrite5(RESP0, 0);
		vcsNop2n(10);
		vcsJmp3();
		vcsWrite5(VBLANK, 0);
		int line = 20;
		while(line < 64)
		{
			vcsSta3(HMOVE);
			vcsWrite5(COLUPF, colupfBuffer[line]);
			vcsWrite5(GRP0, grp0Buffer[line]);
			vcsWrite5(PF0, ReverseByte[playfieldBuffer[line * 5] >> 4]);
			vcsWrite5(PF1, (playfieldBuffer[line * 5] << 4) | (playfieldBuffer[line * 5 + 1] >> 4));
			vcsWrite5(COLUBK, colubkBuffer[line]);
			vcsWrite5(PF2, ReverseByte[(uint8_t)((playfieldBuffer[line * 5 + 1] << 4) | (playfieldBuffer[line * 5 + 2] >> 4))]);
			vcsWrite5(PF0, ReverseByte[playfieldBuffer[line * 5 + 2]]);
			vcsWrite6(PF1, playfieldBuffer[line * 5 + 3]);
			vcsWrite5(PF2, ReverseByte[playfieldBuffer[line * 5 + 4]]);
			vcsJmp3();
			vcsJmp3();
			vcsNop2n(6);
			vcsWrite5(COLUBK, 0xe2);
			vcsSta3(WSYNC);
			line++;
		}
		while (line < 128)
		{
			vcsSta3(HMOVE);
			vcsWrite5(COLUPF, colupfBuffer[line]);
			vcsWrite5(PF0, ReverseByte[playfieldBuffer[line * 5] >> 4]);
			vcsWrite5(PF1, (playfieldBuffer[line * 5] << 4) | (playfieldBuffer[line * 5 + 1] >> 4));
			vcsJmp3();
			vcsLdx2(colubkBuffer[line]);
			vcsWrite5(COLUBK, 0xe2);
			vcsStx4(COLUBK);
			vcsWrite5(PF2, ReverseByte[(uint8_t)((playfieldBuffer[line * 5 + 1] << 4) | (playfieldBuffer[line * 5 + 2] >> 4))]);
			vcsWrite5(PF0, ReverseByte[playfieldBuffer[line * 5 + 2]]);
			vcsWrite5(PF1, playfieldBuffer[line * 5 + 3]);
			vcsJmp3();
			vcsWrite5(PF2, ReverseByte[playfieldBuffer[line * 5 + 4]]);
			vcsNop2n(3);
			vcsLdx2(0x5c);
			vcsWrite5(COLUBK, 0xe2);
			vcsStx4(COLUBK);
			vcsSta3(WSYNC);
			line++;
		}
		while (line < 192)
		{
			vcsSta3(HMOVE);
			vcsWrite5(COLUPF, colupfBuffer[line]);
			vcsWrite5(PF0, ReverseByte[playfieldBuffer[line * 5] >> 4]);
			vcsWrite6(PF1, (playfieldBuffer[line * 5] << 4) | (playfieldBuffer[line * 5 + 1] >> 4));
			vcsWrite6(PF2, ReverseByte[(uint8_t)((playfieldBuffer[line * 5 + 1] << 4) | (playfieldBuffer[line * 5 + 2] >> 4))]);
			vcsLdx2(colubkBuffer[line]);
			vcsWrite5(COLUBK, 0xe2);
			vcsStx4(COLUBK);
			vcsWrite5(PF0, ReverseByte[playfieldBuffer[line * 5 + 2]]);
			vcsWrite5(PF1, playfieldBuffer[line * 5 + 3]);
			vcsJmp3();
			vcsWrite5(PF2, ReverseByte[playfieldBuffer[line * 5 + 4]]);
			vcsJmp3();
			vcsLdx2(0x5c);
			vcsWrite5(COLUBK, 0xe2);
			vcsStx4(COLUBK);
			vcsSta3(WSYNC);
			line++;
		}
		vcsWrite5(VBLANK, 2);
		vcsStartOverblank();
	}
}

void setPF(int x, int y)
{
	int offset = x / 8;
	uint8_t mask = 0x80 >> (x - (offset * 8));
	playfieldBuffer[y * 5 + offset] |= mask;
}

/*

_XXX___XXX___XXX___XXX___XXX___XXX___XXX___XXX
__HH                                       HHH
__  HHH                                 HHH   
__     HHH                           HHH      


*/