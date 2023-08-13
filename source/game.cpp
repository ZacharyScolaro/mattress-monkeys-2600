#include "sound.h"
#include "sprites.h"
#include "text.h"
#include "vcsLib.h"
#include "fp32.hpp"
#include "boundingBox.hpp"
#include <cstddef>

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
#define ColuP0Monkey 0x5a
#define ColuP1Monkey 0x2a

class Monkey {
public:
	BoundingBox<FP32> hit_box;
	uint8_t color;
	FP32 x;
	FP32 y;
	FP32 velocity_x;
	FP32 velocity_y;
	int score;
};

__attribute__((section(".noinit")))
static uint8_t bitmap[192 * 80];

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

static char scoreText[18] = { 0, 0, 0, 0, 16, 18, 18, 18, 16, 16, 18, 18, 18, 16, 0, 0, 0, 0 };
void setPF(int x, int y);
void DrawFlyRegion(int* line, int height, int fly_x, int fly_y, int fly_frame);
void PositionObject(int line, int x, uint8_t resp, uint8_t hm);
void move_monkey(uint8_t joy, Monkey* monkey);
void RenderWideBed(int& line, Monkey* jumping_monkey, Monkey* standing_monkey);

#if 1
// Gopher
#define vcsWrite6(a,d) vcsLda2(d); vcsSta4(a);
// 7800 mode
void injectDmaDataWM0(int address, int count, const uint8_t* pBuffer) {}
void injectDmaDataWM1(int address, int count, const uint8_t* pBuffer) {}
#else
// Chameleon Cart
// 7800 mode
void injectDmaDataWM0(int address, int count, const uint8_t* pBuffer);
void injectDmaDataWM1(int address, int count, const uint8_t* pBuffer);
#endif

static void init_7800();

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
static const int8_t Initial_X_Velocity_Lookup[20] = { 1, 1, 2, 2, 3, 4, 3, 2, 2, 1, -1, -1, -2, -2, -3, -4, -3, -2, -2, -1 };

