#include "sprites.h"
#include "text.h"
#include "vcsLib.h"
#include <stdbool.h>

#define ColuBkScore 0x00
#define ColuBkCeiling 0x0f
#define ColuBkWall 0x64
#define ColuBkSheet 0xda
#define ColuFlyWing 0x0e
#define ColuFlyBody 0x02

__attribute__((section(".noinit")))
static uint8_t playfieldBuffer[192*5]; // 00001111 11112222 22220000 11111111 22222222
__attribute__((section(".noinit")))
static uint8_t colupfBuffer[192];
__attribute__((section(".noinit")))
static uint8_t grp0Buffer[192];
__attribute__((section(".noinit")))
static uint8_t grp1Buffer[192];
__attribute__((section(".noinit")))
static uint8_t colup1Buffer[192];

static char scoreText[18] = { 0, 1, 2, 3, 10, 12, 12, 12, 10, 10, 12, 12, 12, 10, 6, 7, 8, 9 };
#define vcsWrite6(a,d) vcsLda2(d); vcsSta4(a);
void setPF(int x, int y);
void DrawFlyRegion(int* line, int height, int fly_x, int fly_y, int fly_frame);

int elf_main(uint32_t* args)
{
	int p0x = 0;
	int fly_top_x = 20;
	int fly_bot_x = 40;
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
	//// Draw a diagnol line for testing
	//uint8_t pf = 0x80;
	//int k = 0;
	//for (int i = 0; i < 40; i++)
	//{
	//	for (int j = 0; j < 4; j++)
	//	{
	//		playfieldBuffer[i * 20 + j * 5 + k] = pf;
	//	}
	//	pf >>= 1;
	//	if (!pf) {
	//		pf = 0x80;
	//		k++;
	//	}
	//}
	// Draw place holders for wobble
	for (int i = 1; i < 3; i++)
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
	// Init PF colors
	for (int i = 0; i < 64; i++)
	{
		colupfBuffer[i] = 0x00;
	}
	for (int i = 64; i < sizeof(colupfBuffer) / sizeof(colupfBuffer[0]); i++)
	{
		colupfBuffer[i] = i;
	}

	// Render loop
	while (true) {

		PrintScore(scoreText);

		p0x++;
		if (p0x > 159)
			p0x = 0;

		fly_top_x -= 1;
		if (fly_top_x < 0)
			fly_top_x = 159;

		fly_bot_x++;
		if (fly_bot_x > 159)
			fly_bot_x = 0;


		// Fan blade test
		if ((frame++ & 3) == 0) {
			fanFrame++;
		}
		if (fanFrame > 6)
		{
			fanFrame = 0;
		}
		for (int y = 0; y < 7; y++)
		{
			playfieldBuffer[(36 + y) * 5 + 1] = FanBladeGraphics[fanFrame][y * 2] >> 7;
			playfieldBuffer[(36 + y) * 5 + 2] = FanBladeGraphics[fanFrame][y * 2] << 1 | FanBladeGraphics[fanFrame][y * 2 + 1] >> 7;
			playfieldBuffer[(36 + y) * 5 + 3] = FanBladeGraphics[fanFrame][y * 2 + 1] << 1;
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

		//Fan Chasis
		for (int i = 0; i < 192; i++)
		{
			grp1Buffer[i] = 0;
		}
		for (int i = 0; i < sizeof(FanChasisGraphics)/sizeof(FanChasisGraphics[0]); i++)
		{
			grp1Buffer[i+19] = FanChasisGraphics[i];
			colup1Buffer[i + 19] = FanChasisColu[i];
		}

		// Banana
		for (int i = 0; i < sizeof(BonusBananaGraphics)/sizeof(BonusBananaGraphics[0]); i++)
		{
			grp1Buffer[i + 50] = BonusBananaGraphics[i];
			colup1Buffer[i + 50] = BonusBananaColu[i];
		}

		vcsEndOverblank();
		vcsSta3(WSYNC); vcsSta3(WSYNC); vcsSta3(WSYNC); vcsSta3(WSYNC); vcsSta3(WSYNC); vcsSta3(WSYNC);
		
		DisplayText();
		
		vcsSta3(WSYNC);
		int line = 19;
		vcsSta3(HMOVE);
		vcsWrite5(COLUPF, ColuBkCeiling); // Disable PF for this line and next
		vcsWrite5(COLUBK, ColuBkCeiling);
		vcsWrite5(COLUP0, 0xe8);
		vcsWrite5(NUSIZ0, 0);
		vcsWrite5(NUSIZ1, 0);
		vcsSta3(HMCLR);
		vcsNop2n(3);
		vcsWrite5(HMP1, 0x20);
		vcsWrite5(RESPONE, 0);
		line++;
		vcsWrite5(COLUP1, colup1Buffer[line]);
		vcsSta3(WSYNC);

		// Position P0
		{
			int x = p0x;
			if (x > 159)
				x -= 160;
			vcsSta3(HMOVE);
			if (x < 11) {
				vcsSta3(RESP0);
				vcsWrite5(GRP1, grp1Buffer[line]);
				vcsWrite5(COLUBK, ColuBkWall);
				vcsNop2n(15);
				vcsSta3(HMCLR);
				vcsWrite5(HMP0, ((x + 3) ^ 0x07) << 4);
			}
			else if (x < 146) {
				vcsWrite5(GRP1, grp1Buffer[line]);
				vcsWrite5(COLUBK, ColuBkWall);
				vcsNop2n(4);
				while (x > 26) {
					vcsWrite5(GRP0, 0x00);
					x -= 15;
				}
				vcsSta3(HMCLR);
				vcsSta3(RESP0);
				vcsWrite5(HMP0, ((x - 11) ^ 0x07) << 4);
			}
			else {
				vcsWrite5(GRP0, 0x00);
				vcsWrite5(COLUBK, ColuBkWall);
				vcsWrite5(GRP1, grp1Buffer[line]);
				vcsNop2n(20);
				vcsJmp3();
				vcsSta3(HMCLR);
				vcsWrite5(HMP0, ((x - 146) ^ 0x07) << 4);
				vcsSta3(RESP0);
			}
			vcsSta3(WSYNC);
			line++;
		}

		// Fan region
		while (line < 48)
		{
			vcsSta3(HMOVE);
			vcsJmp3();
			vcsWrite5(GRP0, grp0Buffer[line]);
			vcsWrite5(GRP1, grp1Buffer[line]);
			vcsWrite5(PF0, ReverseByte[playfieldBuffer[line * 5] >> 4]);
			vcsWrite5(PF1, (playfieldBuffer[line * 5] << 4) | (playfieldBuffer[line * 5 + 1] >> 4));
			vcsWrite5(COLUPF, colupfBuffer[line]);
			vcsWrite5(COLUP1, colup1Buffer[line]);
			vcsWrite5(PF2, ReverseByte[(uint8_t)((playfieldBuffer[line * 5 + 1] << 4) | (playfieldBuffer[line * 5 + 2] >> 4))]);
			vcsWrite5(PF0, ReverseByte[playfieldBuffer[line * 5 + 2]]);
			vcsWrite6(PF1, playfieldBuffer[line * 5 + 3]);
			vcsWrite5(PF2, ReverseByte[playfieldBuffer[line * 5 + 4]]);
			vcsJmp3();
			vcsSta3(HMCLR);
			vcsSta3(WSYNC);
			line++;
		}
		DrawFlyRegion(&line, 12, fly_top_x, fanFrame+3, frame & 1);
		DrawFlyRegion(&line, 12, fly_bot_x, 9- fanFrame, frame & 1);

		// Level 1 - Wide bed
		while (line < 128)
		{
			vcsSta3(HMOVE);
			vcsWrite5(COLUPF, colupfBuffer[line]);
			vcsWrite5(GRP0, grp0Buffer[line]);
			vcsWrite5(PF0, ReverseByte[playfieldBuffer[line * 5] >> 4]);
			vcsWrite5(PF1, (playfieldBuffer[line * 5] << 4) | (playfieldBuffer[line * 5 + 1] >> 4));
			vcsWrite5(COLUBK, ColuBkSheet);
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
		// Level 2 Medium bed
		while (line < 160)
		{
			vcsSta3(HMOVE);
			vcsWrite5(COLUPF, colupfBuffer[line]);
			vcsWrite5(PF0, ReverseByte[playfieldBuffer[line * 5] >> 4]);
			vcsWrite5(PF1, (playfieldBuffer[line * 5] << 4) | (playfieldBuffer[line * 5 + 1] >> 4));
			vcsJmp3();
			vcsLdx2(ColuBkSheet);
			vcsWrite5(COLUBK, 0xe2);
			vcsStx4(COLUBK);
			vcsWrite5(PF2, ReverseByte[(uint8_t)((playfieldBuffer[line * 5 + 1] << 4) | (playfieldBuffer[line * 5 + 2] >> 4))]);
			vcsWrite5(PF0, ReverseByte[playfieldBuffer[line * 5 + 2]]);
			vcsWrite5(PF1, playfieldBuffer[line * 5 + 3]);
			vcsJmp3();
			vcsWrite5(PF2, ReverseByte[playfieldBuffer[line * 5 + 4]]);
			vcsNop2n(3);
			vcsLdx2(ColuBkWall);
			vcsWrite5(COLUBK, 0xe2);
			vcsStx4(COLUBK);
			vcsSta3(WSYNC);
			line++;
		}
		// Level 3 Narrow bed
		while (line < 192)
		{
			vcsSta3(HMOVE);
			vcsWrite5(COLUPF, colupfBuffer[line]);
			vcsWrite5(PF0, ReverseByte[playfieldBuffer[line * 5] >> 4]);
			vcsWrite6(PF1, (playfieldBuffer[line * 5] << 4) | (playfieldBuffer[line * 5 + 1] >> 4));
			vcsWrite6(PF2, ReverseByte[(uint8_t)((playfieldBuffer[line * 5 + 1] << 4) | (playfieldBuffer[line * 5 + 2] >> 4))]);
			vcsLdx2(ColuBkSheet);
			vcsWrite5(COLUBK, 0xe2);
			vcsStx4(COLUBK);
			vcsWrite5(PF0, ReverseByte[playfieldBuffer[line * 5 + 2]]);
			vcsWrite5(PF1, playfieldBuffer[line * 5 + 3]);
			vcsJmp3();
			vcsWrite5(PF2, ReverseByte[playfieldBuffer[line * 5 + 4]]);
			vcsJmp3();
			vcsLdx2(ColuBkWall);
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

// x must be 0-159
void PositionBall(int line, int x)
{
	vcsSta3(HMOVE);
	if (x < 11) {
		vcsSta3(RESBL);
		vcsWrite5(GRP0, grp0Buffer[line]);
		vcsWrite5(GRP1, grp1Buffer[line]);
		vcsNop2n(15);
		vcsSta3(HMCLR);
		vcsWrite5(HMBL, ((x + 3) ^ 0x07) << 4);
	}
	else if (x < 146) {
		vcsWrite5(GRP0, grp0Buffer[line]);
		vcsWrite5(GRP1, grp1Buffer[line]);
		vcsNop2n(4);
		while (x > 26) {
			vcsWrite5(GRP0, grp0Buffer[line]);
			x -= 15;
		}
		vcsSta3(HMCLR);
		vcsSta3(RESBL);
		vcsWrite5(HMBL, ((x - 11) ^ 0x07) << 4);
	}
	else {
		vcsWrite5(GRP0, grp0Buffer[line]);
		vcsWrite5(GRP1, grp1Buffer[line]);
		vcsNop2n(21);
		vcsJmp3();
		vcsJmp3();
		vcsSta3(HMCLR);
		vcsWrite5(HMBL, ((x - 146) ^ 0x07) << 4);
		vcsSta3(RESBL);
	}
	vcsSta3(WSYNC);
}

void DrawFlyRegion(int* line, int height, int fly_x, int fly_y, int fly_frame) {
	PositionBall(*line, fly_x);
	*line+=1;
	for (int i = 1; i < height; i++)
	{
		vcsSta3(HMOVE);
		vcsWrite5(GRP0, grp0Buffer[*line]);
		vcsWrite5(GRP1, grp1Buffer[*line]);
		vcsWrite5(COLUP1, colup1Buffer[*line]);
		if (i < fly_y) {
			vcsWrite5(COLUPF, fly_frame ? ColuFlyBody : ColuFlyWing);
		}
		else if (i == fly_y) {
			vcsWrite5(ENABL, 2);
		}
		else if (i == fly_y + 1) {
			vcsWrite5(COLUPF, ColuFlyBody);
		}
		else {
			vcsWrite5(ENABL, 0);
		}
		if (i == 1) vcsSta3(HMCLR); else vcsJmp3();
		vcsSta3(WSYNC);
		*line += 1;
	}
}