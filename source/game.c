#include "vcsLib.h"
#include <stdbool.h>

__attribute__((section(".noinit")))
static uint8_t playfieldBuffer[192*5]; // 00001111 11112222 22220000 11111111 22222222
__attribute__((section(".noinit")))
static uint8_t colupfBuffer[192];
__attribute__((section(".noinit")))
static uint8_t colubkBuffer[192];

int elf_main(uint32_t* args)
{
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
	for (int i = 0; i < sizeof(colupfBuffer)/ sizeof(colupfBuffer[0]); i++)
	{
		colupfBuffer[i] = i;
		colubkBuffer[i] = (i ^ 0xff) & 0xe0;
	}

	// Render loop
	while (true) {
		vcsEndOverblank();
		vcsSta3(WSYNC); vcsSta3(WSYNC); vcsSta3(WSYNC); vcsSta3(WSYNC); vcsSta3(WSYNC); vcsSta3(WSYNC);
		for (int i = 0; i < 192; i++)
		{
			vcsSta3(WSYNC);
			vcsWrite5(VBLANK, 0);
			vcsWrite5(COLUPF, colupfBuffer[i]);
			vcsWrite5(COLUBK, colubkBuffer[i]);
			vcsWrite5(PF0, ReverseByte[playfieldBuffer[i * 5] >> 4]);
			vcsWrite5(PF1, (playfieldBuffer[i * 5] << 4) | (playfieldBuffer[i * 5 + 1] >> 4));
			vcsWrite5(PF2, ReverseByte[(uint8_t)((playfieldBuffer[i * 5 + 1] << 4) | (playfieldBuffer[i * 5 + 2] >> 4))]);
			vcsWrite5(PF0, ReverseByte[playfieldBuffer[i * 5 + 2]]);
			vcsJmp3();
			vcsWrite5(PF1, playfieldBuffer[i * 5 + 3]);
			vcsJmp3();
			vcsWrite5(PF2, ReverseByte[playfieldBuffer[i * 5 + 4]]);
		}
		vcsSta3(WSYNC);
		vcsWrite5(VBLANK, 2);
		vcsStartOverblank();
	}
}