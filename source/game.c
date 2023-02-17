#include "sprites.h"
#include "text.h"
#include "vcsLib.h"
#include <stdbool.h>

#define ColuBkScore 0x00
#define ColuCeiling 0x0f
#define ColuWall 0x64
#define ColuSheet 0xda
#define ColuMattress 0xd4
#define ColuFlyWing 0x0e
#define ColuFlyBody 0x02
#define ColuPillow 0x0f
#define ColuHeadboard 0xe6
#define ColuBedPost 0xe2
#define ColuFanBlade 0x02

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
void PositionObject(int line, int x, uint8_t resp, uint8_t hm);

//        x x x
//       x     x
//      x       x  
//       x     x
//        x   x
//          x
//        x   x
//      x       x
//   x             x  
//x                   x  
static const int8_t Fly_Loop_X[] = { 1,1,1, 1,1,1, 1,1, 1,1 ,1,1 ,1,0, 1,0, -1,0, -1,0, -1,0,-1,0,-1,0, -1,0, -1,0, 1,0, 1,0, 1,1, 1,1 ,1,1, 1,1,1, 1,1,1, 1,1,1,1,1 };
static const int8_t Fly_Loop_Y[] = {-1,-1,0,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1,-1, -1,-1,  0,0, 0,0, 0,0,  1,1,  1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1,0, 1,1,0, 0,0,0,0,0 };
static const int8_t Fly_Wave_Y[] = { 0,0,1, 0,0,1, 0,1, 1, 1, 0,1, 0,0,1, 0,0,1, 0,0,0,0,0, 0,0,-1, 0,0,-1, 0,-1, -1, -1, 0,-1, 0,0,-1, 0,0,-1, 0,0,0,0,0 };

