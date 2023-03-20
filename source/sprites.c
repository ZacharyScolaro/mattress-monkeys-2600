#include "sprites.h"

const uint8_t ScoreSpritesGraphics[14*13] = { 0x1c, 0x10, 0x3c, 0x3e, 0x0e, 0x7e, 0x1e, 0x3f, 0x3c, 0x3e, 0x00, 0x00, 0x00, 0x1c, 0x10, 0x3c, 0x3e, 0x0e, 0x7e, 0x1e, 0x3f, 0x3c, 0x3e, 0x00, 0x00, 0x00, 0x26, 0x30, 0x66, 0x04, 0x1e, 0x40, 0x30, 0x23, 0x62, 0x63, 0x00, 0x00, 0x08, 0x26, 0x30, 0x66, 0x04, 0x1e, 0x40, 0x30, 0x23, 0x62, 0x63, 0x00, 0x00, 0x08, 0x63, 0x10, 0x06, 0x08, 0x36, 0x7e, 0x60, 0x06, 0x72, 0x63, 0x00, 0x22, 0x00, 0x63, 0x10, 0x06, 0x08, 0x36, 0x7e, 0x60, 0x06, 0x72, 0x63, 0x00, 0x22, 0x00, 0x63, 0x10, 0x1c, 0x1c, 0x66, 0x03, 0x7e, 0x0c, 0x3c, 0x3f, 0x00, 0x14, 0x1c, 0x63, 0x10, 0x1c, 0x1c, 0x66, 0x03, 0x7e, 0x0c, 0x3c, 0x3f, 0x00, 0x14, 0x1c, 0x63, 0x10, 0x30, 0x06, 0x7f, 0x03, 0x63, 0x18, 0x43, 0x03, 0x00, 0x08, 0x08, 0x63, 0x10, 0x30, 0x06, 0x7f, 0x03, 0x63, 0x18, 0x43, 0x03, 0x00, 0x08, 0x08, 0x32, 0x10, 0x60, 0x66, 0x06, 0x63, 0x63, 0x18, 0x43, 0x06, 0x00, 0x14, 0x00, 0x32, 0x10, 0x60, 0x66, 0x06, 0x63, 0x63, 0x18, 0x43, 0x06, 0x00, 0x14, 0x00, 0x1c, 0x7c, 0x7e, 0x38, 0x06, 0x3e, 0x3e, 0x18, 0x3e, 0x3c, 0x00, 0x22, 0x14, 0x1c, 0x7c, 0x7e, 0x38, 0x06, 0x3e, 0x3e, 0x18, 0x3e, 0x3c, 0x00, 0x22, 0x14 };

const uint8_t FanBladeGraphics[7][14] = { 
{ 0x80, 0x00, 0xc0, 0x00, 0xe0, 0x00, 0xf3, 0xc0, 0x01, 0xc0, 0x00, 0xc0, 0x00, 0x40 },

{ 0x00, 0x00, 0x20, 0x00, 0x30, 0x00, 0x33, 0x00, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00 },

{ 0x00, 0x00, 0x10, 0x00, 0x10, 0x00, 0x12, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00 },

{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },

{ 0x00, 0x00, 0x02, 0x00, 0x02, 0x00, 0x12, 0x00, 0x10, 0x00, 0x10, 0x00, 0x00, 0x00 },

{ 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 0x33, 0x00, 0x30, 0x00, 0x20, 0x00, 0x00, 0x00 },

{ 0x00, 0x40, 0x00, 0xc0, 0x01, 0xc0, 0xf3, 0xc0, 0xe0, 0x00, 0xc0, 0x00, 0x80, 0x00 }
 };

const uint8_t FanBladeColu[7] = { 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e };

const uint8_t MonkeyWalkingGraphics[2][12] = { 
{ 0xe0, 0xf1, 0xe2, 0xd2, 0x39, 0x7d, 0x5d, 0x9e, 0xbc, 0xb0, 0x88, 0x58 },

{ 0x01, 0xe2, 0xf2, 0xe1, 0xd9, 0x3d, 0x3e, 0x5c, 0x5c, 0x93, 0x85, 0x0c }
 };

const uint8_t MonkeyWalkingColu[12] = { 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e };

const uint8_t MonkeyIdleGraphics[12] = { 0xe0, 0xf1, 0xe2, 0xd2, 0x39, 0x7d, 0x5d, 0x9e, 0xbc, 0xb0, 0x88, 0x58 };

const uint8_t MonkeyIdleColu[12] = { 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e };

const uint8_t FanChasisGraphics[28] = { 0xff, 0xff, 0x7e, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e, 0xff, 0xff, 0x18, 0xff, 0xff, 0xff, 0x7e, 0x7e, 0x3c, 0x18 };

