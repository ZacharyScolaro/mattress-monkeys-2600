#include "sound.h"
#include "sprites.h"
#include "text.h"
#include "vcsLib.h"
#include "fp32.hpp"
#include "boundingBox.hpp"
#include <cstddef>

const FP32 MaxFlyVelocity = fp32(2.5);
const FP32 MaxFlyVelocityMinus = MaxFlyVelocity * fp32(-1.0);
const FP32 FlyAccel = fp32(0.75);
const FP32 FlyAccelMinus = FlyAccel * fp32(-1.0);
const uint8_t FlyBuzzVolAdd = 1;
const FP32 ArmVelocity = fp32(16);
const int FlyAscentDuration = 32;
const int BubblePopFrames = 3;
const int BubbleScoreFrames = 45;
const int ChallengeFrames = 60*20;
const int ChallengeThreshold = 100;
const uint8_t ColuRedWall = 0x42;
const int BubblePopValue = 10;
const int BubbleStartPositions[16] = { 30, 20, 30, 40, 50, 60, 70, 80, 90, 100, 90, 80, 70, 60, 50, 40 };
const FP32 BubbleVelocity = fp32(0.04);

int countdown_frames_remaining = 0;
int countdown_index = 0;

int challenge_player = 0;
int challenge_frames_remaining = 0;
int next_challenge_score = 0;
int min_monkey_x = 16;
int max_monkey_x = 140;
int shake_frames_remaining = 0;

int monkey_y_lwm = 500;
int monkey_y_hwm = 0;

FP32 bubbleDistance = 0;
int bubble_index = 0;
int bubble_offset = 0;
uint8_t zoom_level = 0;
bool zoom_out_red_wall;

static uint8_t InitialColuWall = 0x6a						;
static uint8_t InitialColuFloor = 0x1d						;
static const uint8_t InitialColuCeiling = 0x0f					;
static const uint8_t InitialColuSheet = 0xd6						; // formerly 0xdb
static const uint8_t InitialColuMattress = 0xd4					; // formerly 0xd7
static const uint8_t InitialColuFlyWing = 0xff					;
static const uint8_t InitialColuFlyBody = 0x00					;
static const uint8_t InitialColuPillow = 0x0f					;
static const uint8_t InitialColuHeadboard = 0xf7				;
static const uint8_t InitialColuBedPost = 0xf5					;
static const uint8_t InitialColuFanBlade = 0x02					;
static const uint8_t InitialColuP0Monkey = 0xf3					;
static const uint8_t InitialColuP1Monkey = 0x2f					;

static const uint8_t InitialColuScoreBackground = 0;
static uint8_t ColuScoreBackground = InitialColuScoreBackground;

static uint8_t ColuCeiling	  = InitialColuCeiling;
static uint8_t ColuWall = InitialColuWall;
static uint8_t ColuSheet = InitialColuSheet;
static uint8_t ColuMattress = InitialColuMattress;
static uint8_t ColuFlyWing = InitialColuFlyWing;
static uint8_t ColuFlyBody = InitialColuFlyBody;
static uint8_t ColuPillow = InitialColuPillow;
static uint8_t ColuHeadboard = InitialColuHeadboard;
static uint8_t ColuBedPost = InitialColuBedPost;
static uint8_t ColuFanBlade = InitialColuFanBlade;
static uint8_t ColuP0Monkey = InitialColuP0Monkey;
static uint8_t ColuP1Monkey = InitialColuP1Monkey;
static uint8_t ColuFloor = InitialColuFloor;

const uint8_t BitWidthLookup[16] = { 0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4 };

const uint8_t BitWidthTo24PixelLookup[25 * 3] = {
	0x00, 0x00, 0x00,
	0x00, 0x00, 0x01,
	0x00, 0x00, 0x03,
	0x00, 0x00, 0x07,
	0x00, 0x00, 0x0f,
	0x00, 0x00, 0x1f,
	0x00, 0x00, 0x3f,
	0x00, 0x00, 0x7f,
	0x00, 0x00, 0xff,
	0x00, 0x01, 0xff,
	0x00, 0x03, 0xff,
	0x00, 0x07, 0xff,
	0x00, 0x0f, 0xff,
	0x00, 0x1f, 0xff,
	0x00, 0x3f, 0xff,
	0x00, 0x7f, 0xff,
	0x00, 0xff, 0xff,
	0x01, 0xff, 0xff,
	0x03, 0xff, 0xff,
	0x07, 0xff, 0xff,
	0x0f, 0xff, 0xff,
	0x1f, 0xff, 0xff,
	0x3f, 0xff, 0xff,
	0x7f, 0xff, 0xff,
	0xff, 0xff, 0xff
};

const uint8_t DoubleWideLookup[16] = {
	0x00,
	0x03,
	0x0c,
	0x0f,
	0x30,
	0x33,
	0x3c,
	0x3f,
	0xc0,
	0xc3,
	0xcc,
	0xcf,
	0xf0,
	0xf3,
	0xfc,
	0xff
};

const char OctopusherTitleScreen2600Graphics[192 * 9] = {
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x71,0xdf,0x77,0x57,0x4b,0xde,
0x0, 0x0, 0x0,0x71,0xdf,0x77,0x57,0x4b,0xde,
0x0, 0x0, 0x0,0x8a,0x44,0x55,0x54,0x4a,0x11,
0x0, 0x0, 0x0,0x8a,0x44,0x55,0x54,0x4a,0x11,
0x0, 0x0, 0x0,0x8a,0x4,0x57,0x57,0x7b,0x91,
0x0, 0x0, 0x0,0x8a,0x4,0x57,0x57,0x7b,0x91,
0x0, 0x0, 0x0,0x8a,0x4,0x54,0x51,0x4a,0x11,
0x0, 0x0, 0x0,0x8a,0x4,0x54,0x51,0x4a,0x11,
0x0, 0x0, 0x0,0x8a,0x4,0x74,0x77,0x4a,0x1e,
0x0, 0x0, 0x0,0x8a,0x4,0x74,0x77,0x4a,0x1e,
0x0, 0x0, 0x0,0x8a,0x4,0x0,0x0,0x4a,0x14,
0x0, 0x0, 0x0,0x8a,0x4,0x0,0x0,0x4a,0x14,
0x0, 0x0, 0x80,0x8a,0x40,0x0,0x0,0x2,0x12,
0x0, 0x0, 0x80,0x8a,0x40,0x0,0x0,0x2,0x12,
0x0, 0x0, 0xc0,0x89,0xc0,0x0,0x0,0x3,0xd2,
0x0, 0x0, 0xc0,0x89,0xc0,0x0,0x0,0x3,0xd2,
0x0, 0x0, 0xe0,0x88,0x0,0x0,0x0,0x0,0x11,
0x0, 0x0, 0xe0,0x88,0x0,0x0,0x0,0x0,0x11,
0x0, 0x0, 0xe0,0x70,0x0,0x0,0x0,0x0,0x11,
0x0, 0x0, 0xe0,0x70,0x0,0x0,0x0,0x0,0x11,
0x0, 0x0, 0xe0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0xe0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0xf0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0xf0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0xf0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0xf0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0xf0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0xf0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0xf0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0xf0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0xf0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0xf0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0xf8,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0xf8,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0xf8,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0xf8,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0xf8,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0xf8,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0xf8,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0xf8,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0xf8,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0xf8,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0xf8,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0xf8,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0xf8,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0xf8,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0xd8,0x0,0xf,0x0,0x0,0xf0,0x0,
0x0, 0x0, 0xd8,0x0,0xf,0x0,0x0,0xf0,0x0,
0x0, 0x0, 0xd8,0x0,0xf,0x0,0x0,0xf0,0x0,
0x0, 0x0, 0xd8,0x0,0xf,0x0,0x0,0xf0,0x0,
0x0, 0x0, 0x98,0x0,0xf,0xf0,0xf,0xf0,0x0,
0x0, 0x0, 0x98,0x0,0xf,0xf0,0xf,0xf0,0x0,
0x0, 0x0, 0x98,0x0,0xf,0xf0,0xf,0xf0,0x0,
0x0, 0x0, 0x98,0x0,0xf,0xf0,0xf,0xf0,0x0,
0x0, 0x0, 0x99,0x0,0xf,0xf0,0xf,0xf0,0x0,
0x0, 0x0, 0x99,0x0,0xf,0xf0,0xf,0xf0,0x0,
0x0, 0x0, 0x9b,0x0,0xf,0xf0,0xf,0xf0,0x0,
0x0, 0x0, 0x9b,0x0,0xf,0xf0,0xf,0xf0,0x0,
0x0, 0x0, 0x9a,0x0,0xf,0xf0,0xf,0xf0,0x0,
0x0, 0x0, 0x9a,0x0,0xf,0xf0,0xf,0xf0,0x0,
0x0, 0x0, 0xba,0x0,0x0,0xf0,0xf,0x0,0x0,
0x0, 0x0, 0xba,0x0,0x0,0xf0,0xf,0x0,0x0,
0x0, 0x0, 0xbb,0x0,0x0,0xf0,0xf,0x0,0x0,
0x0, 0x0, 0xbb,0x0,0x0,0xf0,0xf,0x0,0x0,
0x0, 0x0, 0xfb,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0xfb,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0xfb,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0xfb,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x1, 0xf1,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x1, 0xf1,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x1, 0xf1,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x1, 0xf1,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x1, 0xf1,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x1, 0xf1,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x1, 0xf1,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x1, 0xf1,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x1, 0xe1,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x1, 0xe1,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x71, 0xe1,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x71, 0xe1,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0xf9, 0xe3,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0xf9, 0xe3,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0xf9, 0xe7,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0xf9, 0xe7,0x0,0x0,0x0,0x0,0x0,0x0,
0x80, 0xfc, 0xff,0x0,0x0,0x0,0x0,0x0,0x0,
0x80, 0xfc, 0xff,0x0,0x0,0x0,0x0,0x0,0x0,
0x80, 0xfc, 0xff,0x0,0x0,0x0,0x0,0x0,0x0,
0x80, 0xfc, 0xff,0x0,0x0,0x0,0x0,0x0,0x0,
0xc0, 0x9e, 0xff,0x0,0x0,0x0,0x0,0x0,0x0,
0xc0, 0x9e, 0xff,0x0,0x0,0x0,0x0,0x0,0x0,
0xc0, 0xe, 0xf6,0x0,0x0,0x0,0x0,0x0,0x0,
0xc0, 0xe, 0xf6,0x0,0x0,0x0,0x0,0x0,0x0,
0x40, 0xf, 0xfa,0x0,0x0,0x0,0x0,0x0,0x0,
0x40, 0xf, 0xfa,0x0,0x0,0x0,0x0,0x0,0x0,
0x40, 0x7, 0xfc,0x0,0x0,0x0,0x0,0x0,0x0,
0x40, 0x7, 0xfc,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x7, 0xdf,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x7, 0xdf,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x7, 0xef,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x7, 0xef,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x3, 0xf7,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x3, 0xf7,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x3, 0xfb,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x3, 0xfb,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x63, 0xff,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x63, 0xff,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0xf1, 0xfd,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0xf1, 0xfd,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0xf9, 0xbe,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0xf9, 0xbe,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0xb8, 0xef,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0xb8, 0xef,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x1c, 0xd7,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x1c, 0xd7,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0xf, 0xff,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0xf, 0xff,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0xf, 0xfb,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0xf, 0xfb,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x7, 0xff,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x7, 0xff,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x3, 0xfd,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x3, 0xfd,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x3, 0x7f,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x3, 0x7f,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x1, 0x76,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x1, 0x76,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x6,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x6,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x3,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x3,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x3,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x3,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x3,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x3,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x3,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x3,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x23,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x23,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x36,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x36,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x3e,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x3e,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x1e,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x1e,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x1c,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x1c,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x8,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x8,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0, 0x0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0
};

class ConfigEntry {
public:
	char * name;
	const uint8_t initial;
	uint8_t* current;
	ConfigEntry(char* n, uint8_t i, uint8_t* c) : name(n), initial(i), current(c) {}
};

class LiveConfig {
public:
	int count;
	ConfigEntry* entries;
	uint8_t prev_joystick = 0;
	int entry_index = 0;
	int digit_index = 0;
	char line[18] = { 0 };
	int frame_count = 0;
	void HandleInput(uint8_t joystick) {
		if ((joystick & 0x8)==0 && (prev_joystick & 0x8)) {
			// right
			digit_index++;
			if (digit_index > 1)
			{
				digit_index = 0;
				entry_index++;
				if (entry_index >= count)
				{
					entry_index = 0;
				}
			}
		}
		else if ((joystick & 0x4) == 0 && (prev_joystick & 0x4)) {
			// left
			digit_index--;
			if (digit_index < 0)
			{
				digit_index = 1;
				entry_index--;
				if (entry_index < 0)
				{
					entry_index = count - 1;
				}
			}
		}
		else if ((joystick & 0x1) == 0 && (prev_joystick & 0x1)) {
			// up
			int shift = 4 * (1 - digit_index);
			//uint8_t mask = 0xf << shift;
			uint8_t inc = 1 << shift;
			uint8_t cur = *entries[entry_index].current;
			*entries[entry_index].current = cur + inc; // (cur & ~mask) | (((cur & mask) + inc) & mask);
		}
		else if ((joystick & 0x2) == 0 && (prev_joystick & 0x2)) {
			int shift = 4 * (1 - digit_index);
			// down
			//uint8_t mask = 0xf << shift;
			uint8_t inc = 0x1 << shift;
			uint8_t cur = *entries[entry_index].current;
			*entries[entry_index].current = cur - inc; // (cur & ~mask) | (((cur & mask) + inc) & mask);
		}
		prev_joystick = joystick;

		for (int i = 0; i < (int)(sizeof(line)/sizeof(line[0])); i++)
		{
			line[i] = ' ';
		}

		int ix = 0;
		while (true) {
			char c = entries[entry_index].name[ix];
			line[ix++] = c;
			if ((c == ' ') || (ix >= 14))
			{
				break;
			}
		}
		for (int i = 0; i < 2; i++)
		{
			int shift = 4 * (1 - i);
			line[ix++] = ((*entries[entry_index].current >> shift) & 0xf);
		}

		PrintText(line, 0);
		if (frame_count < 30) {
			InvertCharacter(0, ix - 2 + digit_index);
		}
		frame_count--;
		if (frame_count < 0)
		{
			frame_count = 60;
		}
	}
};