extern "C" int elf_main(uint32_t * args)
{
	bool banana_shown = false;
	int banana_cooldown = 5 * 60;
	int min = 500;
	int max = 0;
	int fly_top_x = 20;
	int fly_top_y = 2;
	size_t fly_top_index = 0;
	int fly_bot_x = 8;
	int fly_bot_y = 20;
	int frame = 0;
	int fanFrame = 0;
	size_t fly_loop_index = 0;
	track_player audio_player0;
	track_player audio_player1;
	track_player sfx_player;
	track_player* chan1_player;
	int sfx_frames_remaining = 0;
	int sine_frame = 0;
	int sine_hpos = 20;
	Monkey monkey_0 = { .hit_box = BoundingBox<FP32>(0,0,0,8,0,12), .color = ColuP0Monkey, .x = 40, .y = 50, .velocity_x = 0, .velocity_y = 0 };
	Monkey monkey_1 = { .hit_box = BoundingBox<FP32>(0,0,0,8,0,12), .color = ColuP1Monkey, .x = 120, .y = 129, .velocity_x = 0, .velocity_y = 0 };
	Monkey* jumping_monkey = &monkey_0;
	Monkey* standing_monkey = &monkey_1;
	Monkey* p0_monkey = &monkey_0;
	Monkey* p1_monkey = &monkey_1;
	FP32 GravityAscend = fp32(0.25);
	FP32 GravityFall = fp32(0.5);
	BoundingBox<FP32> fly_top_hit_box = BoundingBox<FP32>(1, 1, 0, 2, 0, 2);
	BoundingBox<FP32> fly_bot_hit_box = BoundingBox<FP32>(1, 1, 0, 2, 0, 2);
	BoundingBox<FP32> banana_hit_box = BoundingBox<FP32>(77, 33, 0, 7, 0, 13);

	if (args[MP_SYSTEM_TYPE] == ST_NTSC_7800)
	{
		init_7800();
	}

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
	for (size_t i = 0; i < sizeof(playfieldBuffer)/ sizeof(playfieldBuffer[0]); i++)
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

	init_audio_player(&audio_player0, 0, &SongMonkeys);
	init_audio_player(&audio_player1, 1, &SongMonkeys);
	

	// Render loop
	while (true) {
		// monkey physics
		jumping_monkey->x += jumping_monkey->velocity_x;
		if (jumping_monkey->x < 16) {
			jumping_monkey->x = 16;
			jumping_monkey->velocity_x = 0;
		}
		if (jumping_monkey->x > 140) {
			jumping_monkey->x = 140;
			jumping_monkey->velocity_x = 0;
		}
		// Apply gravity
		if (jumping_monkey->velocity_y > 0)
		{
			// Fall faster than ascent
			jumping_monkey->velocity_y += GravityFall;
		}
		else
		{
			jumping_monkey->velocity_y += GravityAscend;
		}
		jumping_monkey->y += jumping_monkey->velocity_y;
		if (jumping_monkey->y > 0xa3)
		{
			jumping_monkey->y = 0xa3;
			Monkey* temp = jumping_monkey;
			jumping_monkey = standing_monkey;
			standing_monkey = temp;
			jumping_monkey->velocity_x = Initial_X_Velocity_Lookup[((sine_hpos + 105) - (((standing_monkey->x.Round()) + 3) / 4)) % 20];
			//uncomment this to test max jump height jumping_monkey->y = 0x80;
			jumping_monkey->velocity_y = fp32(-7.75);// velocity_adjust * -100;// (jumping_monkey->y.Round() - 500);
		}

		// preclear buffers
		for (int i = 0; i < 192; i++)
		{
			grp0Buffer[i] = 0;
			grp1Buffer[i] = 0;
		}

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
		for (size_t i = 0; i < sizeof(FanChasisGraphics)/sizeof(FanChasisGraphics[0]); i++)
		{
			grp1Buffer[i+2] = FanChasisGraphics[i];
			colup1Buffer[i+2] = FanChasisColu[i];
		}

		// Banana
		if (banana_shown)
		{
			for (size_t i = 0; i < sizeof(BonusBananaGraphics) / sizeof(BonusBananaGraphics[0]); i++)
			{
				grp1Buffer[i + 33] = BonusBananaGraphics[i];
				colup1Buffer[i + 33] = BonusBananaColu[i];
			}
		}
		else {
			banana_cooldown--;
			if (banana_cooldown <= 0)
			{
				banana_shown = true;
				banana_cooldown = 5 * 60;
			}
		}

		for (size_t i = 140*5; i < sizeof(playfieldBuffer); i++)
		{
			playfieldBuffer[i] = 0;
		}
		// Mattress
		if ((frame & 0x01) == 0)
		{
			sine_frame++;
			if (jumping_monkey->y > 129 && jumping_monkey->y < 0xa4)
			{
				if (jumping_monkey->y > 0x92)
				{
					// Once below sine middle move wave to player
					sine_hpos = 34 - ((jumping_monkey->x.Round()) - 2) / 4;
				}
				// Adjust height down to player if needed
				while (SineTables[sine_frame & 0x1f][((jumping_monkey->x.Round()) / 4) + sine_hpos] > (164 - jumping_monkey->y.Round()))
				{
					sine_frame++;
				}
			}
			else
			{
			}
			sine_frame &= 0x1f;
		}

		for (int i = 4; i < 37; i++)
		{
			int height = SineTables[sine_frame][i + sine_hpos]; //frame & 0x1f
			if (i == ((standing_monkey->x.Round() )+3) /4)
			{
				standing_monkey->y = 163 - height;
			}
			for (int j = 0; j <= height; j++)
			{
				setPF(i, 175 - j);
			}
		}
		// Monkey Idle Test
		for (int j = 0; j < 12; j++)
		{
			grp0Buffer[jumping_monkey->y.Round() + j] = MonkeyIdleGraphics[j];
			grp1Buffer[standing_monkey->y.Round() + j] = MonkeyWalkingGraphics[0][j]; //112-147
		}

		next_audio_frame(&audio_player0);
		next_audio_frame(&audio_player1);
		if (sfx_frames_remaining > 0)
		{
			sfx_frames_remaining--;
			next_audio_frame(&sfx_player);
			chan1_player = &sfx_player;
		}
		else
		{
			chan1_player = &audio_player1;
		}
		if (standing_monkey->y < min)
		{
			min = standing_monkey->y.Round();
		}
		if (standing_monkey->y > max)
		{
			max = standing_monkey->y.Round();
		}

		////int8_t iv = Initial_X_Velocity_Lookup[((sine_hpos + 105) - (((monkey_0.x.Round()) + 3) / 4)) % 20];
		//for (int i = 0; i < 8; i++)
		//{
		//	scoreText[i] = (char)((uint32_t)(jumping_monkey->x.Value) >> ((7 - i) * 4)) & 0xf;
		//}
		//for (int i = 0; i < 8; i++)
		//{
		//	scoreText[i+9] = (char)((uint32_t)(jumping_monkey->y.Value) >> ((7 - i) * 4)) & 0xf;
		//}
		jumping_monkey->hit_box.X = jumping_monkey->x;
		jumping_monkey->hit_box.Y = jumping_monkey->y;

		fly_top_hit_box.X = fly_top_x;
		if (jumping_monkey->hit_box.Intersects(fly_top_hit_box))
		{
			fly_top_x = 0;
			jumping_monkey->score += 1;
		}

		fly_bot_hit_box.X = fly_bot_x;
		if (jumping_monkey->hit_box.Intersects(fly_bot_hit_box))
		{
			fly_bot_x = 0;
			jumping_monkey->score += 1;
		}
		
		////for (int i = 0; i < 2; i++)
		////{
		////	scoreText[i] = (char)(iv >> ((1 - i) * 4)) & 0xf;
		////}
		if (banana_shown && jumping_monkey->hit_box.Intersects(banana_hit_box))
		{
			banana_shown = false;
			jumping_monkey->score += 5;
		}
		int left_score = monkey_0.score;
		for (int i = 0; i < 4; i++)
		{
			scoreText[3 - i] = (left_score % 10) & 0xf;
			left_score /= 10;
		}
		int right_score = monkey_1.score;
		for (int i = 0; i < 4; i++)
		{
			scoreText[17 - i] = (right_score % 10) & 0xf;
			right_score /= 10;
		}
		PrintScore(scoreText);
		vcsEndOverblank();
		vcsSta3(WSYNC); 
		vcsWrite5(AUDC0, audio_player0.control);
		vcsWrite5(AUDV0, audio_player0.volume);
		vcsWrite5(AUDF0, audio_player0.frequency);
		vcsWrite5(AUDC1, chan1_player->control);
		vcsWrite5(AUDV1, chan1_player->volume);
		vcsWrite5(AUDF1, chan1_player->frequency);
		vcsSta3(WSYNC); vcsSta3(WSYNC); vcsSta3(WSYNC); vcsSta3(WSYNC);

		PositionObject(0, jumping_monkey->x.Round(), RESP0, HMP0);

		vcsLda2(0);
		vcsSta3(PF0);
		vcsSta3(PF1);
		vcsSta3(PF2);
		vcsSta3(GRP0);
		vcsSta3(GRP1);
		vcsSta3(ENAM0);
		vcsSta3(ENAM1);
		vcsSta3(ENABL);
		vcsSta3(NUSIZ0);
		vcsLda2(ColuCeiling);
		vcsSta3(COLUBK);
		vcsLda2(ColuFanBlade);
		vcsSta3(COLUPF);
		vcsWrite5(COLUP0, jumping_monkey->color);
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
		fly_top_hit_box.Y = fly_top_y + line;
		DrawFlyRegion(&line, 14, fly_top_x, fly_top_y, frame & 1);
		fly_bot_hit_box.Y = fly_bot_y + line;
		DrawFlyRegion(&line, 24, fly_bot_x, fly_bot_y, frame & 1);

		PositionObject(line++, 132, RESPONE, HMP1);
		PositionObject(line++, 25, RESM1, HMM1);

		RenderWideBed(line, jumping_monkey, standing_monkey);
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
		move_monkey(joysticks >> 4, p0_monkey);
		move_monkey(joysticks & 0xf, p1_monkey);
		if (sfx_frames_remaining == 0 && (but0 & 0x80) == 0)
		{
			Monkey* temp = p0_monkey;
			p0_monkey = p1_monkey;
			p1_monkey = temp;
			p0_monkey->color = ColuP0Monkey;
			p1_monkey->color = ColuP1Monkey;
			sfx_frames_remaining = SfxBounce.percussions->length;
			init_audio_player(&sfx_player, sfx_player.channel_index == 0 ? 1 : 0, &SfxBounce);
		}
	}
}