const uint8_t FanChasisColu[28] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x1e, 0x1e, 0x1e };

const uint8_t BonusBananaGraphics[13] = { 0x20, 0x30, 0x30, 0x18, 0x18, 0x18, 0x3c, 0x5a, 0x1a, 0x38, 0x30, 0x70, 0x60 };

const uint8_t BonusBananaColu[13] = { 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e };

const uint8_t HeadBoardWideGraphics[200] = { 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0xff, 0x80, 0x00, 0x01, 0xc0, 0xff, 0x81, 0xc0, 0x01, 0xc1, 0xff, 0xc1, 0xc0, 0x01, 0xe1, 0xff, 0xc3, 0xc0, 0x01, 0xe3, 0xff, 0xe3, 0xc0, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80 };

const uint8_t HeadBoardWideColu[40] = { 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c };

const uint8_t SineTables[32][80] = { 
{ 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17 },

{ 17, 19, 20, 21, 22, 22, 22, 21, 20, 19, 17, 15, 14, 13, 12, 12, 12, 13, 14, 15, 17, 19, 20, 21, 22, 22, 22, 21, 20, 19, 17, 15, 14, 13, 12, 12, 12, 13, 14, 15, 17, 19, 20, 21, 22, 22, 22, 21, 20, 19, 17, 15, 14, 13, 12, 12, 12, 13, 14, 15, 17, 19, 20, 21, 22, 22, 22, 21, 20, 19, 17, 15, 14, 13, 12, 12, 12, 13, 14, 15 },

{ 17, 20, 23, 25, 26, 27, 26, 25, 23, 20, 17, 14, 11, 9, 8, 7, 8, 9, 11, 14, 17, 20, 23, 25, 26, 27, 26, 25, 23, 20, 17, 14, 11, 9, 8, 7, 8, 9, 11, 14, 17, 20, 23, 25, 26, 27, 26, 25, 23, 20, 17, 14, 11, 9, 8, 7, 8, 9, 11, 14, 17, 20, 23, 25, 26, 27, 26, 25, 23, 20, 17, 14, 11, 9, 8, 7, 8, 9, 11, 14 },

{ 17, 21, 25, 28, 30, 31, 30, 28, 25, 21, 17, 13, 9, 6, 4, 3, 4, 6, 9, 13, 17, 21, 25, 28, 30, 31, 30, 28, 25, 21, 17, 13, 9, 6, 4, 3, 4, 6, 9, 13, 17, 21, 25, 28, 30, 31, 30, 28, 25, 21, 17, 13, 9, 6, 4, 3, 4, 6, 9, 13, 17, 21, 25, 28, 30, 31, 30, 28, 25, 21, 17, 13, 9, 6, 4, 3, 4, 6, 9, 13 },

{ 17, 22, 27, 30, 32, 33, 32, 30, 27, 22, 17, 12, 7, 4, 2, 1, 2, 4, 7, 12, 17, 22, 27, 30, 32, 33, 32, 30, 27, 22, 17, 12, 7, 4, 2, 1, 2, 4, 7, 12, 17, 22, 27, 30, 32, 33, 32, 30, 27, 22, 17, 12, 7, 4, 2, 1, 2, 4, 7, 12, 17, 22, 27, 30, 32, 33, 32, 30, 27, 22, 17, 12, 7, 4, 2, 1, 2, 4, 7, 12 },

{ 17, 22, 27, 31, 34, 34, 34, 31, 27, 22, 17, 12, 7, 3, 0, 0, 0, 3, 7, 12, 17, 22, 27, 31, 34, 34, 34, 31, 27, 22, 17, 12, 7, 3, 0, 0, 0, 3, 7, 12, 17, 22, 27, 31, 34, 34, 34, 31, 27, 22, 17, 12, 7, 3, 0, 0, 0, 3, 7, 12, 17, 22, 27, 31, 34, 34, 34, 31, 27, 22, 17, 12, 7, 3, 0, 0, 0, 3, 7, 12 },

{ 17, 22, 27, 31, 33, 34, 33, 31, 27, 22, 17, 12, 7, 3, 1, 0, 1, 3, 7, 12, 17, 22, 27, 31, 33, 34, 33, 31, 27, 22, 17, 12, 7, 3, 1, 0, 1, 3, 7, 12, 17, 22, 27, 31, 33, 34, 33, 31, 27, 22, 17, 12, 7, 3, 1, 0, 1, 3, 7, 12, 17, 22, 27, 31, 33, 34, 33, 31, 27, 22, 17, 12, 7, 3, 1, 0, 1, 3, 7, 12 },

{ 17, 22, 26, 29, 32, 32, 32, 29, 26, 22, 17, 12, 8, 5, 2, 2, 2, 5, 8, 12, 17, 22, 26, 29, 32, 32, 32, 29, 26, 22, 17, 12, 8, 5, 2, 2, 2, 5, 8, 12, 17, 22, 26, 29, 32, 32, 32, 29, 26, 22, 17, 12, 8, 5, 2, 2, 2, 5, 8, 12, 17, 22, 26, 29, 32, 32, 32, 29, 26, 22, 17, 12, 8, 5, 2, 2, 2, 5, 8, 12 },

{ 17, 21, 24, 27, 29, 29, 29, 27, 24, 21, 17, 13, 10, 7, 5, 5, 5, 7, 10, 13, 17, 21, 24, 27, 29, 29, 29, 27, 24, 21, 17, 13, 10, 7, 5, 5, 5, 7, 10, 13, 17, 21, 24, 27, 29, 29, 29, 27, 24, 21, 17, 13, 10, 7, 5, 5, 5, 7, 10, 13, 17, 21, 24, 27, 29, 29, 29, 27, 24, 21, 17, 13, 10, 7, 5, 5, 5, 7, 10, 13 },

{ 17, 20, 22, 24, 25, 25, 25, 24, 22, 20, 17, 14, 12, 10, 9, 9, 9, 10, 12, 14, 17, 20, 22, 24, 25, 25, 25, 24, 22, 20, 17, 14, 12, 10, 9, 9, 9, 10, 12, 14, 17, 20, 22, 24, 25, 25, 25, 24, 22, 20, 17, 14, 12, 10, 9, 9, 9, 10, 12, 14, 17, 20, 22, 24, 25, 25, 25, 24, 22, 20, 17, 14, 12, 10, 9, 9, 9, 10, 12, 14 },

{ 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16 },

{ 17, 16, 16, 16, 15, 15, 15, 16, 16, 16, 17, 18, 18, 18, 19, 19, 19, 18, 18, 18, 17, 16, 16, 16, 15, 15, 15, 16, 16, 16, 17, 18, 18, 18, 19, 19, 19, 18, 18, 18, 17, 16, 16, 16, 15, 15, 15, 16, 16, 16, 17, 18, 18, 18, 19, 19, 19, 18, 18, 18, 17, 16, 16, 16, 15, 15, 15, 16, 16, 16, 17, 18, 18, 18, 19, 19, 19, 18, 18, 18 },

{ 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18 },

{ 17, 15, 14, 13, 12, 11, 12, 13, 14, 15, 17, 19, 20, 21, 22, 23, 22, 21, 20, 19, 17, 15, 14, 13, 12, 11, 12, 13, 14, 15, 17, 19, 20, 21, 22, 23, 22, 21, 20, 19, 17, 15, 14, 13, 12, 11, 12, 13, 14, 15, 17, 19, 20, 21, 22, 23, 22, 21, 20, 19, 17, 15, 14, 13, 12, 11, 12, 13, 14, 15, 17, 19, 20, 21, 22, 23, 22, 21, 20, 19 },

{ 17, 15, 13, 11, 10, 10, 10, 11, 13, 15, 17, 19, 21, 23, 24, 24, 24, 23, 21, 19, 17, 15, 13, 11, 10, 10, 10, 11, 13, 15, 17, 19, 21, 23, 24, 24, 24, 23, 21, 19, 17, 15, 13, 11, 10, 10, 10, 11, 13, 15, 17, 19, 21, 23, 24, 24, 24, 23, 21, 19, 17, 15, 13, 11, 10, 10, 10, 11, 13, 15, 17, 19, 21, 23, 24, 24, 24, 23, 21, 19 },

{ 17, 14, 12, 10, 9, 9, 9, 10, 12, 14, 17, 20, 22, 24, 25, 25, 25, 24, 22, 20, 17, 14, 12, 10, 9, 9, 9, 10, 12, 14, 17, 20, 22, 24, 25, 25, 25, 24, 22, 20, 17, 14, 12, 10, 9, 9, 9, 10, 12, 14, 17, 20, 22, 24, 25, 25, 25, 24, 22, 20, 17, 14, 12, 10, 9, 9, 9, 10, 12, 14, 17, 20, 22, 24, 25, 25, 25, 24, 22, 20 },

{ 17, 14, 12, 10, 9, 8, 9, 10, 12, 14, 17, 20, 22, 24, 25, 26, 25, 24, 22, 20, 17, 14, 12, 10, 9, 8, 9, 10, 12, 14, 17, 20, 22, 24, 25, 26, 25, 24, 22, 20, 17, 14, 12, 10, 9, 8, 9, 10, 12, 14, 17, 20, 22, 24, 25, 26, 25, 24, 22, 20, 17, 14, 12, 10, 9, 8, 9, 10, 12, 14, 17, 20, 22, 24, 25, 26, 25, 24, 22, 20 },

{ 17, 14, 12, 10, 9, 9, 9, 10, 12, 14, 17, 20, 22, 24, 25, 25, 25, 24, 22, 20, 17, 14, 12, 10, 9, 9, 9, 10, 12, 14, 17, 20, 22, 24, 25, 25, 25, 24, 22, 20, 17, 14, 12, 10, 9, 9, 9, 10, 12, 14, 17, 20, 22, 24, 25, 25, 25, 24, 22, 20, 17, 14, 12, 10, 9, 9, 9, 10, 12, 14, 17, 20, 22, 24, 25, 25, 25, 24, 22, 20 },

{ 17, 15, 13, 11, 10, 10, 10, 11, 13, 15, 17, 19, 21, 23, 24, 24, 24, 23, 21, 19, 17, 15, 13, 11, 10, 10, 10, 11, 13, 15, 17, 19, 21, 23, 24, 24, 24, 23, 21, 19, 17, 15, 13, 11, 10, 10, 10, 11, 13, 15, 17, 19, 21, 23, 24, 24, 24, 23, 21, 19, 17, 15, 13, 11, 10, 10, 10, 11, 13, 15, 17, 19, 21, 23, 24, 24, 24, 23, 21, 19 },

{ 17, 15, 14, 13, 12, 11, 12, 13, 14, 15, 17, 19, 20, 21, 22, 23, 22, 21, 20, 19, 17, 15, 14, 13, 12, 11, 12, 13, 14, 15, 17, 19, 20, 21, 22, 23, 22, 21, 20, 19, 17, 15, 14, 13, 12, 11, 12, 13, 14, 15, 17, 19, 20, 21, 22, 23, 22, 21, 20, 19, 17, 15, 14, 13, 12, 11, 12, 13, 14, 15, 17, 19, 20, 21, 22, 23, 22, 21, 20, 19 },

{ 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18 },

{ 17, 17, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 17, 17, 17, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 17, 17, 17, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 17, 17, 17, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 17 },

{ 17, 18, 18, 18, 19, 19, 19, 18, 18, 18, 17, 16, 16, 16, 15, 15, 15, 16, 16, 16, 17, 18, 18, 18, 19, 19, 19, 18, 18, 18, 17, 16, 16, 16, 15, 15, 15, 16, 16, 16, 17, 18, 18, 18, 19, 19, 19, 18, 18, 18, 17, 16, 16, 16, 15, 15, 15, 16, 16, 16, 17, 18, 18, 18, 19, 19, 19, 18, 18, 18, 17, 16, 16, 16, 15, 15, 15, 16, 16, 16 },

{ 17, 18, 18, 19, 19, 19, 19, 19, 18, 18, 17, 16, 16, 15, 15, 15, 15, 15, 16, 16, 17, 18, 18, 19, 19, 19, 19, 19, 18, 18, 17, 16, 16, 15, 15, 15, 15, 15, 16, 16, 17, 18, 18, 19, 19, 19, 19, 19, 18, 18, 17, 16, 16, 15, 15, 15, 15, 15, 16, 16, 17, 18, 18, 19, 19, 19, 19, 19, 18, 18, 17, 16, 16, 15, 15, 15, 15, 15, 16, 16 },

{ 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16 },

{ 17, 18, 19, 20, 21, 21, 21, 20, 19, 18, 17, 16, 15, 14, 13, 13, 13, 14, 15, 16, 17, 18, 19, 20, 21, 21, 21, 20, 19, 18, 17, 16, 15, 14, 13, 13, 13, 14, 15, 16, 17, 18, 19, 20, 21, 21, 21, 20, 19, 18, 17, 16, 15, 14, 13, 13, 13, 14, 15, 16, 17, 18, 19, 20, 21, 21, 21, 20, 19, 18, 17, 16, 15, 14, 13, 13, 13, 14, 15, 16 },

{ 17, 18, 20, 20, 21, 21, 21, 20, 20, 18, 17, 16, 14, 14, 13, 13, 13, 14, 14, 16, 17, 18, 20, 20, 21, 21, 21, 20, 20, 18, 17, 16, 14, 14, 13, 13, 13, 14, 14, 16, 17, 18, 20, 20, 21, 21, 21, 20, 20, 18, 17, 16, 14, 14, 13, 13, 13, 14, 14, 16, 17, 18, 20, 20, 21, 21, 21, 20, 20, 18, 17, 16, 14, 14, 13, 13, 13, 14, 14, 16 },

{ 17, 18, 20, 21, 21, 21, 21, 21, 20, 18, 17, 16, 14, 13, 13, 13, 13, 13, 14, 16, 17, 18, 20, 21, 21, 21, 21, 21, 20, 18, 17, 16, 14, 13, 13, 13, 13, 13, 14, 16, 17, 18, 20, 21, 21, 21, 21, 21, 20, 18, 17, 16, 14, 13, 13, 13, 13, 13, 14, 16, 17, 18, 20, 21, 21, 21, 21, 21, 20, 18, 17, 16, 14, 13, 13, 13, 13, 13, 14, 16 },

{ 17, 18, 19, 20, 21, 21, 21, 20, 19, 18, 17, 16, 15, 14, 13, 13, 13, 14, 15, 16, 17, 18, 19, 20, 21, 21, 21, 20, 19, 18, 17, 16, 15, 14, 13, 13, 13, 14, 15, 16, 17, 18, 19, 20, 21, 21, 21, 20, 19, 18, 17, 16, 15, 14, 13, 13, 13, 14, 15, 16, 17, 18, 19, 20, 21, 21, 21, 20, 19, 18, 17, 16, 15, 14, 13, 13, 13, 14, 15, 16 },

{ 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16 },

{ 17, 18, 18, 19, 19, 19, 19, 19, 18, 18, 17, 16, 16, 15, 15, 15, 15, 15, 16, 16, 17, 18, 18, 19, 19, 19, 19, 19, 18, 18, 17, 16, 16, 15, 15, 15, 15, 15, 16, 16, 17, 18, 18, 19, 19, 19, 19, 19, 18, 18, 17, 16, 16, 15, 15, 15, 15, 15, 16, 16, 17, 18, 18, 19, 19, 19, 19, 19, 18, 18, 17, 16, 16, 15, 15, 15, 15, 15, 16, 16 },

{ 17, 17, 18, 18, 18, 18, 18, 18, 18, 17, 17, 17, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 17, 17, 17, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 17, 17, 17, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 17, 17, 17, 16, 16, 16, 16, 16, 16, 16, 17 }
 };