enum BubbleState {
	LargeBubble,
	MediumBubble,
	SmallBubble,
	Popping0,
	Popping1,
	Popping2,
	PoppedPoints,
	Popped,
};

BoundingBox<FP32> LargeBubbleHitbox(0,0,0,8,0,14);
BoundingBox<FP32> MediumBubbleHitbox(0,0,1,7,1,13);
BoundingBox<FP32> SmallBubbleHitbox(0,0,2,6,2,12);
BoundingBox<FP32>* BubbleHitBoxes[] = { &LargeBubbleHitbox, &MediumBubbleHitbox, &SmallBubbleHitbox };

struct Bubble {
	int x;
	BubbleState state;
	int frames_remaining;
	BoundingBox<FP32>* hit_box;
	bool points_awarded;
};

static Bubble bubbles[16];

enum MonkeyState {
	Standing,
	Walking,
	Jumping,
	FanSmacked,
	HoppingOntoPost,
	WalkingToEdge,
	HoppingOntoMattress,
	Dead,
};

class Monkey {
public:
	BoundingBox<FP32> hit_box;
	uint8_t color;
	FP32 x;
	FP32 y;
	FP32 velocity_x;
	FP32 velocity_y;
	int score;
	MonkeyState state;
	int frame;
	int animation;
	int lives;
	bool face_left;
	bool bottomed_out;
};

class Fly {
public:
	BoundingBox<FP32> hit_box;
	FP32 x;
	FP32 y;
	FP32 velocity_x;
	FP32 velocity_y;
	int frames_remaining;
	int score;
	bool face_left;
	bool is_alive;
};

class MonkeyArm {
public:
	BoundingBox<FP32> hit_box;
	FP32 y;
	int frames_remaining;
	bool rising;
	bool closed;
};

__attribute__((section(".noinit")))
static uint8_t bitmap[192 * 80];

__attribute__((section(".noinit")))
static uint8_t playfieldBuffer[193*5]; // 00001111 11112222 22220000 11111111 22222222
__attribute__((section(".noinit")))
static uint8_t colupfBuffer[193];
__attribute__((section(".noinit")))
static uint8_t grp0Buffer[193];
__attribute__((section(".noinit")))
static uint8_t colup0Buffer[193];
__attribute__((section(".noinit")))
static uint8_t grp1Buffer[193];
__attribute__((section(".noinit")))
static uint8_t colup1Buffer[193];

static char scoreText[18] = { 0, 0, 0, 0, 16, 18, 18, 18, 16, 16, 18, 18, 18, 16, 0, 0, 0, 0 };
void setPF(int x, int y);
void DrawFlyRegion(int& line, int height, int fly_x, int fly_y, int fly_frame);
void PositionObject(int& line, int x, uint8_t resp, uint8_t hm);
void move_monkey(uint8_t joy, Monkey* monkey);
int title_screen();
void game_over_screen();
void show_credits();
void show_previews();
void play_game(int player_count);
void RenderWideBed(int& line, Monkey* jumping_monkey, Monkey* standing_monkey);
void RenderMediumBed(int& line, Monkey* jumping_monkey, Monkey* standing_monkey);
void RenderNarrowBed(int& line, Monkey* jumping_monkey, Monkey* standing_monkey);
void fade_palette(uint8_t fade_level);
void RenderZoomScreen(int& line, int line_limit);
void DrawBouncingScene();
void DrawZoomScene();
void DrawChallengeScreen();
void RenderChallengeScreen();
void DrawMattress();
void DrawMonkeys();
void DrawScores();
void SetVariablesFromState();
void ApplyGravity();
void place_monkey_on_post();
void writeAudio30();
void next_audio_frame();
void moveFly(uint8_t joy);

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

static track_player audio_player0;
static track_player audio_player1;
static int high_score = 0;