void move_monkey(uint8_t joy, Monkey* monkey)
{
	if (((joy & 0x4) == 0) && monkey->x > 16) {
		// left
		monkey->x -= 1;
		if (monkey->velocity_x > 0)
		{
			monkey->velocity_x--;
		}
	}
	if (((joy & 0x8) == 0) && monkey->x < 140) {
		// right
		monkey->x += 1;
		if (monkey->velocity_x < 0)
		{
			monkey->velocity_x++;
		}
	}
	if (((joy & 0x1) == 0) && monkey->y > 4) {
		// up
		monkey->y -= 1;
	}
	if (((joy & 0x2) == 0) && monkey->y < 0xa3) {
		// down
		monkey->y += 1;
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

__attribute__((long_call, section(".RamFunc")))
static void init_7800()
{
	for (size_t i = 0; i < sizeof(kernel_7800); i++) {
		vcsWrite6((uint16_t)(0x1800 + i), kernel_7800[i]);
		vcsNop2n(2);
		vcsJmp3();
		vcsNop2n(2);
	}


	vcsSta3(0x24);

	vcsWrite5(0x20, 0x1c);
	vcsWrite5(0x21, 0x72);
	vcsWrite5(0x22, 0x59);
	vcsWrite5(0x23, 0xc4);
	
	vcsWrite5(0x31, 0xf3);
	vcsWrite5(0x32, 0x48); //36 aa 73
	vcsWrite5(0x33, 0x79);
	
	vcsWrite5(0x35, 0x36);
	vcsWrite5(0x36, 0xce);
	vcsWrite5(0x37, 0xf1);
	
	vcsWrite5(0x39, 0xaa);
	vcsWrite5(0x3A, 0x8e);
	vcsWrite5(0x3B, 0x31);
	
	vcsWrite5(0x3D, 0x73);
	vcsWrite5(0x3E, 0x44);
	vcsWrite5(0x3F, 0x55);


	vcsJmpToRam3(0x1800);

	//// Test pattern
	//int color_count = 16;
	//uint8_t colors[16] = {
	//	0x00, 0x05, 0x0a, 0x0f,
	//	0x50, 0x55, 0x5a, 0x5f,
	//	0xa0, 0xa5, 0xaa, 0xaf,
	//	0xf0, 0xf5, 0xfa, 0xff,
	//};
	//for (int y = 0; y < 192; y++)
	//{
	//	for (int x = 0; x < color_count; x+= 1)
	//	{
	//		for (int i = 0; i < (80/ color_count); i++)
	//		{
	//			bitmap[(y * 80) + (x * (80 / color_count)) + i] = colors[x];
	//		}
	//	}
	//}
	uint8_t dll[128];
	uint16_t dma_addr[64];
	while (1) {
		// TODO each frame update scrolling, sampled audio, colubk 
		// To do vertical scrolling we need to dynamically build the DLL
		int d = 0;
		int dma_addr_ix = 0;
		int buffer_height = 192;
		int vertical_scroll = 10;
		// Top of buffer shifted to bottom portion of screen
		for (int i = vertical_scroll; i < buffer_height; i+=7)
		{
			int zone_height = 7;
			int region_remaining = buffer_height - i;
			if (region_remaining < 7)
			{
				zone_height = region_remaining;
			}
			dma_addr[dma_addr_ix] = 0x10c0 | ((zone_height - 1) << 8);
			dll[d++] = zone_height-1;
			dll[d++] = 0x1a;
			dll[d++] = 0x00;
		}
		// Remaining portion of buffer to top portion of screen
		for (int i = 0; i < vertical_scroll; i += 7)
		{
			int zone_height = 7;
			int region_remaining = vertical_scroll - i;
			if (region_remaining < 7)
			{
				zone_height = region_remaining;
			}
			dma_addr[dma_addr_ix] = 0x10c0 | ((zone_height - 1) << 8);
			dll[d++] = zone_height - 1;
			dll[d++] = 0x1a;
			dll[d++] = 0x00;
		}
		// Padd bottom of screen
		for (int i = 0; i < 5; i++)
		{
			dll[d++] = 0x0f;
			dll[d++] = 0x18;
			dll[d++] = 0xfa;
		}
		// TODO trap control transfer back to ARM
		vcsWaitForAddress(0x18ff);
		vcsJmp3();
		vcsNop2();
		for (uint16_t i = 0; i < d; i++)
		{
			vcsWrite6(0x1906 + i, dll[i]);
		}


		for (int row = 0; row < 192; )
		{
			for (int i = dma_addr[dma_addr_ix++]; i > 0x1000; i -= 0x100)
			{
				const uint8_t* pRow = bitmap + (row * 80);
				row++;
				injectDmaDataWM0(i, 20, pRow);
				injectDmaDataWM0(i, 20, &(pRow[40]));
				injectDmaDataWM1(i, 32, pRow);
				injectDmaDataWM1(i, 32, &(pRow[32]));
				injectDmaDataWM1(i, 16, &(pRow[64]));
			}
		}
	}
}

void RenderWideBed(int& line, Monkey* jumping_monkey, Monkey* standing_monkey) {
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
	int x = standing_monkey->x.Round();
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
		vcsWrite5(COLUP1, standing_monkey->color);
		vcsSta3(HMCLR);
		vcsNop2();
		vcsWrite5(GRP1, grp1Buffer[line + 1]);
		vcsWrite5(COLUBK, ColuBedPost);
		vcsSta3(WSYNC);
		line++;
	}
}