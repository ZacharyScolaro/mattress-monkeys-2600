#ifndef SPRITES_H
#define SPRITES_H
#include <stdint.h>
#include "fp32.hpp"

extern const uint8_t ScoreSpritesGraphics[128*8];

extern const uint8_t GameOverGraphics[6*23];

extern const uint8_t TitleArtGraphics[2][138];

extern const uint8_t MenuOptionsGraphics[8][30];

extern const uint8_t FanBladeGraphics[7][14];

extern const uint8_t FanChasisGraphics[20];

extern const uint8_t FanChasisColuNtsc[20];

extern const uint8_t FanChasisColuPal[20];

extern const uint8_t MonkeyGraphics[8][13];

extern const uint8_t SpiderGraphics[8][13];

extern const uint8_t OctopusGraphics[8][13];

extern const uint8_t BonusBananaGraphics[13];

extern const uint8_t BonusBananaColuNtsc[13];

extern const uint8_t BonusBananaColuPal[13];

extern const uint8_t HeadBoardWideGraphics[200];

extern const uint8_t HeadBoardMediumGraphics[200];

extern const uint8_t HeadBoardNarrowGraphics[200];

extern const uint8_t MonkeyHandOpenGraphics[136];

extern const uint8_t MonkeyHandClosedGraphics[136];

extern const uint8_t CatPawOpenGraphics[136];

extern const uint8_t CatPawClosedGraphics[136];

extern const uint8_t TentacleOpenGraphics[136];

extern const uint8_t TentacleClosedGraphics[136];

extern const uint8_t BubbleGraphics[7][15];

extern const uint8_t BubbleColuNtsc[7][15];

extern const uint8_t BubbleColuPal[7][15];

extern const uint8_t FlyGraphics[2][11];

extern const uint8_t FlyColuNtsc[2][11];

extern const uint8_t FlyColuPal[2][11];

extern const uint8_t CountdownGraphics[3][186];

extern const uint8_t CountdownP2Graphics[3][186];

extern const uint8_t PaletteGraphics[20];

extern const uint8_t PaletteColuNtsc[20];

extern const uint8_t PaletteColuPal[20];

extern const uint8_t PreviewFlyHunterGraphics[1152];

extern const uint8_t PreviewBigfootGraphics[1152];

extern const uint8_t PreviewOctopusherGraphics[1152];

extern const uint8_t ChallengeLightPlayfield[204];

extern const uint8_t kernel_7800[549];


typedef struct {
	const int8_t goto_index;
	const uint8_t pattern_index;
} sequence_t;
typedef struct {
	const sequence_t* sequenced_patterns;
} channel_t;
typedef struct {
	const uint8_t even_speed;
	const uint8_t odd_speed;
	const uint8_t* notes;
} pattern_t;
typedef struct {
const int8_t* frequencies;
const uint8_t* volumes;
const uint8_t sustainStart;
const uint8_t releaseStart;
const uint8_t waveform;
const uint8_t length;
} instrument_t;
typedef struct {
const uint8_t* frequencies;
const uint8_t* volumes;
const uint8_t* waveforms;
const uint8_t length;
} percussion_t;
typedef struct {
	const channel_t channels[2];
	const instrument_t* instruments;
	const percussion_t* percussions;
	const pattern_t* patterns;
} track_t;

extern const track_t SongMonkeys;
extern const track_t SfxBounce;
extern const track_t SfxBonus;
extern const track_t SfxFlyCaught;
extern const track_t SfxFan;
extern const track_t SfxFlyIdle;
extern const track_t SfxFlySquish;
extern const track_t SfxBubblePop;
extern const track_t SfxBellShort;
extern const track_t SfxBellLong;
extern const track_t SfxTimeBonus;
extern const track_t SfxBedFall;
extern const int32_t Sine[256];


#endif // SPRITES_H