const uint8_t kernel_7800[549] = {
0xa9, 0x19, 0x85, 0x2c, 0xa9, 0x00, 0x85, 0x30, 0x85, 0x24, 0xa5, 0x28, 0x10, 0xfa, 0xae, 0xfc,
0x18, 0xae, 0xfd, 0x18, 0xae, 0xfe, 0x18, 0xae, 0xff, 0x18, 0xae, 0xdc, 0xf7, 0xe0, 0x25, 0xd0,
0x04, 0x85, 0x3c, 0x85, 0x24, 0xa9, 0x40, 0x85, 0x3c, 0x85, 0x24, 0xa5, 0x28, 0x30, 0xfa, 0x4c,
0x08, 0x18, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x25, 0x25, 0x25, 0x25,
0x0f, 0x18, 0xfa, 0x08, 0x18, 0xfa, 0x07, 0x1a, 0x00, 0x07, 0x1a, 0x00, 0x07, 0x1a, 0x00, 0x07,
0x1a, 0x00, 0x07, 0x1a, 0x00, 0x07, 0x1a, 0x00, 0x07, 0x1a, 0x00, 0x07, 0x1a, 0x00, 0x07, 0x1a,
0x00, 0x07, 0x1a, 0x00, 0x07, 0x1a, 0x00, 0x07, 0x1a, 0x00, 0x07, 0x1a, 0x00, 0x07, 0x1a, 0x00,
0x07, 0x1a, 0x00, 0x07, 0x1a, 0x00, 0x07, 0x1a, 0x00, 0x07, 0x1a, 0x00, 0x07, 0x1a, 0x00, 0x07,
0x1a, 0x00, 0x07, 0x1a, 0x00, 0x07, 0x1a, 0x00, 0x07, 0x1a, 0x00, 0x07, 0x1a, 0x00, 0x0f, 0x18,
0xfa, 0x0f, 0x18, 0xfa, 0x0f, 0x18, 0xfa, 0x0f, 0x18, 0xfa, 0x0f, 0x18, 0xfa, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xc0, 0x40, 0xf0, 0x0c, 0x00, 0xc0, 0x40, 0xf0, 0x0c, 0x50, 0xc0, 0x40, 0xf0, 0x0c, 0x50, 0xc0,
0xc0, 0xf0, 0x80, 0x00, 0xc0, 0xc0, 0xf0, 0x80, 0x40, 0xc0, 0xc0, 0xf0, 0x90, 0x80, 0xc0, 0xc0,
0xf0, 0x90, 0x80, 0x00, 0x00};