int elf_main(uint32_t* args)
{
	int p0x = 140;
	int p1x = 20;
	int p0y = 129;
	int p1y = 129;
	int fly_top_x = 20;
	int fly_top_y = 2;
	int fly_top_index = 0;
	int fly_bot_x = 8;
	int fly_bot_y = 20;
	int frame = 0;
	int fanFrame = 0;
	int fly_loop_index = 0;
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
	// Init arrays
	for (int i = 0; i < 192; i++)
	{
		colupfBuffer[i] = 0;
		grp0Buffer[i] = 0;
		grp1Buffer[i] = 0;
	}

	// Render loop
	while (true) {

		PrintScore(scoreText);

		fly_top_x -= 1;
		if (fly_top_x < 0)
			fly_top_x = 159;
		fly_top_y += Fly_Wave_Y[fly_top_index];
		fly_top_index++;
		if (fly_top_index > sizeof(Fly_Wave_Y))
			fly_top_index = 0;

		if ((frame & 0) == 0) {
			fly_bot_x += Fly_Loop_X[fly_loop_index];
			fly_bot_y+= Fly_Loop_Y[fly_loop_index];
			fly_loop_index += 1;
			if (fly_loop_index >= sizeof(Fly_Loop_X))
				fly_loop_index = 0;
			if (fly_bot_x > 159)
				fly_bot_x -= 160;
			if (fly_bot_x < 0)
				fly_bot_x += 160;
		}

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
			playfieldBuffer[(19 + y) * 5 + 1] = FanBladeGraphics[fanFrame][y * 2] >> 7;
			playfieldBuffer[(19 + y) * 5 + 2] = FanBladeGraphics[fanFrame][y * 2] << 1 | FanBladeGraphics[fanFrame][y * 2 + 1] >> 7;
			playfieldBuffer[(19 + y) * 5 + 3] = FanBladeGraphics[fanFrame][y * 2 + 1] << 1;
		}

		// Monkey Walking Test
		//for (int i = 0; i < 16; i++)
		//{
		//	for (int j = 0; j < 12; j++)
		//	{
		//		grp0Buffer[i * 12 + j] = MonkeyWalkingGraphics[(frame >> 3) & 1][j];
		//	}
		//}

		//Fan Chasis
		for (int i = 0; i < 64; i++)
		{
			grp1Buffer[i] = 0;
		}
		for (int i = 0; i < sizeof(FanChasisGraphics)/sizeof(FanChasisGraphics[0]); i++)
		{
			grp1Buffer[i+2] = FanChasisGraphics[i];
			colup1Buffer[i+2] = FanChasisColu[i];
		}

		// Banana
		for (int i = 0; i < sizeof(BonusBananaGraphics)/sizeof(BonusBananaGraphics[0]); i++)
		{
			grp1Buffer[i + 33] = BonusBananaGraphics[i];
			colup1Buffer[i + 33] = BonusBananaColu[i];
		}

		for (int i = 140*5; i < sizeof(playfieldBuffer); i++)
		{
			playfieldBuffer[i] = 0;
		}
		// Mattress
		for (int i = 4; i < 37; i++)
		{
			int height = SineTables[frame & 0x1f][i];
			if (i == p0x/4)
			{
				p0y = 163 - height;
			}
			if (i == p1x/4)
			{
				p1y = 163 - height;
			}
			for (int j = 0; j <= height; j++)
			{
				setPF(i, 175 - j);
			}
		}
		// Monkey Idle Test
		for (int j = 100; j < 192; j++)
		{
			grp0Buffer[j] = 0;
			grp1Buffer[j] = 0;
		}
		for (int j = 0; j < 12; j++)
		{
			grp0Buffer[p0y + j] = MonkeyIdleGraphics[j];
			grp1Buffer[p1y + j] = MonkeyWalkingGraphics[0][j]; //112-147
		}

		vcsEndOverblank();
		vcsSta3(WSYNC); vcsSta3(WSYNC); vcsSta3(WSYNC); vcsSta3(WSYNC); vcsSta3(WSYNC); 

		PositionObject(0, p0x, RESP0, HMP0);

		vcsLda2(0);
		vcsSta3(PF0);
		vcsSta3(PF1);
		vcsSta3(PF2);
		vcsSta3(GRP0);
		vcsSta3(GRP1);
		vcsSta3(ENAM0);
		vcsSta3(ENAM0);
		vcsSta3(ENABL);
		vcsSta3(NUSIZ0);
		vcsLda2(ColuCeiling);
		vcsSta3(COLUBK);
		vcsLda2(ColuFanBlade);
		vcsSta3(COLUPF);
		vcsWrite5(COLUP0, 0xe8);
		vcsSta3(RESPONE); // 42 cycles before this
		vcsNop2n(7);
		vcsWrite5(NUSIZ1, 0x30);
		vcsWrite5(HMP1, 0x20);
		vcsWrite5(VBLANK, 0);

		int line = 0;

		// Ceiling
		while (1)
		{
			vcsSta3(HMOVE);
			vcsNop2n(32);
			vcsSta4(HMCLR);
			line++;
			if (line >= 2)
				break;
			vcsSta3(WSYNC);
		}
		vcsWrite5(COLUBK, ColuWall);

		// Fan region
		while (line < 29)
		{
			vcsSta3(HMOVE);
			vcsJmp3();
			vcsWrite5(GRP1, grp1Buffer[line]);
			vcsWrite5(GRP0, grp0Buffer[line]);
			vcsWrite5(PF0, ReverseByte[playfieldBuffer[line * 5] >> 4]);
			vcsWrite5(PF1, (playfieldBuffer[line * 5] << 4) | (playfieldBuffer[line * 5 + 1] >> 4));
			vcsWrite5(COLUP1, colup1Buffer[line]);
			vcsJmp3();
			vcsJmp3();
			vcsWrite5(PF2, ReverseByte[(uint8_t)((playfieldBuffer[line * 5 + 1] << 4) | (playfieldBuffer[line * 5 + 2] >> 4))]);
			vcsWrite5(PF0, ReverseByte[playfieldBuffer[line * 5 + 2]]);
			vcsWrite5(PF1, playfieldBuffer[line * 5 + 3]);
			vcsWrite5(PF2, ReverseByte[playfieldBuffer[line * 5 + 4]]);
			vcsSta3(HMCLR);
			vcsSta3(WSYNC);
			line++;
		}
		DrawFlyRegion(&line, 14, fly_top_x, fly_top_y, frame & 1);
		DrawFlyRegion(&line, 24, fly_bot_x, fly_bot_y, frame & 1);

		PositionObject(line++, 132, RESPONE, HMP1);
		PositionObject(line++, 25, RESM1, HMM1);

		// Level 1 - Wide bed
		// Headboard
		for (int i = 0; i < 40; i++)
		{
			vcsSta3(HMOVE);
			vcsWrite5(COLUPF, ColuHeadboard);
			vcsWrite5(GRP0, grp0Buffer[line]);
			vcsWrite5(PF0, ReverseByte[HeadBoardWideGraphics[i * 5] >> 4]);
			vcsWrite5(PF1, (HeadBoardWideGraphics[i * 5] << 4) | (HeadBoardWideGraphics[i * 5 + 1] >> 4));
			vcsWrite5(COLUBK, ColuWall);
			vcsWrite5(PF2, ReverseByte[(uint8_t)((HeadBoardWideGraphics[i * 5 + 1] << 4) | (HeadBoardWideGraphics[i * 5 + 2] >> 4))]);
			vcsWrite5(PF0, ReverseByte[HeadBoardWideGraphics[i * 5 + 2]]);
			vcsWrite6(PF1, HeadBoardWideGraphics[i * 5 + 3]);
			vcsWrite5(PF2, ReverseByte[HeadBoardWideGraphics[i * 5 + 4]]);
			if (i < 39)
			{
				vcsJmp3();
				vcsWrite5(COLUP1, ColuWall);
				vcsSta3(HMCLR);
				vcsWrite5(VDELP1, 0xff);
			}
			else
			{
				vcsWrite5(HMP1, 0xf0);
				vcsWrite5(HMM1, 0x10);
				vcsWrite5(GRP1, 0xff);
				vcsWrite5(ENAM1, 0xff);
			}
			vcsSta3(WSYNC);
			line++;
		}

		// 4 lines of pillow and wall
		// 4 lines of sheet and wall
		for (int i = 0; i < 8; i++)
		{
			vcsSta3(HMOVE);
			vcsWrite5(COLUPF, i < 4 ? ColuPillow : ColuSheet);
			vcsWrite5(GRP0, grp0Buffer[line]);
			vcsWrite5(PF0, 0);
			vcsWrite5(PF1, i < 4 ? 0x3f : 0x7f);
			vcsWrite5(COLUBK, ColuWall);
			vcsWrite5(PF2, 0xff);
			vcsWrite5(CTRLPF, 1);
			if (i == 7)
			{
				vcsNop2n(15);
				vcsWrite5(CTRLPF, 0x05);
			}
			vcsSta3(WSYNC);
			line++;
		}
		// 4 lines of post, wall, and sheet
		for (int i = 0; i < 4; i++)
		{
			vcsSta3(HMOVE);
			vcsWrite5(COLUPF, ColuHeadboard);
			vcsWrite5(GRP0, grp0Buffer[line]);
			vcsWrite5(PF0, 0xff);
			vcsWrite5(PF1, 0x80);
			vcsWrite5(COLUBK, ColuSheet);
			vcsWrite5(PF2, 0x00);
			vcsJmp3();
			vcsWrite5(PF1, 0x00);
			if (i == 3)
			{
				vcsNop2n(12);
				vcsWrite5(ENAM1, 0);
				vcsSta3(GRP1);
			}
			vcsSta3(WSYNC);
			line++;
		}
		// 4 lines of post and sheet
		for (int i = 0; i < 4; i++)
		{
			vcsSta3(HMOVE);
			vcsWrite5(COLUPF, ColuBedPost);
			vcsWrite5(GRP0, grp0Buffer[line]);
			vcsWrite5(PF0, 0xff);
			vcsWrite5(PF1, 0x80);
			vcsWrite5(COLUBK, ColuSheet);
			vcsWrite5(PF2, 0x00);
			vcsJmp3();
			vcsWrite5(PF1, 0x00);
			vcsSta3(WSYNC);
			line++;
		}

		// Position Second Monkey while drawing matress and bed posts with COLUBK
		int x = p1x;
		vcsSta3(HMOVE);
		if (x < 80) {
			vcsWrite5(GRP0, grp0Buffer[line]);
			vcsWrite5(PF0, 0xff);
			vcsNop2n(4);
			while (x > 26) {
				vcsWrite5(PF0, 0xff);
				x -= 15;
			}
			vcsSta3(HMCLR);
			vcsSta3(RESPONE);
			vcsWrite5(HMP1, ((x - 11) ^ 0x07) << 4);
			vcsWrite5(PF0, 0x70);
		}
		else {
			vcsWrite5(GRP0, grp0Buffer[line]);
			vcsWrite5(PF0, 0xff);
			vcsNop2n(9);
			x -= 30;
			while (x > 26) {
				vcsWrite5(PF0, 0x70);
				x -= 15;
			}
			vcsSta3(HMCLR);
			vcsSta3(RESPONE);
			vcsWrite5(HMP1, ((x - 11) ^ 0x07) << 4);
		}
			
		vcsSta3(WSYNC);
		line++;

		vcsSta3(HMOVE);
		vcsWrite5(PF0, 0xff);
		vcsWrite5(GRP0, grp0Buffer[line]);
		vcsNop2n(22);
		vcsWrite5(PF0, 0x70);
		vcsSta3(HMCLR);
		vcsJmp3();
		vcsJmp3();
		vcsWrite5(COLUBK, ColuBedPost);
		line++;

		for (int i = 0; line < 175; i++)
		{
			vcsSta3(HMOVE);
			if (i == 0)
			{
				vcsWrite5(COLUPF, ColuMattress);
			}
			else {
				vcsWrite5(CTRLPF, 0);
			}
			vcsWrite5(GRP0, grp0Buffer[line]);
			vcsWrite5(PF0, ReverseByte[playfieldBuffer[line * 5] >> 4]);
			vcsWrite5(PF1, (playfieldBuffer[line * 5] << 4) | (playfieldBuffer[line * 5 + 1] >> 4));
			vcsWrite5(COLUBK, ColuSheet);
			vcsWrite5(PF2, ReverseByte[(uint8_t)((playfieldBuffer[line * 5 + 1] << 4) | (playfieldBuffer[line * 5 + 2] >> 4))]);
			vcsWrite5(PF0, ReverseByte[playfieldBuffer[line * 5 + 2]]);
			vcsWrite6(PF1, playfieldBuffer[line * 5 + 3]);
			vcsWrite5(PF2, ReverseByte[playfieldBuffer[line * 5 + 4]]);
			vcsJmp3();
			vcsJmp3();
			vcsSta3(HMCLR);
			vcsNop2n(2);
			vcsWrite5(GRP1, grp1Buffer[line+1]);
			vcsWrite5(COLUBK, ColuBedPost);
			vcsSta3(WSYNC);
			line++;
		}
		// Level 2 Medium bed
		while (line < 0)
		{
			vcsSta3(HMOVE);
			vcsWrite5(COLUPF, colupfBuffer[line]);
			vcsWrite5(PF0, ReverseByte[playfieldBuffer[line * 5] >> 4]);
			vcsWrite5(PF1, (playfieldBuffer[line * 5] << 4) | (playfieldBuffer[line * 5 + 1] >> 4));
			vcsJmp3();
			vcsLdx2(ColuSheet);
			vcsWrite5(COLUBK, ColuBedPost);
			vcsStx4(COLUBK);
			vcsWrite5(PF2, ReverseByte[(uint8_t)((playfieldBuffer[line * 5 + 1] << 4) | (playfieldBuffer[line * 5 + 2] >> 4))]);
			vcsWrite5(PF0, ReverseByte[playfieldBuffer[line * 5 + 2]]);
			vcsWrite5(PF1, playfieldBuffer[line * 5 + 3]);
			vcsJmp3();
			vcsWrite5(PF2, ReverseByte[playfieldBuffer[line * 5 + 4]]);
			vcsNop2n(3);
			vcsLdx2(ColuWall);
			vcsWrite5(COLUBK, ColuBedPost);
			vcsStx4(COLUBK);
			vcsSta3(WSYNC);
			line++;
		}
		// Level 3 Narrow bed
		while (line < 0)
		{
			vcsSta3(HMOVE);
			vcsWrite5(COLUPF, colupfBuffer[line]);
			vcsWrite5(PF0, ReverseByte[playfieldBuffer[line * 5] >> 4]);
			vcsWrite6(PF1, (playfieldBuffer[line * 5] << 4) | (playfieldBuffer[line * 5 + 1] >> 4));
			vcsWrite6(PF2, ReverseByte[(uint8_t)((playfieldBuffer[line * 5 + 1] << 4) | (playfieldBuffer[line * 5 + 2] >> 4))]);
			vcsLdx2(ColuSheet);
			vcsWrite5(COLUBK, ColuBedPost);
			vcsStx4(COLUBK);
			vcsWrite5(PF0, ReverseByte[playfieldBuffer[line * 5 + 2]]);
			vcsWrite5(PF1, playfieldBuffer[line * 5 + 3]);
			vcsJmp3();
			vcsWrite5(PF2, ReverseByte[playfieldBuffer[line * 5 + 4]]);
			vcsJmp3();
			vcsLdx2(ColuWall);
			vcsWrite5(COLUBK, ColuBedPost);
			vcsStx4(COLUBK);
			vcsSta3(WSYNC);
			line++;
		}

		DisplayText(ColuBedPost);
		vcsWrite5(VBLANK, 2);
		uint8_t joysticks = vcsRead4(SWCHA);
		vcsNop2();
		uint8_t but0 = vcsRead4(INPT4);
		vcsNop2();
		uint8_t but1 = vcsRead4(INPT5);
		vcsStartOverblank();
		uint8_t joy = joysticks >> 4;
		if (((joy & 0x4) == 0) && p0x > 16) {
			// left
			p0x -= 1;
		}
		if (((joy & 0x8) == 0) && p0x < 140) {
			// right
			p0x += 1;
		}
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
void PositionObject(int line, int x, uint8_t resp, uint8_t hm)
{
	vcsSta3(HMOVE);
	if (x < 11) {
		vcsSta3(resp);
		vcsWrite5(GRP0, grp0Buffer[line]);
		vcsWrite5(GRP1, grp1Buffer[line]);
		vcsNop2n(15);
		vcsSta3(HMCLR);
		vcsWrite5(hm, ((x + 3) ^ 0x07) << 4);
	}
	else if (x < 100) {
		vcsWrite5(GRP0, grp0Buffer[line]);
		vcsWrite5(GRP1, grp1Buffer[line]);
		vcsNop2n(4);
		while (x > 26) {
			vcsWrite5(GRP0, grp0Buffer[line]);
			x -= 15;
		}
		vcsJmp3();
		vcsSta3(resp);
		vcsSta3(HMCLR);
		vcsWrite5(hm, ((x - 11) ^ 0x07) << 4);
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
		vcsSta3(resp);
		vcsWrite5(hm, ((x - 11) ^ 0x07) << 4);
	}
	else {
		vcsWrite5(GRP0, grp0Buffer[line]);
		vcsWrite5(GRP1, grp1Buffer[line]);
		vcsNop2n(21);
		vcsJmp3();
		vcsJmp3();
		vcsSta3(HMCLR);
		vcsWrite5(hm, ((x - 146) ^ 0x07) << 4);
		vcsSta3(resp);
	}
	vcsSta3(WSYNC);
}

void DrawFlyRegion(int* line, int height, int fly_x, int fly_y, int fly_frame) {
	PositionObject(*line, fly_x, RESBL, HMBL);
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