extern "C" int elf_main(uint32_t * args)
{
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
	for (size_t i = 0; i < sizeof(playfieldBuffer) / sizeof(playfieldBuffer[0]); i++)
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


	while (true) {
		int menu_selection = title_screen();
		switch (menu_selection)
		{
		case 0:
		case 1:
		case 2:
			play_game(menu_selection);
			break;
		case 3:
			show_credits();
			break;
		case 4:
			show_previews();
			break;

		default:
			play_game(1);
		}
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="faded_color"></param>
/// <param name="original_color"></param>
/// <param name="level">0-black, 1-16 darkest to brightest luminance</param>
void fade_color(uint8_t& faded_color, uint8_t original_color, uint8_t level)
{
	if (level == 0)
	{
		faded_color = 0;
	}
	else
	{
		faded_color = ((original_color & 0xf) < level) ? original_color : (original_color & 0xf0) | (uint8_t)(level - 1);
	}
}

void fade_palette(uint8_t fade_level) {
	// Do fading first so it takes effect everywhere this frame
	fade_color(ColuCeiling, InitialColuCeiling, fade_level);
	fade_color(ColuWall, shake_frames_remaining ? ColuRedWall : InitialColuWall, fade_level);
	fade_color(ColuFloor, InitialColuFloor, fade_level);
	fade_color(ColuSheet, InitialColuSheet, fade_level);
	fade_color(ColuMattress, InitialColuMattress, fade_level);
	fade_color(ColuFlyWing, InitialColuFlyWing, fade_level);
	fade_color(ColuFlyBody, InitialColuFlyBody, fade_level);
	fade_color(ColuPillow, InitialColuPillow, fade_level);
	fade_color(ColuHeadboard, InitialColuHeadboard, fade_level);
	fade_color(ColuBedPost, InitialColuBedPost, fade_level);
	fade_color(ColuFanBlade, InitialColuFanBlade, fade_level);
	fade_color(ColuP0Monkey, InitialColuP0Monkey, fade_level);
	fade_color(ColuP1Monkey, InitialColuP1Monkey, fade_level);

}

enum PlayState {
Wide,
Medium,
Narrow,
};

enum PlaySubState {
	NotPlaying, // Hold monkeys in place for title screen and level transitions
	Playing,
	FlyExit,
	MonkeyLanding,
	FadingOut,
	ZoomingIn,
	CountingDown,
	Challenge,
	ZoomingOut,
	FadingIn,
};

bool challenge_mode = false;
bool show_zoom_screen = false;
bool jump_in_progress = true;
bool show_challenge_wall = false;
bool bonus_enabled = true;
bool jumping_enabled = true;
bool fly_spawn_enabled = true;
bool banana_shown = false;
int banana_cooldown = 5 * 60;
int min = 500;
int max = 0;
bool fly_top_spawned = true;
bool fly_bot_spawned = true;
int fly_top_x = 20;
int fly_top_y = 2;
size_t fly_top_index = 0;
int fly_bot_x = 8;
int fly_bot_y = 20;
int frame = 0;
int fanFrame = 0;
size_t fly_loop_index = 0;
track_player sfx_player;
track_player* chan1_player;
int sfx_frames_remaining = 0;
uint8_t sine_frame = 0;
FP32 sine_hpos = 20;
Monkey monkey_0 = { .hit_box = BoundingBox<FP32>(0,0,0,8,0,12), .color = ColuP0Monkey, .x = 40, .y = 50, .velocity_x = 0, .velocity_y = 0, .score = 0, .state = Standing, .frame = 0, .animation = 0, .lives = 3, .face_left = false, .bottomed_out = false };
Monkey monkey_1 = { .hit_box = BoundingBox<FP32>(0,0,0,8,0,12), .color = ColuP1Monkey, .x = 120, .y = 129, .velocity_x = 0, .velocity_y = 0, .score = 0, .state = Standing, .frame = 0,.animation = 0, .lives = 3, .face_left = true, .bottomed_out = false };
Monkey* jumping_monkey = &monkey_0;
Monkey* standing_monkey = &monkey_1;
Monkey* p0_monkey = &monkey_0;
Monkey* p1_monkey = &monkey_1;
FP32 GravityAscend = fp32(0.24);
FP32 GravityFall = fp32(0.5);
FP32 MattressFriction = fp32(-0.3);
BoundingBox<FP32> fly_top_hit_box = BoundingBox<FP32>(1, 1, 0, 2, 0, 2);
BoundingBox<FP32> fly_bot_hit_box = BoundingBox<FP32>(1, 1, 0, 2, 0, 2);
BoundingBox<FP32> banana_hit_box = BoundingBox<FP32>(77, 33, 0, 7, 0, 13);
uint8_t fade_level = 16;
int bed_left = 40; 
int bed_right = 124;
bool button_down_event = false;
uint8_t but0 = 0, prev_but0 = 0;
PlayState play_state = Wide;
PlaySubState play_substate = Playing;
uint8_t joysticks = 0;
auto render_bed = RenderWideBed;
PlayState max_play_state_reached = Narrow; // TODO Wide;
int room_height = 175;
FP32 wave_length = 80;
Fly fly = { .hit_box = BoundingBox<FP32>(0,0,0,8,4,10), .x = 40, .y = 50, .velocity_x = 0, .velocity_y = 0, .score = 0, .face_left = false, .is_alive = true };
MonkeyArm left_arm = { .hit_box = BoundingBox<FP32>(32,39,10,20,16+32,44+32), .y = 0, .frames_remaining = 0, .rising = false, .closed = true };
MonkeyArm right_arm = { .hit_box = BoundingBox<FP32>(96,39,10,20,16+32,44+32), .y = 0, .frames_remaining = 0, .rising = false, .closed = true };

BoundingBox<FP32> fan_blade_hit_boxes[7] = {
	BoundingBox<FP32>(60, 4, 0, 44, 0, 11),
	BoundingBox<FP32>(60, 4, 8, 36, 0, 11),
	BoundingBox<FP32>(60, 4, 12, 32, 0, 11),
	BoundingBox<FP32>(60, 4, 16, 28, 0, 11),
	BoundingBox<FP32>(60, 4, 12, 32, 0, 11),
	BoundingBox<FP32>(60, 4, 8, 36, 0, 11),
	BoundingBox<FP32>(60, 4, 0, 44, 0, 11),
};

// For tuning purposes only
ConfigEntry config_entries[] = {
	//ConfigEntry("Zoom Level "               ,0 		,&zoom_level),
	//ConfigEntry("ColuWall "               ,ColuWall 		,&ColuWall),
	//ConfigEntry("ColuSheet "              ,ColuSheet 	,&ColuSheet),
	//ConfigEntry("ColuMattress "           ,ColuMattress ,&ColuMattress),
	//ConfigEntry("ColuFlyWing "            ,ColuFlyWing	,&ColuFlyWing),
	//ConfigEntry("ColuFlyBody "            ,ColuFlyBody	,&ColuFlyBody),
	//ConfigEntry("ColuPillow "             ,ColuPillow  	,&ColuPillow),
	//ConfigEntry("ColuHeadboard "          ,ColuHeadboard,&ColuHeadboard),
	//ConfigEntry("ColuBedPost "            ,ColuBedPost 	,&ColuBedPost),
	//ConfigEntry("ColuFanBlade "           ,ColuFanBlade ,&ColuFanBlade),
	//ConfigEntry("ColuP0Monkey "           ,ColuP0Monkey ,&ColuP0Monkey),
	//ConfigEntry("ColuP1Monkey "           ,ColuP1Monkey	,&ColuP1Monkey),
};
LiveConfig live_config = { .count = (int)(sizeof(config_entries) / sizeof(config_entries[0])), .entries = config_entries };


void play_game(int player_count){
	next_challenge_score = ChallengeThreshold;
	button_down_event = false;
	but0 = 0;
	prev_but0 = 0;
	play_substate = ZoomingIn;
	joysticks = 0;
	monkey_0.lives = 3;
	monkey_0.score = 0;
	monkey_1.lives = 3;
	monkey_1.score = 0;
	// Render loop
	while (true) {
		frame++;
		if (jumping_monkey->state == Dead)
			break;
		//Check for state changes
		switch (play_substate) {
		case NotPlaying:
			break;
		case Playing:
		{
			auto hs = monkey_0.score + monkey_1.score;
			if (hs > next_challenge_score)
				play_substate = FlyExit;
			break; 
		}
		case FlyExit:
			if (!fly_top_spawned && !fly_bot_spawned)
			{
				play_substate = MonkeyLanding;
			}
			break;
		case MonkeyLanding:
			if (!jump_in_progress)
				play_substate = FadingOut;
			break;
		case FadingOut:
			if (fade_level == 0)
			{
				play_substate = ZoomingIn;
				zoom_level = 0;
				countdown_frames_remaining = 0;
				challenge_player = 0;
			}
			break;
		case ZoomingIn:
		{
			if (zoom_level == 17) {
				play_substate = CountingDown;
				countdown_frames_remaining = 60 * 3;
				countdown_index = 0;
			}
		}
		case CountingDown:
		{
			countdown_frames_remaining--;
			if (countdown_frames_remaining == 60 * 2) {
				countdown_index = 1;
			}
			else if (countdown_frames_remaining == 60) {
				countdown_index = 2;
			}
			else if (countdown_frames_remaining == 0) {
				play_substate = Challenge;
				challenge_frames_remaining = ChallengeFrames;
				bubbleDistance = 0;
				bubble_index = 0;
				bubble_offset = 5;
				for (int i = 0; i < 16; i++)
				{
					if (i > 10)
					{
						auto size = randint() & 3;
						if (size > 2)
							size = 0;
						bubbles[i].state = (BubbleState)size;
						bubbles[i].hit_box = BubbleHitBoxes[size];
					}
					else
					{
						bubbles[i].state = Popped;
					}
					bubbles[i].x = BubbleStartPositions[i];
					bubbles[i].points_awarded = false;
				}
				fly.is_alive = true;
				fly.x = 80;
				fly.y = 80;
				left_arm.y = 0;
				left_arm.frames_remaining = 0;
				left_arm.rising = true;
				left_arm.closed = false;
				right_arm.y = 0;
				right_arm.frames_remaining = 64;
				right_arm.rising = true;
				right_arm.closed = false;
			}
			break;
		}
		case Challenge:
		{
			challenge_frames_remaining--;
			if (challenge_frames_remaining <= 0)
			{
				if(player_count < 2 || challenge_player > 0)
					play_substate = ZoomingOut;
				else {
					challenge_player = 1;
					zoom_level = 16;
					play_substate = ZoomingIn;
				}
			}
			else
			{
				moveFly((challenge_player > 0) ? joysticks & 0xf : joysticks >> 4);
			}
			break;
		}
		case ZoomingOut:
			if (zoom_level == 0)
			{
				next_challenge_score = monkey_0.score + monkey_1.score + ChallengeThreshold;

				play_substate = FadingIn;
				fade_level = 0;
				if (play_state == Wide)
					max_play_state_reached = play_state = Medium;
				else if (play_state == Medium)
					max_play_state_reached = play_state = Narrow;
				place_monkey_on_post();
				standing_monkey->face_left = !jumping_monkey->face_left;
				standing_monkey->x = 88;
				standing_monkey->state = Standing;
			}
			break;
		case FadingIn:
			if (fade_level == 16)
			{
				play_substate = Playing;
				fly_top_spawned = fly_bot_spawned = true;
			}
			break;
		}

		SetVariablesFromState();


		fade_palette(fade_level);

		next_audio_frame();

		if (challenge_mode) {
			DrawChallengeScreen();
		}
		else if (show_zoom_screen) {
			DrawZoomScene();
		}
		else {
			DrawBouncingScene();
		}

		DrawScores();

		// Update High Score
		if (high_score < monkey_0.score)
		{
			high_score = monkey_0.score;
		}
		if (high_score < monkey_1.score)
		{
			high_score = monkey_1.score;
		}

		// Render
		if (challenge_mode)
		{
			RenderChallengeScreen();
		}
		else
		{
			vcsEndOverblank();
			vcsSta3(WSYNC);
			writeAudio30();
			vcsSta3(WSYNC); vcsSta3(WSYNC);


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

			DisplayText(ColuScoreBackground, 1);

			int line = 0;

			if (show_zoom_screen) {
				RenderZoomScreen(line, 175);
			}
			else
			{
				room_height = 175;
				// Shake screen for fan strikes
				if (shake_frames_remaining & 0x4)
				{
					for (int i = 0; i < 4; i++)
					{
						vcsSta3(WSYNC);
						room_height--;
						vcsSta3(HMOVE);
						vcsLda2(0);
						vcsSta3(GRP0);
						vcsSta3(GRP1);
						vcsSta3(PF0);
						vcsSta3(PF1);
						vcsSta3(PF2);
						vcsSta3(ENAM0);
						vcsSta3(ENAM1);
						vcsSta3(ENABL);
						vcsSta3(COLUBK);
					}
				}

				vcsSta3(WSYNC);

				// Ceiling
				vcsSta3(HMOVE);
				vcsLda2(ColuCeiling);
				vcsSta3(COLUBK);
				vcsLda2(0);
				vcsSta3(GRP0);
				vcsSta3(GRP1);
				vcsSta3(PF0);
				vcsSta3(PF1);
				vcsSta3(PF2);
				vcsSta3(ENAM0);
				vcsSta3(ENAM1);
				vcsSta3(ENABL);
				vcsSta3(NUSIZ0);
				vcsLdy2(ColuFanBlade);
				vcsWrite5(COLUP0, jumping_monkey->color);
				vcsSta3(RESPONE); // 42 cycles before this
				vcsSty3(COLUPF);
				vcsNop2n(7);
				vcsWrite5(NUSIZ1, 0x30);
				vcsWrite5(HMP1, 0x00);
				vcsNop2();
				line++;
				//
				vcsSta3(HMOVE);
				vcsWrite5(NUSIZ0, 0);
				vcsNop2n(21);
				vcsLdy2(ColuWall);
				vcsSta4(HMCLR);
				vcsSta3(WSYNC);
				line++;
				PositionObject(line, jumping_monkey->x.Round(), RESP0, HMP0);

				// Fan region
				while (line < (show_challenge_wall ? 29 + 38 : 29))
				{
					vcsSta3(HMOVE);
					vcsSty3(COLUBK);
					vcsWrite5(GRP1, grp1Buffer[line]);
					vcsWrite5(GRP0, grp0Buffer[line]);
					vcsWrite5(PF0, ReverseByte[playfieldBuffer[line * 5] >> 4]);
					vcsWrite5(PF1, (playfieldBuffer[line * 5] << 4) | (playfieldBuffer[line * 5 + 1] >> 4));
					vcsWrite5(COLUP1, colup1Buffer[line]);
					vcsWrite5(COLUPF, colupfBuffer[line]);
					vcsWrite5(PF2, ReverseByte[(uint8_t)((playfieldBuffer[line * 5 + 1] << 4) | (playfieldBuffer[line * 5 + 2] >> 4))]);
					vcsWrite5(PF0, ReverseByte[playfieldBuffer[line * 5 + 2]]);
					vcsWrite5(PF1, playfieldBuffer[line * 5 + 3]);
					vcsWrite5(PF2, ReverseByte[playfieldBuffer[line * 5 + 4]]);
					vcsSta3(HMCLR);
					vcsJmp3();
					vcsSta3(WSYNC);
					line++;
				}

				// Draw flies during normal play and when they're exiting, otherwise section above will fill this space
				if (!show_challenge_wall) {
					fly_top_hit_box.Y = fly_top_y + line;
					DrawFlyRegion(line, 14, fly_top_x, fly_top_y, frame & 1);
					fly_bot_hit_box.Y = fly_bot_y + line;
					DrawFlyRegion(line, 24, fly_bot_x, fly_bot_y, frame & 1);
				}

				render_bed(line, jumping_monkey, standing_monkey);
			}
		}

		vcsWrite5(VBLANK, 2);
		joysticks = vcsRead4(SWCHA);
		vcsNop2();
		but0 = vcsRead4(INPT4);
		vcsNop2();
		uint8_t but1 = vcsRead4(INPT5);
		vcsStartOverblank();
		if (!challenge_mode)
		{
			move_monkey(joysticks >> 4, p0_monkey);
			move_monkey(joysticks & 0xf, p1_monkey);
		}
		button_down_event = (((but0 & 0x80) == 0) && (prev_but0 & 0x80));
		prev_but0 = but0;
	}
	
	game_over_screen();
}

int bitmap_screen(bool is_title_screen) {
	int bitmap_frame = 0;
	button_down_event = false;
	but0 = 0;
	prev_but0 = 0;

	if (is_title_screen) {
		play_state = Wide;
		play_substate = NotPlaying;
		fade_palette(16);
		jumping_monkey = &monkey_0;
		standing_monkey = &monkey_1;
		monkey_1.state = Standing;
		monkey_1.face_left = true;
		monkey_1.x = 100;
		monkey_1.y = 145;
	}
	int menu_selection = 1;
	for (uint32_t i = 0; i < sizeof(bitmap) / sizeof(bitmap[0]); i++)
	{
		bitmap[i] = 0;
	}
	joysticks = 0;
	uint8_t prev_joy = 0;
	while (true)
	{
		int ix;
		int line = 0;
		if (is_title_screen) {
			ix = 6 * 19; // vertical position of title art
			for (unsigned int i = 0; i < sizeof(TitleArtGraphics[0]); i++)
			{
				bitmap[ix++] = TitleArtGraphics[(frame >> 3 & 1)][i];
			}

			ix = 6 * 54; // vertical gap before selection menu
			for (unsigned int i = 0; i < sizeof(MenuOptionsGraphics[0]); i++)
			{
				bitmap[ix++] = MenuOptionsGraphics[menu_selection][i];
			}
			frame++;
			place_monkey_on_post();
		}
		else
		{
			frame = 1;
			bitmap_frame++;
			ix = 6 * 20; // vertical position of Game Over sprite
			for (unsigned int i = 0; i < sizeof(GameOverGraphics); i++)
			{
				bitmap[ix++] = GameOverGraphics[i];
			}
		}

		next_audio_frame();

		SetVariablesFromState();
		ColuWall = InitialColuWall;
		ColuFloor = InitialColuFloor;

		// preclear buffers
		for (int i = 0; i < 192; i++)
		{
			grp0Buffer[i] = 0;
			grp1Buffer[i] = 0;
		}

		DrawBouncingScene();

		if (is_title_screen || bitmap_frame & 0x40) {
			char high_score_text[19] = "High Score:  00000";
			int right_score = high_score;
			for (int i = 0; i < 5; i++)
			{
				high_score_text[17 - i] = (right_score % 10) & 0xf;
				right_score /= 10;
			}
			PrintText(high_score_text, 0);
		}
		else {
			DrawScores();
		}

		ix = 18;
		vcsEndOverblank();
		writeAudio30();
		vcsWrite5(COLUP0, 0);
		vcsSta3(COLUP1);
		vcsSta3(PF0);
		vcsSta3(PF1);
		vcsSta4(PF2);

		vcsSta3(WSYNC);
		vcsSta3(WSYNC);
		vcsJmp3();
		vcsNop2n(34);
		vcsWrite5(VBLANK, 0);

		// High Score
		DisplayText(ColuScoreBackground, 1);
		vcsSta3(WSYNC);

		//Ceiling
		vcsSta3(HMOVE);
		vcsWrite5(COLUBK, ColuCeiling);
		vcsSta3(WSYNC);
		line++;

		PositionObject(line, 58, RESP0, HMP0);
		PositionObject(line, 66, RESPONE, HMP1);

		vcsSta3(HMOVE);
		vcsWrite5(COLUBK, ColuWall);
		vcsWrite5(GRP0, 0);
		vcsSta3(GRP1);
		vcsSta3(PF0);
		vcsSta3(PF1);
		vcsSta3(PF2);
		vcsWrite5(COLUP0, FanChasisColu[18]);
		vcsSta3(COLUP1);
		vcsWrite5(VDELP0, 1);
		vcsSta3(VDELP1);
		vcsSta3(HMCLR);
		vcsSta3(WSYNC);
		line++;

		for (int i = 0; i < 60; i++)
		{
			vcsSta3(HMOVE);
			if (i == 50) {
				vcsWrite5(COLUP0, 0);
				vcsSta3(COLUP1);
				ix += 6;
			}
			else {
				vcsWrite5(COLUBK, ColuWall);
				vcsWrite5(GRP0, bitmap[ix++]);
				vcsWrite5(GRP1, bitmap[ix++]);
				vcsWrite5(GRP0, bitmap[ix++]);
				vcsJmp3();
				vcsJmp3();
				vcsNop2n(4);
				vcsLda2(bitmap[ix++]);
				vcsLdx2(bitmap[ix++]);
				vcsLdy2(bitmap[ix++]);
				vcsSta3(GRP1);
				vcsStx3(GRP0);
				vcsSty3(GRP1);
				vcsSty3(GRP0);
			}
			vcsSta3(WSYNC);
			line++;
		}

		vcsSta3(HMOVE);
		vcsJmp3();

		vcsLda2(0);
		vcsSta3(GRP0);
		vcsSta3(GRP1);
		vcsSta3(NUSIZ0);
		vcsWrite5(COLUP0, jumping_monkey->color);
		vcsWrite5(NUSIZ1, 0x30);
		vcsWrite5(VDELP0, 0);
		vcsWrite5(VDELP1, 0);
		vcsSta3(WSYNC);
		line++;

		vcsSta3(HMOVE);
		vcsSta3(WSYNC);
		line++;

		PositionObject(line, jumping_monkey->x.Round(), RESP0, HMP0);
		render_bed(line, jumping_monkey, standing_monkey);
		vcsWrite5(VBLANK, 2);
		uint8_t joy = vcsRead4(SWCHA);
		vcsNop2();
		uint8_t but0 = vcsRead4(INPT4);
		vcsStartOverblank();
		if (is_title_screen) {
			if (((joy & 0x40) == 0) && (prev_joy & 0x40)) {
				// left
				if (menu_selection <= 0)
				{
					menu_selection = sizeof(MenuOptionsGraphics) / sizeof(MenuOptionsGraphics[0]);
				}
				menu_selection--;
				init_audio_player(&sfx_player, 1, &SfxBounce);
				sfx_frames_remaining = SfxBounce.percussions[0].length;
			}
			if (((joy & 0x80) == 0) && (prev_joy & 0x80)) {
				// right
				menu_selection++;
				if (menu_selection >= (int)(sizeof(MenuOptionsGraphics) / sizeof(MenuOptionsGraphics[0])))
				{
					menu_selection = 0;
				}
				init_audio_player(&sfx_player, 1, &SfxBounce);
				sfx_frames_remaining = SfxBounce.percussions[0].length;
			}
			if (((joy & 0x20) == 0) && (prev_joy & 0x20)) {
				// down
				switch (play_state) {
				case Narrow:
					play_state = Medium;
					break;
				case Medium:
					play_state = Wide;
					break;
				default:
					break;
				}
			}
			if (((joy & 0x10) == 0) && (prev_joy & 0x10) && (play_state != max_play_state_reached)) {
				// up
				switch (play_state) {
				case Wide:
					play_state = Medium;
					break;
				case Medium:
					play_state = Narrow;
					break;
				default:
					break;
				}
			}
		}
		prev_joy = joy;

		if (((but0 & 0x80) == 0) && (prev_but0 & 0x80))
		{
			return menu_selection;
		}
		prev_but0 = but0;
	}
}

int title_screen() {
	return bitmap_screen(true);
}

void game_over_screen() {
	bitmap_screen(false);
}

void show_credits() {
	uint8_t prev_but0 = 0;
	while (true)
	{
		next_audio_frame();
		int text_line = 0;
		PrintText("Design            ", text_line++);
		PrintText("  Mathew Halpern  ", text_line++);
		PrintText("                  ", text_line++);
		PrintText("Programming       ", text_line++);
		PrintText("  Zack Scolaro    ", text_line++);
		PrintText("                  ", text_line++);
		PrintText("TIA Music         ", text_line++);
		PrintText("  Marco Johannes  ", text_line++);
		PrintText("                  ", text_line++);
		PrintSmall("\"Monkeys Spinning Monkeys\" licensed ", text_line++, 0, 36);
		PrintSmall("by Incopetech Inc. (c) 2023         ", text_line++, 0, 36);

		vcsEndOverblank();
		vcsSta3(WSYNC);
		writeAudio30();
		vcsSta3(WSYNC);
		vcsLda2(ColuWall);
		vcsSta3(COLUBK);

		vcsSta3(WSYNC);
		vcsWrite5(COLUP0, 0x0f);
		vcsSta3(COLUP1);
		vcsWrite5(PF0, 0);
		vcsSta3(PF1);
		vcsSta3(PF2);
		vcsJmp3();
		vcsSta3(HMCLR);

		vcsSta3(WSYNC);
		vcsNop2n(34);
		vcsJmp3();
		vcsWrite5(VBLANK, 0);

		DisplayText(ColuWall, 11);

		for (int i = 0; i < 5; i++)
		{
			vcsSta3(HMOVE);
			vcsJmp3();
			vcsSta3(WSYNC);
		}

		vcsWrite5(VBLANK, 2);
		uint8_t but0 = vcsRead4(INPT4);
		vcsStartOverblank();
		if (((but0 & 0x80) == 0) && (prev_but0 & 0x80))
		{
			return;
		}
		prev_but0 = but0;
	}
}

static const char title_screen_2600_colubk[16] = { 0x96, 0x96, 0x98, 0x98, 0x9a, 0x9a, 0x9c, 0x9c, 0x9c, 0x9c, 0x9a, 0x9a, 0x98, 0x98, 0x96, 0x96 };
void show_previews() {
	int frameCount = 0;
	int tenthCount = 0;
	uint8_t prev_but0 = 0;
	while (true)
	{
		frameCount++;
		if (frameCount == 6)
		{
			frameCount = 0;
			tenthCount++;
		}
		next_audio_frame();

		vcsEndOverblank();
		vcsSta3(WSYNC);
		writeAudio30();
		vcsSta3(WSYNC);

		vcsSta3(WSYNC);
		vcsNop2n(3);
		vcsWrite5(NUSIZ0, 0x03);
		vcsWrite5(NUSIZ1, 0x03);
		vcsWrite5(COLUP0, 0x0f);
		vcsWrite5(COLUP1, 0x0f);
		vcsWrite5(GRP0, 0xff);
		vcsWrite5(GRP1, 0xff);
		vcsSta3(RESP0);
		vcsSta3(RESPONE);
		vcsWrite5(HMP0, 0xe0);
		vcsWrite5(HMP1, 0xf0);
		vcsWrite5(VDELP0, 0x01);
		vcsWrite5(VDELP1, 0x01);

		vcsSta3(WSYNC);
		vcsSta3(HMOVE);
		vcsWrite5(CTRLPF, 0x01);
		vcsWrite5(COLUPF, 0x80);
		vcsNop2n(26);
		vcsSta3(HMCLR);
		vcsJmp3();
		vcsWrite5(VBLANK, 0);

		int y = 0;
		for (int i = 0; i < 192; i++)
		{
			vcsWrite5(COLUBK, title_screen_2600_colubk[0xf & (i + tenthCount)]);
			vcsWrite5(PF0, OctopusherTitleScreen2600Graphics[y]);
			vcsWrite5(PF1, OctopusherTitleScreen2600Graphics[y + 1]);
			vcsWrite5(PF2, OctopusherTitleScreen2600Graphics[y + 2]);
			vcsLdx2(OctopusherTitleScreen2600Graphics[y + 7]);
			vcsLdy2(OctopusherTitleScreen2600Graphics[y + 8]);
			vcsWrite5(GRP0, OctopusherTitleScreen2600Graphics[y + 3]);
			vcsWrite5(GRP1, OctopusherTitleScreen2600Graphics[y + 4]);
			vcsWrite5(GRP0, OctopusherTitleScreen2600Graphics[y + 5]);
			vcsWrite5(GRP1, OctopusherTitleScreen2600Graphics[y + 6]);
			vcsStx3(GRP0);
			vcsSty3(GRP1);
			vcsStx3(GRP0);
			vcsJmp3();
			vcsNop2n(10);
			y += 9;
		}


		vcsWrite5(VBLANK, 2);
		uint8_t but0 = vcsRead4(INPT4);
		vcsStartOverblank();
		if (((but0 & 0x80) == 0) && (prev_but0 & 0x80))
		{
			return;
		}
		prev_but0 = but0;
	}
}


void move_monkey(uint8_t joy, Monkey* monkey)
{
	switch (monkey->state) {
	case FanSmacked:
	case HoppingOntoPost:
	case WalkingToEdge:
	case HoppingOntoMattress:
	case Dead:
		return;
	default:
		break;
	}

	bool horizontal_input = false;
	if (((joy & 0x4) == 0) && monkey->x > min_monkey_x) {
		// left
		monkey->x -= 1;
		if (monkey->velocity_x > 0)
		{
			monkey->velocity_x--;
		}
		monkey->face_left = true;
		horizontal_input = true;
	}
	if (((joy & 0x8) == 0) && monkey->x < max_monkey_x) {
		// right
		monkey->x += 1;
		if (monkey->velocity_x < 0)
		{
			monkey->velocity_x++;
		}
		monkey->face_left = false;
		horizontal_input = true;
	}
	if (monkey->y < 110) {
		if (((joy & 0x1) == 0) && monkey->y > 4) {
			// up
			monkey->y -= 1;
		}
		if (((joy & 0x2) == 0) && monkey->y < 157) {
			// down
			monkey->y += 1;
		}
	}

	if(monkey->state == Walking && !horizontal_input) {
		monkey->state = Standing;
	}

	if(monkey->state == Standing && horizontal_input) {
		monkey->state = Walking;
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
void PositionObject(int& line, int x, uint8_t resp, uint8_t hm)
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
	line++;
}

void DrawFlyRegion(int& line, int height, int fly_x, int fly_y, int fly_frame) {
	PositionObject(line, fly_x, RESBL, HMBL);
	for (int i = 1; i < height; i++)
	{
		vcsSta3(HMOVE);
		vcsWrite5(GRP0, grp0Buffer[line]);
		vcsWrite5(GRP1, grp1Buffer[line]);
		vcsWrite5(COLUP1, colup1Buffer[line]);
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
		line++;
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

void DrawMonkeyArm(MonkeyArm& arm, int offset) {
	if (!arm.closed && fly.hit_box.Intersects(arm.hit_box))
	{
		challenge_frames_remaining = shake_frames_remaining = 30;
		arm.closed = true;
		fly.is_alive = false;
		init_audio_player(&sfx_player, 1, &SfxFlySquish);
		sfx_frames_remaining = SfxFlySquish.percussions[0].length;
	}
	if (arm.frames_remaining > 0) {
		arm.frames_remaining--;
	}
	else
	{
		arm.y += ArmVelocity;
		if (arm.rising) {
			if (arm.y.Round() >= 64) {
				arm.rising = false;
				arm.closed = true;
			}
		}
		else {
			if (arm.y.Round() >= 128) {
				arm.rising = true;
				arm.closed = !fly.is_alive;
				arm.frames_remaining = 64;
				arm.y = 0;
			}
		}
	}
	const uint8_t* pArmGraphics = arm.closed ? &MonkeyHandClosedGraphics[0] : &MonkeyHandOpenGraphics[0];
	arm.hit_box.Y = 136 - (FP32(Sine[arm.y.Round()], true) * 136);
	auto ix = (39 + arm.hit_box.Y.Round()) * 5 + offset;
	for (; ix < 175 * 5;)
	{
		playfieldBuffer[ix] = *pArmGraphics;
		ix += 5;
		pArmGraphics++;
	}
}

void DrawChallengeScreen() {
	// Move fly before collision detection
	fly.x += fly.velocity_x;
	if (fly.x.Round() < 8)
		fly.x = 8;
	if (fly.x.Round() > 152)
		fly.x = 152;
	fly.y += fly.velocity_y;
	if (fly.y.Round() < 2)
		fly.y = 2;
	if (fly.y.Round() > 164) {
		fly.y = 164;
	}
	auto fy = fly.y.Round();

	// Light
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			auto left = DoubleWideLookup[FanChasisGraphics[16 + i] >> 4];
			auto right = DoubleWideLookup[FanChasisGraphics[16 + i] & 0xf];
			playfieldBuffer[(i * 8 + j + 2) * 5 + 0] = 0;
			playfieldBuffer[(i * 8 + j + 2) * 5 + 1] = left >> 5;
			playfieldBuffer[(i * 8 + j + 2) * 5 + 2] = left << 3 | right >> 5;
			playfieldBuffer[(i * 8 + j + 2) * 5 + 3] = right << 3;
			playfieldBuffer[(i * 8 + j + 2) * 5 + 4] = 0;
		}
	}

	// Monkey Arms
	for (int i = 4*8*5; i < 175*5; i++)
	{
		playfieldBuffer[i] = 0;
	}
	fly.hit_box.X = fly.x;
	fly.hit_box.Y = fly.y;
	DrawMonkeyArm(left_arm, 1);
	DrawMonkeyArm(right_arm, 3);

	// Top 3 lines empty because we are positioning the fly and setting up for the next display kernel
	for (int i = 0; i < 3; i++)
	{
		grp1Buffer[i] = 0;
	}
	// See if player popped them all
	bool zoom_out_red_wall = false;
	for (int i = 0; i < 16; i++)
	{
		if (bubbles[i].points_awarded == false)
			zoom_out_red_wall = true;
	}
	if (!zoom_out_red_wall)
	{
		challenge_frames_remaining = 1;
	}
	// Animate bubbles
	int r = ((frame & 3) == 0) ? randint() : 0xffffffff;
	for (int i = 0; i < 16; i++)
	{
		switch (bubbles[i].state)
		{
		case Popping0: {
			bubbles[i].frames_remaining--;
			if (bubbles[i].frames_remaining <= 0)
			{
				bubbles[i].state = Popping1;
				bubbles[i].frames_remaining = BubblePopFrames;
			}
			break;
		}
		case Popping1: {
			bubbles[i].frames_remaining--;
			if (bubbles[i].frames_remaining <= 0)
			{
				bubbles[i].state = Popping2;
				bubbles[i].frames_remaining = BubblePopFrames;
			}
			break;
		}
		case Popping2: {
			bubbles[i].frames_remaining--;
			if (bubbles[i].frames_remaining <= 0)
			{
				bubbles[i].state = bubbles[i].points_awarded ? PoppedPoints : Popped;
				bubbles[i].frames_remaining = BubbleScoreFrames;
			}
			break;
		}
		case PoppedPoints: {
			bubbles[i].frames_remaining--;
			if (bubbles[i].frames_remaining <= 0)
			{
				bubbles[i].state = Popped;
			}
			break;
		}
		default: {
			// Wiggle
			bubbles[i].x += (r & 1) ? 0 : (r & 2 ? -1 : 1);
			if (bubbles[i].x < 5) {
				bubbles[i].x = 5;
			}
			if (bubbles[i].x > 139)
			{
				bubbles[i].x = 139;
			}
			r >>= 2;
			break;
		}
		}
	}

	// Move the bubbles up a line
	bubbleDistance += BubbleVelocity;
	if (bubbleDistance > 1)
	{
		bubbleDistance -= 1;
		bubble_offset++;
		if (bubble_offset >= 16)
		{
			bubble_offset = 0;
			if (!bubbles[bubble_index].points_awarded) {
				auto size = randint() & 3;
				if (size > 2)
					size = 0;
				bubbles[bubble_index].hit_box = BubbleHitBoxes[size];
				bubbles[bubble_index].state = (BubbleState)size;
			}
			bubble_index++;
			if (bubble_index >= 16)
			{
				bubble_index = 0;
			}
		}
	}
	int bi = bubble_index;
	// Check for collision with bubble in row above and below fly's Y position.
	if (fly.is_alive)
	{
		int bit = ((fy >> 4) + bi) & 0xf;
		int bib = (bit + 1) & 0xf;
		fly.hit_box.X = fly.x.Round() - 8;
		fly.hit_box.Y = (fy & 0xf) + bubble_offset;
		(*bubbles[bit].hit_box).X = bubbles[bit].x;
		if ((int)bubbles[bit].state < 3 && fly.hit_box.Intersects(*bubbles[bit].hit_box))
		{
			bubbles[bit].state = Popping0;
			bubbles[bit].frames_remaining = BubblePopFrames;
			bubbles[bit].points_awarded = true;
			init_audio_player(&sfx_player, 1, &SfxBubblePop);
			sfx_frames_remaining = SfxBubblePop.percussions[0].length;
			if (challenge_player == 0)
				monkey_0.score += BubblePopValue;
			else
				monkey_1.score += BubblePopValue;
		}
		fly.hit_box.Y -= 16;
		(*bubbles[bib].hit_box).X = bubbles[bib].x;
		if ((int)bubbles[bib].state < 3 && fly.hit_box.Intersects(*bubbles[bib].hit_box))
		{
			bubbles[bib].state = Popping0;
			bubbles[bib].frames_remaining = BubblePopFrames;
			bubbles[bib].points_awarded = true;
			init_audio_player(&sfx_player, 1, &SfxBubblePop);
			sfx_frames_remaining = SfxBubblePop.percussions[0].length;
			if (challenge_player == 0)
				monkey_0.score += BubblePopValue;
			else
				monkey_1.score += BubblePopValue;
		}
	}	
	// Pop bubbles towards top of screen to force fly into danger zone to pick up points
	int bip = (bi + 3) & 0xf;
	if ((int)bubbles[bip].state < 3) {
		bubbles[bip].state = Popping0;
		bubbles[bip].frames_remaining = BubblePopFrames;
	}
	// Top bubble may start in middle so position it ahead of time
	colupfBuffer[0] = bubbles[bi].x + 8; 
	// Bubbles
	int j = bubble_offset;
	for (int i = 3; i < 192; )
	{
		int b = (int)bubbles[bi].state;
		for (; j < 15 && i < 192; j++)
		{
			colupfBuffer[i] = 0;
			grp1Buffer[i] = 0;
			if (b < 7)
			{
				grp1Buffer[i] = BubbleGraphics[b][j];
				colup1Buffer[i] = BubbleColu[b][j];
			}
			i++;
		}
		j = 0;
		bi++;
		bi &= 0xf;
		// Position next bubble
		int x = bubbles[bi].x;
		grp1Buffer[i] = 0;
		colupfBuffer[i] = ((-(x % 15) << 4) + 0x70) + (x / 15) + 1;
		i++;
	}

	for (int i = 0; i < 192; i++)
	{
		grp0Buffer[i] = 0;
	}

	// Blit fly
	if (fly.is_alive) {
		for (int i = 0; i < 11; i++)
		{
			grp0Buffer[fy + i] = FlyGraphics[(frame >> 4) & 1][i];
			colup0Buffer[fy + i] = FlyColu[(frame >> 4) & 1][i];
		}
	}
}

void RenderChallengeScreen() {
	int line = 0;
	vcsEndOverblank();
	writeAudio30();


	vcsSta3(WSYNC);
	vcsSta3(WSYNC);
	vcsSta3(WSYNC);
	vcsSta3(HMOVE);
	vcsWrite5(GRP1, 0);
	vcsWrite5(COLUP0, 0);
	vcsSta3(COLUP1);
	vcsWrite5(PF0, 0);
	vcsWrite5(PF1, 0);
	vcsWrite5(PF2, 0);
	vcsWrite5(VDELP0, 0);
	vcsWrite5(VDELP1, 1);
	vcsJmp3();
	vcsSta3(HMCLR);
	vcsNop2n(12);
	vcsWrite5(VBLANK, 0);

	DisplayText(ColuScoreBackground, 1);

	// Prep for rest of screen
	PositionObject(line, fly.x.Round(), RESP0, HMP0);
	PositionObject(line, colupfBuffer[0], RESPONE, HMP1);
	vcsSta3(HMOVE);
	vcsWrite5(GRP1, grp1Buffer[0]);
	vcsWrite5(COLUP0, 0);
	vcsSta3(COLUP1);
	vcsWrite5(PF0, ReverseByte[playfieldBuffer[0] >> 4]);
	vcsWrite5(PF1, (playfieldBuffer[0] << 4) | (playfieldBuffer[1] >> 4));
	vcsWrite5(PF2, ReverseByte[(uint8_t)((playfieldBuffer[1] << 4) | (playfieldBuffer[2] >> 4))]);
	vcsWrite5(VDELP0, 0);
	vcsWrite5(VDELP1, 1);
	vcsJmp3();
	vcsSta3(HMCLR);
	vcsWrite5(NUSIZ0, 0);
	vcsWrite5(NUSIZ1, 0);
	vcsNop2n(7);
	uint8_t colubk = InitialColuWall;
	if (shake_frames_remaining > 0)
	{
		shake_frames_remaining--;
		colubk = ColuRedWall;
	}
	vcsWrite5(COLUBK, colubk);

	for (int i = line; i < room_height; i++)
	{
		vcsSta3(HMOVE);							// 3
		vcsJmp3();									// 6
		vcsWrite5(GRP0, grp0Buffer[i]);		// 11
		vcsWrite5(COLUP0, colup0Buffer[i]);	// 16
		vcsWrite5(COLUP1, colup1Buffer[i]);	// 21
		if ((colupfBuffer[i] & 0xf) == 1) {
			vcsNop2();
			vcsSta3(RESPONE);
		}
		vcsWrite5(COLUPF, i < 34 ? FanChasisColu[18] : InitialColuP0Monkey);		// 26 31
		if ((colupfBuffer[i] & 0xf) == 2) {
			vcsNop2();
			vcsSta3(RESPONE);
		}
		vcsWrite5(PF2, ReverseByte[(uint8_t)((playfieldBuffer[i * 5 + 1] << 4)
			| (playfieldBuffer[i * 5 + 2] >> 4))]);								// 31	36
		if ((colupfBuffer[i] & 0xf) == 3) {
			vcsNop2();
			vcsSta3(RESPONE);
		}
		vcsWrite5(PF0, ReverseByte[playfieldBuffer[i * 5 + 2]]);				// 36	41
		if ((colupfBuffer[i] & 0xf) == 4) {
			vcsNop2();
			vcsSta3(RESPONE);
		}
		vcsWrite5(PF1, playfieldBuffer[i * 5 + 3]);								// 41	46
		if ((colupfBuffer[i] & 0xf) == 5) {
			vcsNop2();
			vcsSta3(RESPONE);
		}
		vcsWrite5(COLUPF, i < 34 ? FanChasisColu[18] : InitialColuP1Monkey);		// 46	51
		if ((colupfBuffer[i] & 0xf) == 6) {
			vcsNop2();
			vcsSta3(RESPONE);
		}
		vcsWrite5(PF2, ReverseByte[playfieldBuffer[i * 5 + 4]]);				// 51	56
		if ((colupfBuffer[i] & 0xf) == 7) {
			vcsNop2();
			vcsSta3(RESPONE);
		}
		vcsWrite5(PF0, ReverseByte[playfieldBuffer[(i + 1) * 5] >> 4]);	// 56	61
		if ((colupfBuffer[i] & 0xf) == 8) {
			vcsNop2();
			vcsSta3(RESPONE);
		}
		vcsWrite5(HMP1, colupfBuffer[i]);
		if ((colupfBuffer[i] & 0xf) == 9) {
			vcsNop2();
			vcsSta3(RESPONE);
		}
		vcsWrite5(PF1, (playfieldBuffer[(i + 1) * 5] << 4)
			| (playfieldBuffer[(i + 1) * 5 + 1] >> 4));							//	66	71
		if ((colupfBuffer[i] & 0xf) > 9) {
			vcsNop2();
			vcsSta3(RESPONE);
		}
		vcsWrite5(GRP1, grp1Buffer[i + 1]);											// 71	76
		if ((colupfBuffer[i] & 0xf) == 0) {
			vcsWrite5(CXCLR, 0);
		}
	}
}

void RenderWideBed(int& line, Monkey* jumping_monkey, Monkey* standing_monkey) {
	PositionObject(line, 132, RESPONE, HMP1);
	PositionObject(line, 25, RESM1, HMM1);

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
		vcsWrite5(COLUPF, i < 2 ? ColuHeadboard : ColuBedPost);
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

	for (int i = 0; line < room_height; i++)
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
		vcsWrite5(COLUBK, line < 170 ? ColuSheet : ColuBedPost);
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

const uint8_t hmp1_lookup[] = { 0x77, 0x76, 0x75, 0x74, 0x73, 0x72, 0x71, 0x70, 0x60, 0x50, 0x40, 0x30, 0x20, 0x10, 0x00,
										0xf0, 0xe0, 0xd0, 0xc0, 0xb0, 0xa0, 0x90, 0x80, 0x8f, 0x8e, 0x8d, 0x8c, 0x8b, 0x8a, 0x89, 0x88 };

void RenderMediumBed(int& line, Monkey* jumping_monkey, Monkey* standing_monkey) {
	PositionObject(line, 120, RESPONE, HMP1);
	PositionObject(line, 37, RESM1, HMM1);
	// Headboard
	for (int i = 0; i < 40; i++)
	{
		vcsSta3(HMOVE);
		vcsWrite5(COLUPF, ColuHeadboard);
		vcsWrite5(GRP0, grp0Buffer[line]);
		vcsWrite5(PF0, ReverseByte[HeadBoardMediumGraphics[i * 5] >> 4]);
		vcsWrite5(PF1, (HeadBoardMediumGraphics[i * 5] << 4) | (HeadBoardMediumGraphics[i * 5 + 1] >> 4));
		vcsWrite5(COLUBK, ColuWall);
		vcsWrite5(PF2, ReverseByte[(uint8_t)((HeadBoardMediumGraphics[i * 5 + 1] << 4) | (HeadBoardMediumGraphics[i * 5 + 2] >> 4))]);
		vcsWrite5(PF0, ReverseByte[HeadBoardMediumGraphics[i * 5 + 2]]);
		vcsWrite6(PF1, HeadBoardMediumGraphics[i * 5 + 3]);
		vcsWrite5(PF2, ReverseByte[HeadBoardMediumGraphics[i * 5 + 4]]);
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
		vcsWrite5(PF1, i < 4 ? 0x07 : 0x0f);
		vcsWrite5(COLUBK, ColuWall);
		vcsWrite5(PF2, 0xff);
		vcsWrite5(CTRLPF, 1);
		if (i == 7)
		{
			vcsNop2n(14);
			vcsWrite5(CTRLPF, 0x05);
			vcsWrite5(PF2, 0);
		}
		else
		{
			vcsSta3(WSYNC);
		}
		line++;
	}
	// 8 lines of post, wall, and sheet
	for (int i = 0; i < 8; i++)
	{
		vcsSta3(HMOVE);
		vcsWrite5(COLUBK, i < 6 ? ColuWall : ColuFloor);
		vcsWrite5(COLUPF, i < 2 ? ColuHeadboard : ColuBedPost);
		vcsWrite5(PF0, 0x80);
		vcsWrite5(PF1, 0xf0);
		vcsWrite5(GRP0, grp0Buffer[line]);
		vcsWrite5(COLUBK, ColuSheet);
		vcsWrite5(PF2, 0x00);
		vcsWrite5(PF1, 0xe0);
		vcsNop2n(3);
		if (i == 3) {
			vcsWrite5(ENAM1, 0);
			vcsSta3(GRP1);
		}
		else
		{
			vcsNop2n(4);
		}
		vcsWrite5(PF0, 0xc0);
		vcsWrite5(COLUBK, i < 6 ? ColuWall : ColuFloor);
		vcsSta3(WSYNC);
		line++;
	}

	uint8_t hmp1 = 0;
	// Position Second Monkey while drawing matress and bed posts with PF
	// 28 is furthest left position
	int x = standing_monkey->x.Round();
	// 28-54
	// 55-81
	// 82-108
	// 109-136
	vcsSta3(HMOVE);
	vcsWrite5(COLUBK, ColuFloor);
	vcsWrite5(PF0, 0);
	vcsWrite5(PF1, 0);
	vcsJmp3();
	vcsLdx2(ColuSheet);
	vcsWrite5(COLUBK, ColuBedPost);
	vcsStx4(COLUBK);
	if (x < 55)
	{
		hmp1 = hmp1_lookup[x - 28];
		vcsSta3(RESPONE);
		vcsNop2n(12);
		vcsLdy2(hmp1);
		vcsLdx2(ColuFloor);
		vcsWrite5(COLUBK, ColuBedPost);
	}
	else if (x < 82)
	{
		vcsNop2n(4);
		hmp1 = hmp1_lookup[x - 55];
		vcsSta4(RESPONE);
		vcsNop2n(6);
		vcsJmp3();
		vcsLdy2(hmp1);
		vcsLdx2(ColuFloor);
		vcsWrite5(COLUBK, ColuBedPost);
	}
	else if (x < 109)
	{
		vcsNop2n(9);
		hmp1 = hmp1_lookup[x - 82];
		vcsSta3(RESPONE);
		vcsNop2();
		vcsJmp3();
		vcsLdy2(hmp1);
		vcsLdx2(ColuFloor);
		vcsWrite6(COLUBK, ColuBedPost);
	}
	else
	{
		vcsNop2n(4);
		hmp1 = hmp1_lookup[x - 109];
		vcsNop2n(6);
		vcsLdy2(hmp1);
		vcsLdx2(ColuFloor);
		vcsLda2(ColuBedPost);
		vcsSta4(RESPONE);
		vcsJmp3();
		vcsSta3(COLUBK);
	}
	vcsStx4(COLUBK);
	vcsSty4(HMP1);
	line++;

	vcsSta3(HMOVE);
	vcsWrite5(COLUBK, ColuFloor);
	vcsWrite5(PF0, 0);
	vcsWrite5(PF1, 0);
	vcsJmp3();
	vcsLdx2(ColuSheet);
	vcsWrite5(COLUBK, ColuBedPost);
	vcsStx4(COLUBK);
	vcsNop2n(5);
	vcsJmp3();
	vcsWrite5(COLUP1, standing_monkey->color);
	vcsLdy2(grp0Buffer[line + 1]);
	vcsWrite6(HMP1, hmp1 << 4);
	vcsJmp3();
	vcsLdx2(ColuFloor);
	vcsWrite5(COLUBK, ColuBedPost);
	vcsStx4(COLUBK);
	vcsSta3(WSYNC);
	line++;

	for (int i = 0; line < room_height; i++)
	{
		vcsSta3(HMOVE);
		if (i == 0)
		{
			vcsWrite5(COLUPF, ColuMattress);
		}
		else {
			vcsWrite5(CTRLPF, 0);
		}
		vcsWrite5(PF0, ReverseByte[playfieldBuffer[line * 5] >> 4]);
		vcsWrite5(PF1, (playfieldBuffer[line * 5] << 4) | (playfieldBuffer[line * 5 + 1] >> 4));
		vcsSty3(GRP0);
		vcsLdx2(line < 170 ? ColuSheet : ColuBedPost);
		vcsWrite5(COLUBK, ColuBedPost);
		vcsStx4(COLUBK);
		vcsWrite5(PF2, ReverseByte[(uint8_t)((playfieldBuffer[line * 5 + 1] << 4) | (playfieldBuffer[line * 5 + 2] >> 4))]);
		vcsWrite5(PF0, ReverseByte[playfieldBuffer[line * 5 + 2]]);
		vcsWrite5(PF1, playfieldBuffer[line * 5 + 3]);
		vcsNop2();
		vcsWrite5(PF2, ReverseByte[playfieldBuffer[line * 5 + 4]]);
		vcsWrite5(GRP1, grp1Buffer[line+1]);
		vcsLdy2(grp0Buffer[line + 1]);
		vcsLdx2(ColuFloor);
		vcsWrite5(COLUBK, ColuBedPost);
		vcsStx4(COLUBK);
		vcsSta4(HMCLR);
		line++;
	}

}

void RenderNarrowBed(int& line, Monkey* jumping_monkey, Monkey* standing_monkey) {
	PositionObject(line, 108, RESPONE, HMP1);
	PositionObject(line, 49, RESM1, HMM1);
	// Headboard
	for (int i = 0; i < 40; i++)
	{
		vcsSta3(HMOVE);
		vcsWrite5(COLUPF, ColuHeadboard);
		vcsWrite5(GRP0, grp0Buffer[line]);
		vcsWrite5(PF0, ReverseByte[HeadBoardNarrowGraphics[i * 5] >> 4]);
		vcsWrite5(PF1, (HeadBoardNarrowGraphics[i * 5] << 4) | (HeadBoardNarrowGraphics[i * 5 + 1] >> 4));
		vcsWrite5(COLUBK, ColuWall);
		vcsWrite5(PF2, ReverseByte[(uint8_t)((HeadBoardNarrowGraphics[i * 5 + 1] << 4) | (HeadBoardNarrowGraphics[i * 5 + 2] >> 4))]);
		vcsWrite5(PF0, ReverseByte[HeadBoardNarrowGraphics[i * 5 + 2]]);
		vcsWrite6(PF1, HeadBoardNarrowGraphics[i * 5 + 3]);
		vcsWrite5(PF2, ReverseByte[HeadBoardNarrowGraphics[i * 5 + 4]]);
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
		vcsWrite5(PF1, i < 4 ? 0x00 : 0x01);
		vcsWrite5(COLUBK, ColuWall);
		vcsWrite5(PF2, 0xff);
		vcsWrite5(CTRLPF, 1);
		if (i == 7)
		{
			vcsNop2n(14);
			vcsWrite5(CTRLPF, 0x05);
			vcsWrite5(PF2, 0);
		}
		else
		{
			vcsSta3(WSYNC);
		}
		line++;
	}
	// 8 lines of post, wall, and sheet
	for (int i = 0; i < 8; i++)
	{
		vcsSta3(HMOVE);
		vcsWrite5(COLUPF, i < 2 ? ColuHeadboard : ColuBedPost);
		vcsWrite5(COLUBK, i < 6 ? ColuWall : ColuFloor);
		vcsWrite5(GRP0, grp0Buffer[line]);
		vcsWrite5(PF0, 0x00);
		vcsWrite5(PF1, 0x3e);
		vcsWrite5(COLUBK, ColuSheet);
		vcsWrite5(PF2, 0x00);
		vcsJmp3();
		vcsWrite5(PF1, 0x7c);
		vcsNop2n(2);
		if (i == 3) {
			vcsWrite5(ENAM1, 0);
			vcsSta3(GRP1);
		}
		else
		{
			vcsNop2n(4);
		}
		vcsWrite5(PF0, 0x00);
		vcsWrite5(COLUBK, i < 6 ? ColuWall : ColuFloor);
		vcsSta3(WSYNC);
		line++;
	}

	uint8_t hmp1 = 0;
	// Position Second Monkey while drawing matress and bed posts with PF
	// 28 is furthest left position
	int x = standing_monkey->x.Round();
	// 40-66
	// 67-93
	// 94-120
	vcsSta3(HMOVE);
	vcsWrite5(COLUBK, ColuFloor);
	vcsWrite5(PF0, 0);
	vcsWrite5(PF1, 0);
	vcsJmp3();
	vcsNop2n(2);
	vcsLdx2(ColuSheet);
	vcsWrite5(COLUBK, ColuBedPost);
	vcsStx4(COLUBK);
	if (x < 67)
	{
		hmp1 = hmp1_lookup[x - 40];
		vcsSta3(RESPONE);
		vcsNop2n(8);
		vcsLdy2(hmp1);
		vcsLdx2(ColuFloor);
		vcsWrite5(COLUBK, ColuBedPost);
	}
	else if (x < 94)
	{
		vcsNop2n(4);
		hmp1 = hmp1_lookup[x - 67];
		vcsSta4(RESPONE);
		vcsNop2n(2);
		vcsJmp3();
		vcsLdy2(hmp1);
		vcsLdx2(ColuFloor);
		vcsWrite5(COLUBK, ColuBedPost);
	}
	else
	{
		vcsNop2n(8);
		hmp1 = hmp1_lookup[x - 94];
		vcsLdy2(hmp1);
		vcsSta3(RESPONE);
		vcsLdx2(ColuFloor);
		vcsWrite5(COLUBK, ColuBedPost);
	}
	vcsStx4(COLUBK);
	vcsNop2n(2);
	vcsSty4(HMP1);
	line++;

	vcsSta3(HMOVE);
	vcsWrite5(COLUBK, ColuFloor);
	vcsWrite5(PF0, 0);
	vcsWrite5(PF1, 0);
	vcsJmp3();
	vcsNop2n(2);
	vcsLdx2(ColuSheet);
	vcsWrite5(COLUBK, ColuBedPost);
	vcsStx4(COLUBK);
	vcsNop2();
	vcsJmp3();
	vcsWrite5(COLUP1, standing_monkey->color);
	vcsLdy2(grp0Buffer[line + 1]);
	vcsWrite6(HMP1, hmp1 << 4);
	vcsJmp3();
	vcsLdx2(ColuFloor);
	vcsWrite5(COLUBK, ColuBedPost);
	vcsStx4(COLUBK);
	line++;
	vcsLdx2(line < 170 ? ColuSheet : ColuBedPost);
	vcsSta3(WSYNC);

	for (int i = 0; line < room_height; i++)
	{
		vcsSta3(HMOVE);
		if (i == 0)
		{
			vcsWrite5(COLUPF, ColuMattress);
		}
		else {
			vcsWrite5(CTRLPF, 0);
		}
		vcsWrite5(PF0, ReverseByte[playfieldBuffer[line * 5] >> 4]);
		vcsWrite5(PF1, (playfieldBuffer[line * 5] << 4) | (playfieldBuffer[line * 5 + 1] >> 4));
		vcsSty3(GRP0);
		vcsWrite6(PF2, ReverseByte[(uint8_t)((playfieldBuffer[line * 5 + 1] << 4) | (playfieldBuffer[line * 5 + 2] >> 4))]);
		vcsWrite5(COLUBK, ColuBedPost);
		vcsStx4(COLUBK);
		vcsWrite5(PF0, ReverseByte[playfieldBuffer[line * 5 + 2]]);
		vcsWrite5(PF1, playfieldBuffer[line * 5 + 3]);
		vcsWrite6(PF2, ReverseByte[playfieldBuffer[line * 5 + 4]]);
		vcsWrite5(GRP1, grp1Buffer[line + 1]);
		vcsLdx2(ColuFloor);
		vcsWrite5(COLUBK, ColuBedPost);
		vcsStx4(COLUBK);
		vcsSta4(HMCLR);
		line++;
		vcsLdy2(grp0Buffer[line]);
		vcsLdx2(line < 170 ? ColuSheet : ColuBedPost);
	}
}

static const uint8_t zoom_hmp[] = { 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0 };
void RenderZoomScreen(int& line, int line_limit) {
	int by = line * 6;
	vcsWrite5(GRP0, 0);
	vcsSta3(GRP1);
	vcsSta3(PF0);
	vcsSta3(PF1);
	vcsSta3(PF2);
	vcsWrite5(COLUP0, FanChasisColu[19]);
	vcsSta3(COLUP1);
	vcsWrite5(NUSIZ0, 0x03); 
	vcsSta3(NUSIZ1);
	vcsSta3(VDELP1);
	vcsSta3(RESP0); // 36 cycles before here
	vcsSta3(RESPONE);
	vcsWrite5(HMP0, zoom_hmp[zoom_level]);
	vcsWrite5(HMP1, zoom_hmp[zoom_level] + 0x10);
	vcsWrite5(VDELP0, 0x01);
	vcsWrite5(COLUPF, zoom_out_red_wall ? ColuRedWall : InitialColuWall);
	vcsLdx2(bitmap[by + 4]);
	vcsLdy2(bitmap[by + 5]);
	vcsWrite5(GRP0, bitmap[by + 0]);
	vcsWrite5(GRP1, bitmap[by + 1]);

	for (bool fl = true; line < line_limit; line++)
	{
		if (fl) {
			vcsSta3(HMOVE);
			fl = false;
		}
		else {
			vcsJmp3();
		}
		vcsWrite5(COLUBK, 0);
		vcsWrite5(PF0, ReverseByte[playfieldBuffer[line * 5] >> 4]);
		vcsWrite5(PF1, (playfieldBuffer[line * 5] << 4) | (playfieldBuffer[line * 5 + 1] >> 4));
		vcsWrite5(PF2, ReverseByte[(uint8_t)((playfieldBuffer[line * 5 + 1] << 4) | (playfieldBuffer[line * 5 + 2] >> 4))]);
		vcsWrite5(GRP0, bitmap[by + 2]);
		vcsWrite6(PF0, ReverseByte[playfieldBuffer[line * 5 + 2]]);
		vcsWrite6(PF1, playfieldBuffer[line * 5 + 3]);
		vcsWrite5(GRP1, bitmap[by + 3]);
		vcsStx3(GRP0);
		vcsSty3(GRP1);
		vcsStx3(GRP0);
		vcsWrite5(PF2, ReverseByte[playfieldBuffer[line * 5 + 4]]);
		vcsSta3(HMCLR);

		by += 6;
		vcsLdx2(bitmap[by + 4]);
		vcsLdy2(bitmap[by + 5]);
		vcsWrite5(GRP0, bitmap[by + 0]);
		vcsWrite5(GRP1, bitmap[by + 1]);
	}
}

void ApplyGravity() {
	if (jumping_monkey->velocity_y > 0)
	{
		// Slow as bottom of mattress is approached
		if (jumping_monkey->y > 130)
		{
			if(jumping_monkey->velocity_y > fp32(0.75))
				jumping_monkey->velocity_y += MattressFriction;
		}
		else
		{
			// Fall faster than ascent
			jumping_monkey->velocity_y += GravityFall;
		}
	}
	else
	{
		jumping_monkey->velocity_y += GravityAscend;
	}

	FP32 TerminalVelocity =  fp32(4);
	if (jumping_monkey->velocity_y > TerminalVelocity)
	{
		jumping_monkey->velocity_y = TerminalVelocity;
	}
}

void DrawBouncingScene() {
	switch (jumping_monkey->state) {
	case Standing:
	case Walking:
	case Jumping:
		jumping_monkey->x += jumping_monkey->velocity_x;

		if (jumping_monkey->x < min_monkey_x) {
			jumping_monkey->x = min_monkey_x;
			jumping_monkey->velocity_x = 0;
		}
		if (jumping_monkey->x > max_monkey_x) {
			jumping_monkey->x = max_monkey_x;
			jumping_monkey->velocity_x = 0;
		}
		ApplyGravity();
		jumping_monkey->y += jumping_monkey->velocity_y;
		break;
	case FanSmacked:
		jumping_monkey->x += jumping_monkey->velocity_x;
		if (jumping_monkey->x < 0 || jumping_monkey->x > 159)
		{
			jumping_monkey->velocity_x = 0;
			jumping_monkey->velocity_y = 0;
			jumping_monkey->face_left = !jumping_monkey->face_left;
			jumping_monkey->frame = 0;
			jumping_monkey->x = 0;
			switch (play_state) {
			case Wide:
			jumping_monkey->y = jumping_monkey->face_left ? 0x5b : 0x65;
			jumping_monkey->velocity_y = fp32(4);
			break;
			case Medium:
			jumping_monkey->y = jumping_monkey->face_left ? 0x37 : 0x4b;
			jumping_monkey->velocity_y = fp32(2);
			break;
			case Narrow:
			default:
			jumping_monkey->y = jumping_monkey->face_left ? 0x5f : 0x6e;
			jumping_monkey->velocity_y = fp32(-4);
			break;
			}
			if (jumping_monkey->lives > 0) {
				jumping_monkey->lives--;
				jumping_monkey->velocity_x = jumping_monkey->face_left ? fp32(-1.5) : fp32(1.5);
				jumping_monkey->frame = 0;
				jumping_monkey->state = HoppingOntoPost;
			}
			else
			{
				jumping_monkey->state = Dead;
			}
		}
		else
		{
			jumping_monkey->velocity_y += fp32(0.0625);
		}
		jumping_monkey->y += jumping_monkey->velocity_y;
		break;
	case HoppingOntoPost:
		// Debug if ((frame & 0x3) == 0)
		{
			jumping_monkey->frame++;
			jumping_monkey->x += jumping_monkey->velocity_x;
			if (jumping_monkey->x < 0)
			{
				jumping_monkey->x += 160;
			}
			if (jumping_monkey->face_left 
				? (jumping_monkey->x <= max_monkey_x + 16)
				: (jumping_monkey->x >= min_monkey_x - 16)) {
				jumping_monkey->velocity_y = 0;
				jumping_monkey->state = WalkingToEdge;
			}
			else {
				// Make it a quick hop since player lacks control on ascent
				jumping_monkey->velocity_y += GravityFall;
			}
			jumping_monkey->y += jumping_monkey->velocity_y;
		}
		break;
	case WalkingToEdge:
		switch (play_substate)
		{
		case Playing:
		case FlyExit:
		case MonkeyLanding:
			jumping_monkey->velocity_x = jumping_monkey->face_left ? fp32(-0.25) : fp32(0.25);
			jumping_monkey->x += jumping_monkey->velocity_x;
			if (jumping_monkey->x < 0)
			{
				jumping_monkey->x += 160;
			}
			if (jumping_monkey->face_left
				? (jumping_monkey->x <= max_monkey_x + 3)
				: (jumping_monkey->x >= min_monkey_x - 3)) {
				jumping_monkey->velocity_x = jumping_monkey->face_left ? fp32(-1.5) : fp32(1.5);
				jumping_monkey->velocity_y = fp32(-4);
				jumping_monkey->state = HoppingOntoMattress;
				jump_in_progress = true;
			}
			break;
		default:
			break;
		}
		break;
	case HoppingOntoMattress:
		jumping_monkey->x += jumping_monkey->velocity_x;
		// Make it a quick hop since player lacks control on ascent
		jumping_monkey->velocity_y += GravityFall;
		jumping_monkey->y += jumping_monkey->velocity_y;
		if (jumping_monkey->y > 130) {
			jumping_monkey->state = Jumping;
		}
		break;
	case Dead:
		break;
	}

	if (shake_frames_remaining > 0) {
		shake_frames_remaining--;
	}
	
	if (jumping_monkey->bottomed_out)
	{
		jumping_monkey->bottomed_out = false;
		jump_in_progress = jumping_enabled;
		if (jumping_enabled)
		{
			auto lv = (standing_monkey->x.Round() + 2 + (wave_length / 4)) - sine_hpos;
			auto vx = fp32(-1.25) * FP32(Sine[(uint8_t)((((lv % wave_length) * 256) / wave_length)).Round()], true);
			auto vy = fp32(-7.5) + (fp32(-0.6) * FP32(Sine[(uint8_t)((((lv % wave_length) * 128) / wave_length)).Round()], true));

			Monkey* temp = jumping_monkey;
			jumping_monkey = standing_monkey;
			standing_monkey = temp;
			jumping_monkey->velocity_x = vx;
			jumping_monkey->velocity_y = vy;
			jumping_monkey->state = Jumping;
			standing_monkey->state = Standing;
			init_audio_player(&sfx_player, 1, &SfxBounce);
			sfx_frames_remaining = SfxBounce.percussions[0].length;
		}
		else
		{
			jumping_monkey->state = Standing;
		}
	}
	else if (jumping_monkey->y > 158)
	{
		jumping_monkey->y = 158;
		jumping_monkey->bottomed_out = true;
	}
	else if (jumping_monkey->y > 129 && jumping_monkey->velocity_y > 0)
	{
		jumping_monkey->velocity_x = 0;
	}

	jumping_monkey->hit_box.X = jumping_monkey->x;
	jumping_monkey->hit_box.Y = jumping_monkey->y;
	if (jumping_monkey->hit_box.Intersects(fan_blade_hit_boxes[fanFrame]))
	{
		shake_frames_remaining = 15;
		jumping_monkey->state = FanSmacked;
		jumping_monkey->velocity_x = jumping_monkey->x < 0x4d ? -2 : 2;
		jumping_monkey->velocity_y = 0;
		init_audio_player(&sfx_player, 1, &SfxFan);
		sfx_frames_remaining = SfxFan.percussions[0].length;
	}

	if (jumping_monkey->velocity_x < 0)
		jumping_monkey->face_left = true;
	else if (jumping_monkey->velocity_x > 0)
		jumping_monkey->face_left = false;

	// preclear buffers
	for (int i = 0; i < 192; i++)
	{
		grp0Buffer[i] = 0;
		grp1Buffer[i] = 0;
	}

	if (fly_top_spawned || fly_spawn_enabled)
	{
		fly_top_x -= 1;
	}
	if (fly_top_x < 0)
		fly_top_x = 159;
	fly_top_y += Fly_Wave_Y[fly_top_index];
	fly_top_index++;
	if (fly_top_index > sizeof(Fly_Wave_Y))
		fly_top_index = 0;

	if ((frame & 0) == 0) {
		if (fly_bot_spawned || fly_spawn_enabled)
		{
			fly_bot_x += Fly_Loop_X[fly_loop_index];
		}
		fly_bot_y += Fly_Loop_Y[fly_loop_index];
		fly_loop_index += 1;
		if (fly_loop_index >= sizeof(Fly_Loop_X))
			fly_loop_index = 0;
		if (fly_bot_x > 159)
			fly_bot_x -= 160;
		if (fly_bot_x < 0)
			fly_bot_x += 160;
	}

	// Fan blade test
	if ((frame & 3) == 0) {
		fanFrame++;
	}
	if (fanFrame > 6)
	{
		fanFrame = 0;
	}
	for (int y = 0; y < 7; y++)
	{
		playfieldBuffer[(12 + y) * 5 + 1] = FanBladeGraphics[fanFrame][y * 2] >> 7;
		playfieldBuffer[(12 + y) * 5 + 2] = FanBladeGraphics[fanFrame][y * 2] << 1 | FanBladeGraphics[fanFrame][y * 2 + 1] >> 7;
		playfieldBuffer[(12 + y) * 5 + 3] = FanBladeGraphics[fanFrame][y * 2 + 1] << 1;
		colupfBuffer[12 + y] = ColuFanBlade;
	}

	// Wall around light that will be zoomed to for challenge
	for (int i = 0; i < 22; i++)
	{
		playfieldBuffer[(19 + i) * 5 + 2] = show_challenge_wall ? 0x3e : 0;
		colupfBuffer[19 + i] = InitialColuWall;
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
	for (size_t i = 0; i < sizeof(FanChasisGraphics) / sizeof(FanChasisGraphics[0]); i++)
	{
		grp1Buffer[i + 3] = FanChasisGraphics[i];
		colup1Buffer[i + 3] = FanChasisColu[i];
	}

	// Banana
	banana_shown = banana_shown && bonus_enabled;
	if (banana_shown)
	{
		for (size_t i = 0; i < sizeof(BonusBananaGraphics) / sizeof(BonusBananaGraphics[0]); i++)
		{
			grp1Buffer[i + 33] = BonusBananaGraphics[i];
			colup1Buffer[i + 33] = BonusBananaColu[i];
		}
	}
	banana_cooldown--;
	if (banana_cooldown <= 0)
	{
		banana_shown = !banana_shown;
		banana_cooldown = banana_shown ? 4 * 60 : 7 * 60;
	}

	DrawMattress();

	if (standing_monkey->y > monkey_y_hwm)
	{
		monkey_y_hwm = standing_monkey->y.Round();
	}
	if (standing_monkey->y < monkey_y_lwm)
	{
		monkey_y_lwm = standing_monkey->y.Round();
	}

	DrawMonkeys();

	if (standing_monkey->y < min)
	{
		min = standing_monkey->y.Round();
	}
	if (standing_monkey->y > max)
	{
		max = standing_monkey->y.Round();
	}

	if (jumping_monkey->state != FanSmacked) {

		fly_top_hit_box.X = fly_top_x;
		if (jumping_monkey->hit_box.Intersects(fly_top_hit_box))
		{
			fly_top_spawned = fly_spawn_enabled;
			fly_top_x = 4;
			jumping_monkey->score += 1;
			init_audio_player(&sfx_player, 1, &SfxFlyCaught);
			sfx_frames_remaining = SfxFlyCaught.percussions[0].length;
		}

		fly_bot_hit_box.X = fly_bot_x;
		if (jumping_monkey->hit_box.Intersects(fly_bot_hit_box))
		{
			fly_bot_spawned = fly_spawn_enabled;
			fly_bot_x = 4;
			jumping_monkey->score += 1;
			init_audio_player(&sfx_player, 1, &SfxFlyCaught);
			sfx_frames_remaining = SfxFlyCaught.percussions[0].length;
		}
		if (banana_shown && jumping_monkey->hit_box.Intersects(banana_hit_box))
		{
			banana_shown = false;
			jumping_monkey->score += 5;
			init_audio_player(&sfx_player, 1, &SfxBonus);
			sfx_frames_remaining = SfxBonus.percussions[0].length;
		}
	}
}

static const uint8_t ZoomWallLookup[] =
{
	0x00, 0x00, 0x3e, 0x00, 0x00,
	0x00, 0x00, 0x7f, 0x00, 0x00,
	0x00, 0x00, 0xff, 0x80, 0x00,
	0x00, 0x01, 0xff, 0xc0, 0x00,
	0x00, 0x03, 0xff, 0xe0, 0x00,
	0x00, 0x07, 0xff, 0xf0, 0x00,
	0x00, 0x0f, 0xff, 0xf8, 0x00,
	0x00, 0x1f, 0xff, 0xfc, 0x00,
	0x00, 0x3f, 0xff, 0xfe, 0x00,
	0x00, 0x7f, 0xff, 0xff, 0x00,
	0x00, 0xff, 0xff, 0xff, 0x80,
	0x01, 0xff, 0xff, 0xff, 0xc0,
	0x03, 0xff, 0xff, 0xff, 0xe0,
	0x07, 0xff, 0xff, 0xff, 0xf0,
	0x0f, 0xff, 0xff, 0xff, 0xf8,
	0x1f, 0xff, 0xff, 0xff, 0xfc,
	0x3f, 0xff, 0xff, 0xff, 0xfe,
	0x3f, 0xff, 0xff, 0xff, 0xff,
};

__attribute__((long_call, section(".RamFunc")))
void DrawZoomScene() {
	// Countdown is drawn with zoom kernel, if countdown has begun add the sprite and skip the rest,
	// the rest of the scene was already drawn last frame
	if (countdown_frames_remaining > 0)
	{
		auto os = 80 * 6;
		for (int i = 0; i < (int)sizeof(CountdownGraphics[countdown_index]); i++)
		{
			bitmap[os++] = CountdownGraphics[countdown_index][i];
		}
		if (challenge_player > 0) {
			os = (80 * 6) + 4;
			for (int i = 0; i < (int)sizeof(CountdownP2Graphics); i++)
			{
				bitmap[os] = CountdownP2Graphics[i];
				os += 6;
			}
		}
		return;
	}
	// Had to move multiplications outside of loops to run on Cortex-M0+
	// PF (wall)
	int top = 19 - zoom_level; // ((zoom_level * 17) / 17);
	int bottom = 41 + ((zoom_level * 134) / 17);
	for (int i = 0; i < top * 5; i++)
	{
		playfieldBuffer[i] = 0;
	}
	int k = top * 5;
	auto zwl = zoom_level * 5;
	for (int i = top; i < bottom; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			playfieldBuffer[k + j] = ZoomWallLookup[zwl + j];
		}
		k += 5;
	}
	for (int i = bottom * 5; i < 175 * 5; i++)
	{
		playfieldBuffer[i] = 0;
	}

	// Sprite (Light)
	for (int i = 0; i < top * 6; i++)
	{
		bitmap[i] = 0;
	}
	int light_height = 1 + ((zoom_level * 7) / 17);
	int lhi = 0;
	for (int i = 0; i < 4; i++)
	{
		// Get graphics width
		auto width = BitWidthLookup[FanChasisGraphics[16 + i] >> 4];
		// Scale to zoom
		width *= light_height;
		auto os2 = width * 3;
		auto os = (lhi + top) * 6;
		for (int j = 0; j < light_height; j++)
		{
			bitmap[os++] = BitWidthTo24PixelLookup[os2];
			bitmap[os++] = BitWidthTo24PixelLookup[os2 + 1];
			bitmap[os++] = BitWidthTo24PixelLookup[os2 + 2];
			bitmap[os++] = ReverseByte[BitWidthTo24PixelLookup[os2 + 2]];
			bitmap[os++] = ReverseByte[BitWidthTo24PixelLookup[os2 + 1]];
			bitmap[os++] = ReverseByte[BitWidthTo24PixelLookup[os2]];
		}
		lhi += light_height;
	}
	for (int i = (4 * light_height + top) * 6; i < 40*60; i++)
	{
		bitmap[i] = 0;
	}

}

void DrawMattress() {
	FP32 max_height = FP32(Sine[sine_frame], true) * fp32(16);
	// Mattress
	for (size_t i = 130 * 5; i < sizeof(playfieldBuffer); i++)
	{
		playfieldBuffer[i] = 0;
	}
	if (jumping_monkey->state != Dead)
	{
		sine_frame += 4;
		max_height = FP32(Sine[sine_frame], true) * fp32(15);
		if (jumping_monkey->y > 129 && jumping_monkey->y < 0xa4 && jump_in_progress)
		{
			if (jumping_monkey->y > 142)
			{
				// Once below sine middle move wave to player
				sine_hpos = jumping_monkey->x.Round() + 2 + (wave_length / 4);
			}
			// Adjust height down to player if needed
			FP32 height_ratio = FP32(Sine[(uint8_t)(((((jumping_monkey->x.Round() + 4) - sine_hpos) % wave_length) * 256) / wave_length).Round()], true);
			while (((max_height * height_ratio) + 15) > (159 - jumping_monkey->y.Round()))
			{
				sine_frame++;
				max_height = FP32(Sine[sine_frame], true) * fp32(15);
			}
		}
		else
		{
		}
	}

	for (int i = bed_left; i < bed_right; i++)
	{
		uint8_t si = (uint8_t)((((i - sine_hpos) % wave_length) * 256) / wave_length).Round();
		int height = 15 + (FP32(Sine[si], true) * max_height).Round();
		if (i == ((standing_monkey->x.Round()) + 3))
		{
			standing_monkey->y = 158 - height;
		}
		if (!jump_in_progress && (i == ((jumping_monkey->x.Round()) + 3)))
		{
			jumping_monkey->y = 158 - height;
		}
		if ((i & 0x3) == 0)
		{
			for (int j = 0; j <= height; j++)
			{
				setPF(i/4, 169 - j);
			}
		}
	}
}

void DrawMonkey(Monkey* monkey, uint8_t* buffer) {
	int sprite_index = 0;
	if (monkey->state == Jumping || monkey->state == HoppingOntoPost || monkey->state == HoppingOntoMattress)
		sprite_index = 2;
	else if (monkey->state == Standing || play_substate == NotPlaying)
		sprite_index = 0;
	else if (monkey->state == Walking || monkey->state == WalkingToEdge)
		sprite_index = (frame >> 3) & 1;
	else if (monkey->state == FanSmacked) {
		monkey->frame++;
		if (monkey->frame >= 4)
		{
			monkey->frame = 0;
			monkey->animation++;
			if (monkey->animation >= 8) {
				monkey->animation = 4;
			}
		}
		sprite_index = monkey->animation;
	}


	for (int j = 0; j < 12; j++)
	{
		auto grp = MonkeyGraphics[sprite_index][j];
		if (!monkey->face_left)
			grp = ReverseByte[grp];
		buffer[monkey->y.Round() + j] = grp;
	}
}
void DrawMonkeys() {
	DrawMonkey(jumping_monkey, grp0Buffer);
	DrawMonkey(standing_monkey, grp1Buffer);
}


void SetVariablesFromState() {
	//live_config.HandleInput(joysticks >> 4);
	p0_monkey->color = ColuP0Monkey;
	p1_monkey->color = ColuP1Monkey;


	// Apply current state
	switch (play_state) {
	case(Wide):
		InitialColuWall = 0x6a;
		render_bed = RenderWideBed;
		min_monkey_x = 16;
		max_monkey_x = 140;
		bed_left = 16;
		bed_right = 148;
		wave_length = 80;
		break;
	case(Medium):
		InitialColuWall = 0x9c;
		InitialColuFloor = 0x1d;
		render_bed = RenderMediumBed;
		min_monkey_x = 28;
		max_monkey_x = 128;
		bed_left = 28;
		bed_right = 136;
		wave_length = 65;
		break;
	case(Narrow):
		InitialColuWall = 0xb9;
		InitialColuFloor = 0x69;
		render_bed = RenderNarrowBed;
		min_monkey_x = 40;
		max_monkey_x = 116;
		bed_left = 40;
		bed_right = 124;
		wave_length = 50;
		break;
	}

	switch (play_substate) {
	case NotPlaying:
		// currently set elsewhere, may want to move to here in future
		break;
	case Playing:
		show_challenge_wall = false;
		bonus_enabled = true;
		jumping_enabled = true;
		fly_spawn_enabled = true;
		show_zoom_screen = false;
		challenge_mode = false;
		break;
	case FlyExit:
		show_challenge_wall = false;
		bonus_enabled = true;
		jumping_enabled = true;
		fly_spawn_enabled = false;
		show_zoom_screen = false;
		challenge_mode = false;
		break;
	case MonkeyLanding:
		show_challenge_wall = false;
		bonus_enabled = false;
		jumping_enabled = false;
		fly_spawn_enabled = false;
		show_zoom_screen = false;
		challenge_mode = false;
		break;
	case FadingOut:
		if (frame & 1)
			fade_level--;
		show_challenge_wall = true;
		bonus_enabled = false;
		jumping_enabled = false;
		fly_spawn_enabled = false;
		show_zoom_screen = false;
		challenge_mode = false;
		break;
	case ZoomingIn:
		if (frame & 1)
			zoom_level++;
		show_challenge_wall = true;
		bonus_enabled = false;
		jumping_enabled = false;
		fly_spawn_enabled = false;
		show_zoom_screen = true;
		challenge_mode = false;
		break;
	case CountingDown:
		show_zoom_screen = true;
		challenge_mode = false;
		break;
	case Challenge:
		challenge_mode = true;
		break;
	case ZoomingOut:
		if (frame & 1)
			zoom_level--;
		show_challenge_wall = true;
		bonus_enabled = false;
		jumping_enabled = false;
		fly_spawn_enabled = false;
		show_zoom_screen = true;
		challenge_mode = false;
		break;
	case FadingIn:
		if (frame & 1)
			fade_level++;
		show_challenge_wall = true;
		bonus_enabled = false;
		jumping_enabled = false;
		fly_spawn_enabled = false;
		show_zoom_screen = false;
		challenge_mode = false;
		break;
	}
}

void DrawScores() {
	// Scoring
	for (int i = 0; i < 18; i++)
	{
		scoreText[i] = ' ';
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

	if (challenge_mode) {
		if (fly.is_alive) {
			int seconds_remaining = challenge_frames_remaining / 60;
			for (int i = 0; i < 2; i++)
			{
				scoreText[9 - i] = (seconds_remaining % 10) & 0xf;
				seconds_remaining /= 10;
			}
		}
	}
	else
	{
		for (int i = 0; i < monkey_0.lives; i++)
		{
			scoreText[5 + i] = 18;
		}
		for (int i = 0; i < monkey_1.lives; i++)
		{
			scoreText[10 + i] = 18;
		}
	}
	// Used when debugging
	//for (int i = 0; i < 8; i++)
	//{
	//	scoreText[i] = (char)((uint32_t)(jumping_monkey->y.Round()) >> ((7 - i) * 4)) & 0xf;
	//}
	//for (int i = 0; i < 8; i++)
	//{
	//	scoreText[i + 10] = (char)((uint32_t)(monkey_y_hwm) >> ((7 - i) * 4)) & 0xf;
	//}
	PrintText(scoreText, 0);
}

void place_monkey_on_post() {
	SetVariablesFromState();
	jumping_monkey->face_left = (jumping_monkey == &monkey_1);
	jumping_monkey->x = jumping_monkey->face_left ? max_monkey_x + 7 : min_monkey_x - 7;
	jumping_monkey->y = 105;
	jumping_monkey->velocity_y = 0;
	jumping_monkey->state = WalkingToEdge;
	jump_in_progress = true;
}

void writeAudio30()
{
	// Channel 0 is always music
	vcsWrite5(AUDC0, audio_player0.control);
	vcsWrite5(AUDV0, audio_player0.volume);
	vcsWrite5(AUDF0, audio_player0.frequency);
	// Channel 1 is either music or SFX
	vcsWrite5(AUDC1, chan1_player->control);
	vcsWrite5(AUDV1, chan1_player->volume);
	vcsWrite5(AUDF1, chan1_player->frequency);
}

void next_audio_frame() {
	// Always move music to next frame, even when SFX is playing
	next_audio_frame(&audio_player0);
	next_audio_frame(&audio_player1);
	// If SFX is playing, move it to the next frame
	if (challenge_mode && sfx_frames_remaining == 0 && fly.is_alive) {
		init_audio_player(&sfx_player, 1, &SfxFlyIdle);
		sfx_frames_remaining = SfxFlyIdle.percussions[0].length;
	}
	if (sfx_frames_remaining > 0)
	{
		sfx_frames_remaining--;
		next_audio_frame(&sfx_player);
		chan1_player = &sfx_player; // point channel 1 to SFX
		if (challenge_mode && (fly.velocity_x != 0 || fly.velocity_y != 0)) {
			sfx_player.volume += FlyBuzzVolAdd;
		}
	}
	else
	{
		chan1_player = &audio_player1; // point channel 1 to music
	}
}

void moveFly(uint8_t joy)
{
	if (!fly.is_alive)
	{
		fly.velocity_x = 0;
		fly.velocity_y = 0;
		return;
	}

	if ((joy & 0x4) == 0) {
		if (fly.x > 8) {
			// left
			fly.velocity_x -= FlyAccel;
			if (fly.velocity_x < MaxFlyVelocityMinus)
			{
				fly.velocity_x = MaxFlyVelocityMinus;
			}
			fly.face_left = true;
		}
	}
	else if ((joy & 0x8) == 0) {
		if (fly.x < 152) {
			// right
			fly.velocity_x += FlyAccel;
			if (fly.velocity_x > MaxFlyVelocity)
			{
				fly.velocity_x = MaxFlyVelocity;
			}
			fly.face_left = false;
		}
	}
	else {
		// Fly should coast to stop
		if (fly.velocity_x > FlyAccel) {
			fly.velocity_x -= FlyAccel;
		}
		else if (fly.velocity_x < FlyAccelMinus){
			fly.velocity_x += FlyAccel;
		}
		else {
			fly.velocity_x = 0;
		}
	}

	if ((joy & 0x1) == 0) {
		if (fly.y > 2) {
			// up
			fly.velocity_y -= FlyAccel;
			if (fly.velocity_y < MaxFlyVelocityMinus)
			{
				fly.velocity_y = MaxFlyVelocityMinus;
			}
		}
	}
	else if ((joy & 0x2) == 0) {
		if (fly.y < 175) {
			// down
			fly.velocity_y += FlyAccel;
			if (fly.velocity_y > MaxFlyVelocity)
			{
				fly.velocity_y = MaxFlyVelocity;
			}
		}
	}
	else {
		// Fly should coast to stop
		if (fly.velocity_y > FlyAccel) {
			fly.velocity_y -= FlyAccel;
		}
		else if (fly.velocity_y < FlyAccelMinus) {
			fly.velocity_y += FlyAccel;
		}
		else {
			fly.velocity_y = 0;
		}
	}
}