const track_t SongMiniBlast =
{
	.channels = { {(sequence_t[]){{ .goto_index=-1, .pattern_index=4 },
{ .goto_index=-1, .pattern_index=4 },
{ .goto_index=-1, .pattern_index=0 },
{ .goto_index=-1, .pattern_index=2 },
{ .goto_index=-1, .pattern_index=0 },
{ .goto_index=-1, .pattern_index=2 },
{ .goto_index=-1, .pattern_index=5 },
{ .goto_index=-1, .pattern_index=7 },
{ .goto_index=-1, .pattern_index=7 },
{ .goto_index=-1, .pattern_index=8 },
{ .goto_index=0, .pattern_index=8 }}}, {(sequence_t[]){{ .goto_index=-1, .pattern_index=1 },
{ .goto_index=-1, .pattern_index=3 },
{ .goto_index=-1, .pattern_index=1 },
{ .goto_index=-1, .pattern_index=3 },
{ .goto_index=-1, .pattern_index=1 },
{ .goto_index=-1, .pattern_index=3 },
{ .goto_index=-1, .pattern_index=6 },
{ .goto_index=-1, .pattern_index=1 },
{ .goto_index=-1, .pattern_index=3 },
{ .goto_index=-1, .pattern_index=1 },
{ .goto_index=2, .pattern_index=3 }}} },
	.instruments = (instrument_t[]){   {
   // Chords
   .frequencies = (int8_t[]) { -6, -2, 0, 0, 0, 0 },
   .volumes = (uint8_t[]) { 7, 12, 14, 14, 2, 0 },
   .sustainStart = 4,
   .releaseStart = 5,
   .waveform = 12,
   .length = 6
},
   {
   // bassline
   .frequencies = (int8_t[]) { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
   .volumes = (uint8_t[]) { 0, 15, 15, 15, 15, 15, 15, 15, 0, 0 },
   .sustainStart = 8,
   .releaseStart = 9,
   .waveform = 6,
   .length = 10
},
   {
   // Guitoune
   .frequencies = (int8_t[]) { 7, -6, -6, -6, -5, -6, -6, -6, 7, 7 },
   .volumes = (uint8_t[]) { 0, 5, 8, 10, 12, 10, 8, 5, 0, 0 },
   .sustainStart = 8,
   .releaseStart = 9,
   .waveform = 15,
   .length = 10
},
   {
   // Chords2
   .frequencies = (int8_t[]) { -1, 0, -1, -1, -1, -1 },
   .volumes = (uint8_t[]) { 0, 8, 12, 12, 0, 0 },
   .sustainStart = 4,
   .releaseStart = 5,
   .waveform = 4,
   .length = 6
},
   {
   // Chords2
   .frequencies = (int8_t[]) { -1, 0, -1, -1, -1, -1 },
   .volumes = (uint8_t[]) { 0, 8, 12, 12, 0, 0 },
   .sustainStart = 4,
   .releaseStart = 5,
   .waveform = 12,
   .length = 6
}},
	.percussions = (percussion_t[]){   {
   // Break SD
   .frequencies = (uint8_t[]) { 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17 },
   .volumes = (uint8_t[]) { 10, 10, 9, 9, 8, 8, 8, 7, 7, 7, 6, 4, 3, 3, 1, 0 },
   .waveforms = (uint8_t[]) { 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 },
   .length = 16
},
   {
   // Snare
   .frequencies = (uint8_t[]) { 7, 13, 14, 16, 20, 20, 21, 24, 24, 25, 26, 27, 30, 31 },
   .volumes = (uint8_t[]) { 14, 13, 13, 12, 11, 10, 8, 8, 7, 6, 4, 2, 1, 0 },
   .waveforms = (uint8_t[]) { 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 },
   .length = 14
},
   {
   // hi
   .frequencies = (uint8_t[]) { 0, 4, 4 },
   .volumes = (uint8_t[]) { 15, 10, 4 },
   .waveforms = (uint8_t[]) { 8, 8, 8 },
   .length = 3
}},
	.patterns = (pattern_t[]){   {
   // mel0
   .even_speed = 4,
   .odd_speed = 4,
   .notes = (uint8_t[]) { 0x36, 0x08, 0x08, 0x08, 0x36, 0x08, 0x36, 0x08,
0x32, 0x08, 0x36, 0x08, 0x36, 0x08, 0x36, 0x08,
0x32, 0x08, 0x36, 0x08, 0x13, 0x08, 0x08, 0x08,
0x36, 0x08, 0x11, 0x08, 0x11, 0x08, 0x08, 0x08,
0x32, 0x08, 0x08, 0x08, 0x32, 0x08, 0x32, 0x08,
0x2e, 0x08, 0x32, 0x08, 0x32, 0x08, 0x32, 0x08,
0x2e, 0x08, 0x32, 0x08, 0x13, 0x08, 0x08, 0x08,
0x32, 0x08, 0x11, 0x08, 0x11, 0x08, 0x08, 0x08,
0x00 }
},
   {
   // bass+drum0
   .even_speed = 4,
   .odd_speed = 4,
   .notes = (uint8_t[]) { 0x51, 0x08, 0x08, 0x08, 0x13, 0x08, 0x51, 0x08,
0x12, 0x08, 0x08, 0x08, 0x51, 0x08, 0x08, 0x08,
0x51, 0x08, 0x08, 0x08, 0x51, 0x08, 0x08, 0x08,
0x12, 0x08, 0x51, 0x08, 0x51, 0x08, 0x08, 0x08,
0x4e, 0x08, 0x08, 0x08, 0x13, 0x08, 0x4e, 0x08,
0x12, 0x08, 0x08, 0x08, 0x4e, 0x08, 0x08, 0x08,
0x4e, 0x08, 0x08, 0x08, 0x4e, 0x08, 0x08, 0x08,
0x12, 0x08, 0x4e, 0x08, 0x4e, 0x08, 0x08, 0x08,
0x00 }
},
   {
   // mel1
   .even_speed = 4,
   .odd_speed = 4,
   .notes = (uint8_t[]) { 0x38, 0x08, 0x08, 0x08, 0x38, 0x08, 0x38, 0x08,
0x33, 0x08, 0x38, 0x08, 0x38, 0x08, 0x38, 0x08,
0x33, 0x08, 0x38, 0x08, 0x13, 0x08, 0x08, 0x08,
0x38, 0x08, 0x11, 0x08, 0x11, 0x08, 0x08, 0x08,
0x36, 0x08, 0x08, 0x08, 0x36, 0x08, 0x36, 0x08,
0x32, 0x08, 0x36, 0x08, 0x36, 0x08, 0x36, 0x08,
0x32, 0x08, 0x36, 0x08, 0x13, 0x08, 0x08, 0x08,
0x36, 0x08, 0x11, 0x08, 0x11, 0x08, 0x08, 0x08,
0x00 }
},
   {
   // bass+drum1
   .even_speed = 4,
   .odd_speed = 4,
   .notes = (uint8_t[]) { 0x53, 0x08, 0x08, 0x08, 0x13, 0x08, 0x53, 0x08,
0x12, 0x08, 0x08, 0x08, 0x53, 0x08, 0x08, 0x08,
0x53, 0x08, 0x08, 0x08, 0x53, 0x08, 0x08, 0x08,
0x12, 0x08, 0x53, 0x08, 0x53, 0x08, 0x08, 0x08,
0x51, 0x08, 0x08, 0x08, 0x13, 0x08, 0x51, 0x08,
0x12, 0x08, 0x08, 0x08, 0x51, 0x08, 0x08, 0x08,
0x51, 0x08, 0x08, 0x08, 0x51, 0x08, 0x08, 0x08,
0x12, 0x08, 0x51, 0x08, 0x51, 0x08, 0x08, 0x08,
0x00 }
},
   {
   // mel2
   .even_speed = 4,
   .odd_speed = 4,
   .notes = (uint8_t[]) { 0x67, 0x08, 0x08, 0x08, 0x08, 0x08, 0x68, 0x08,
0x67, 0x08, 0x67, 0x08, 0x08, 0x08, 0x67, 0x08,
0x08, 0x08, 0x68, 0x08, 0x67, 0x08, 0x68, 0x08,
0x67, 0x08, 0x68, 0x08, 0x67, 0x08, 0x68, 0x08,
0x67, 0x08, 0x08, 0x08, 0x08, 0x08, 0x68, 0x08,
0x67, 0x08, 0x67, 0x08, 0x08, 0x08, 0x67, 0x08,
0x08, 0x08, 0x68, 0x08, 0x67, 0x08, 0x68, 0x08,
0x67, 0x08, 0x68, 0x08, 0x67, 0x08, 0x68, 0x08,
0x00 }
},
   {
   // mel3
   .even_speed = 4,
   .odd_speed = 4,
   .notes = (uint8_t[]) { 0x36, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
0x36, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
0x36, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
0x36, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
0x36, 0x08, 0x08, 0x08, 0x36, 0x08, 0x08, 0x08,
0x36, 0x08, 0x08, 0x08, 0x36, 0x08, 0x08, 0x08,
0x36, 0x08, 0x08, 0x08, 0x36, 0x08, 0x08, 0x08,
0x36, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
0x00 }
},
   {
   // drum0
   .even_speed = 4,
   .odd_speed = 4,
   .notes = (uint8_t[]) { 0x08, 0x08, 0x08, 0x08, 0x13, 0x08, 0x08, 0x08,
0x12, 0x08, 0x08, 0x08, 0x13, 0x08, 0x08, 0x08,
0x13, 0x08, 0x13, 0x08, 0x13, 0x08, 0x08, 0x08,
0x12, 0x08, 0x11, 0x08, 0x11, 0x08, 0x08, 0x08,
0x08, 0x08, 0x08, 0x08, 0x13, 0x08, 0x08, 0x08,
0x12, 0x08, 0x08, 0x08, 0x13, 0x08, 0x08, 0x08,
0x13, 0x08, 0x13, 0x08, 0x13, 0x08, 0x13, 0x08,
0x12, 0x08, 0x11, 0x08, 0x11, 0x08, 0x13, 0x08,
0x00 }
},
   {
   // mel4
   .even_speed = 4,
   .odd_speed = 4,
   .notes = (uint8_t[]) { 0xb7, 0x08, 0x08, 0x08, 0x08, 0x08, 0xaf, 0x08,
0x08, 0x08, 0x08, 0x08, 0xab, 0x08, 0x08, 0x08,
0x08, 0x08, 0x08, 0x08, 0x13, 0x08, 0x08, 0x08,
0x08, 0x08, 0x11, 0x08, 0x11, 0x08, 0xb7, 0x08,
0xb7, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0xaf,
0x08, 0x08, 0x08, 0x08, 0xab, 0x08, 0x08, 0x08,
0x08, 0x08, 0x08, 0x08, 0x13, 0x08, 0xb7, 0x08,
0xb7, 0x08, 0x11, 0x08, 0x11, 0x08, 0xb7, 0x08,
0x00 }
},
   {
   // mel5
   .even_speed = 4,
   .odd_speed = 4,
   .notes = (uint8_t[]) { 0x67, 0xb7, 0x08, 0x08, 0x08, 0x08, 0x68, 0xaf,
0x67, 0x08, 0x67, 0x08, 0xab, 0x08, 0x67, 0x08,
0x08, 0x08, 0x68, 0x08, 0x13, 0x08, 0x68, 0x08,
0x67, 0x08, 0x68, 0x08, 0x11, 0x08, 0x68, 0xb7,
0x67, 0xb7, 0x08, 0x08, 0x08, 0x08, 0x68, 0xaf,
0x67, 0x08, 0x67, 0x08, 0xab, 0x08, 0x67, 0x08,
0x08, 0x08, 0x68, 0x08, 0x67, 0x08, 0x68, 0xb7,
0x11, 0xb7, 0x11, 0xb7, 0x67, 0xb7, 0x68, 0xb7,
0x00 }
}}
};


const track_t SfxBounce =
{
	.channels = { {(sequence_t[]){{ .goto_index=0, .pattern_index=0 }}}, {(sequence_t[]){{ .goto_index=-1, .pattern_index=1 }}} },
	.instruments = (instrument_t[]){   {
   // Simple
   .frequencies = (int8_t[]) { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
   .volumes = (uint8_t[]) { 15, 13, 9, 8, 6, 5, 3, 2, 1, 0, 0, 0 },
   .sustainStart = 3,
   .releaseStart = 4,
   .waveform = 4,
   .length = 12
},
   {
   // Simple
   .frequencies = (int8_t[]) { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
   .volumes = (uint8_t[]) { 15, 13, 9, 8, 6, 5, 3, 2, 1, 0, 0, 0 },
   .sustainStart = 3,
   .releaseStart = 4,
   .waveform = 12,
   .length = 12
},
   {
   // Flute
   .frequencies = (int8_t[]) { 0, 0 },
   .volumes = (uint8_t[]) { 0, 0 },
   .sustainStart = 0,
   .releaseStart = 1,
   .waveform = 7,
   .length = 2
}},
	.percussions = (percussion_t[]){   {
   // bed-bounce
   .frequencies = (uint8_t[]) { 30, 23, 18, 23, 20, 15, 9, 3 },
   .volumes = (uint8_t[]) { 10, 9, 9, 8, 7, 6, 4, 1 },
   .waveforms = (uint8_t[]) { 12, 12, 12, 4, 4, 4, 4, 4 },
   .length = 8
},
   {
   // Gunshot - pistol
   .frequencies = (uint8_t[]) { 28, 29, 26, 21, 5, 3, 5, 6, 6, 6 },
   .volumes = (uint8_t[]) { 12, 8, 8, 6, 3, 6, 8, 5, 3, 1 },
   .waveforms = (uint8_t[]) { 7, 7, 7, 7, 8, 8, 8, 8, 8, 8 },
   .length = 10
}},
	.patterns = (pattern_t[]){   {
   // Intro left
   .even_speed = 8,
   .odd_speed = 8,
   .notes = (uint8_t[]) { 0x12, 0x00 }
},
   {
   // Intro right
   .even_speed = 8,
   .odd_speed = 8,
   .notes = (uint8_t[]) { 0x11, 0x00 }
}}
};
