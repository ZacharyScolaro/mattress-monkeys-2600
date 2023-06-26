#include "sprites.h"

const uint8_t ScoreSpritesGraphics[14*19] = { 0x1c, 0x10, 0x3c, 0x3e, 0x0e, 0x7e, 0x1e, 0x3f, 0x3c, 0x3e, 0x3e, 0x7e, 0x1f, 0x7e, 0x7e, 0x7e, 0x00, 0x00, 0x00, 0x1c, 0x10, 0x3c, 0x3e, 0x0e, 0x7e, 0x1e, 0x3f, 0x3c, 0x3e, 0x3e, 0x7e, 0x1f, 0x7e, 0x7e, 0x7e, 0x00, 0x00, 0x00, 0x26, 0x30, 0x66, 0x04, 0x1e, 0x40, 0x30, 0x23, 0x62, 0x63, 0x63, 0x63, 0x30, 0x63, 0x60, 0x60, 0x00, 0x00, 0x08, 0x26, 0x30, 0x66, 0x04, 0x1e, 0x40, 0x30, 0x23, 0x62, 0x63, 0x63, 0x63, 0x30, 0x63, 0x60, 0x60, 0x00, 0x00, 0x08, 0x63, 0x10, 0x06, 0x08, 0x36, 0x7e, 0x60, 0x06, 0x72, 0x63, 0x63, 0x63, 0x60, 0x63, 0x60, 0x60, 0x00, 0x22, 0x00, 0x63, 0x10, 0x06, 0x08, 0x36, 0x7e, 0x60, 0x06, 0x72, 0x63, 0x63, 0x63, 0x60, 0x63, 0x60, 0x60, 0x00, 0x22, 0x00, 0x63, 0x10, 0x1c, 0x1c, 0x66, 0x03, 0x7e, 0x0c, 0x3c, 0x3f, 0x7f, 0x7f, 0x60, 0x63, 0x7c, 0x7c, 0x00, 0x14, 0x1c, 0x63, 0x10, 0x1c, 0x1c, 0x66, 0x03, 0x7e, 0x0c, 0x3c, 0x3f, 0x7f, 0x7f, 0x60, 0x63, 0x7c, 0x7c, 0x00, 0x14, 0x1c, 0x63, 0x10, 0x30, 0x06, 0x7f, 0x03, 0x63, 0x18, 0x43, 0x03, 0x63, 0x63, 0x60, 0x63, 0x60, 0x60, 0x00, 0x08, 0x08, 0x63, 0x10, 0x30, 0x06, 0x7f, 0x03, 0x63, 0x18, 0x43, 0x03, 0x63, 0x63, 0x60, 0x63, 0x60, 0x60, 0x00, 0x08, 0x08, 0x32, 0x10, 0x60, 0x66, 0x06, 0x63, 0x63, 0x18, 0x43, 0x06, 0x63, 0x63, 0x30, 0x63, 0x60, 0x60, 0x00, 0x14, 0x00, 0x32, 0x10, 0x60, 0x66, 0x06, 0x63, 0x63, 0x18, 0x43, 0x06, 0x63, 0x63, 0x30, 0x63, 0x60, 0x60, 0x00, 0x14, 0x00, 0x1c, 0x7c, 0x7e, 0x38, 0x06, 0x3e, 0x3e, 0x18, 0x3e, 0x3c, 0x63, 0x7e, 0x1f, 0x7e, 0x7e, 0x60, 0x00, 0x22, 0x14, 0x1c, 0x7c, 0x7e, 0x38, 0x06, 0x3e, 0x3e, 0x18, 0x3e, 0x3c, 0x63, 0x7e, 0x1f, 0x7e, 0x7e, 0x60, 0x00, 0x22, 0x14 };

const uint8_t FanBladeGraphics[7][14] = { 
{ 0x80, 0x00, 0xc0, 0x00, 0xe0, 0x00, 0xf3, 0xc0, 0x01, 0xc0, 0x00, 0xc0, 0x00, 0x40 },

{ 0x00, 0x00, 0x20, 0x00, 0x30, 0x00, 0x33, 0x00, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00 },

{ 0x00, 0x00, 0x10, 0x00, 0x10, 0x00, 0x12, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00 },

{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },

{ 0x00, 0x00, 0x02, 0x00, 0x02, 0x00, 0x12, 0x00, 0x10, 0x00, 0x10, 0x00, 0x00, 0x00 },

{ 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 0x33, 0x00, 0x30, 0x00, 0x20, 0x00, 0x00, 0x00 },

{ 0x00, 0x40, 0x00, 0xc0, 0x01, 0xc0, 0xf3, 0xc0, 0xe0, 0x00, 0xc0, 0x00, 0x80, 0x00 }
 };

const uint8_t FanBladeColu[7] = { 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e };

const uint8_t MonkeyWalkingGraphics[2][12] = { 
{ 0xe0, 0xf1, 0xe2, 0xd2, 0x39, 0x7d, 0x5d, 0x9e, 0xbc, 0xb0, 0x88, 0x58 },

{ 0x01, 0xe2, 0xf2, 0xe1, 0xd9, 0x3d, 0x3e, 0x5c, 0x5c, 0x93, 0x85, 0x0c }
 };

const uint8_t MonkeyWalkingColu[12] = { 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e };

const uint8_t MonkeyIdleGraphics[12] = { 0xe0, 0xf1, 0xe2, 0xd2, 0x39, 0x7d, 0x5d, 0x9e, 0xbc, 0xb0, 0x88, 0x58 };

const uint8_t MonkeyIdleColu[12] = { 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e };

const uint8_t FanChasisGraphics[28] = { 0xff, 0xff, 0x7e, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e, 0xff, 0xff, 0x18, 0xff, 0xff, 0xff, 0x7e, 0x7e, 0x3c, 0x18 };

const uint8_t FanChasisColu[28] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x1e, 0x1e, 0x1e };

const uint8_t BonusBananaGraphics[13] = { 0x20, 0x30, 0x30, 0x18, 0x18, 0x18, 0x3c, 0x5a, 0x1a, 0x38, 0x30, 0x70, 0x60 };

const uint8_t BonusBananaColu[13] = { 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e };

const uint8_t HeadBoardWideGraphics[200] = { 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0xff, 0x80, 0x00, 0x01, 0xc0, 0xff, 0x81, 0xc0, 0x01, 0xc1, 0xff, 0xc1, 0xc0, 0x01, 0xe1, 0xff, 0xc3, 0xc0, 0x01, 0xe3, 0xff, 0xe3, 0xc0, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0x80 };

const uint8_t HeadBoardWideColu[40] = { 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c };

const uint8_t SineTables[32][80] = { 
{ 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17 },

{ 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16 },

{ 17, 19, 21, 22, 23, 24, 23, 22, 21, 19, 17, 15, 13, 12, 11, 10, 11, 12, 13, 15, 17, 19, 21, 22, 23, 24, 23, 22, 21, 19, 17, 15, 13, 12, 11, 10, 11, 12, 13, 15, 17, 19, 21, 22, 23, 24, 23, 22, 21, 19, 17, 15, 13, 12, 11, 10, 11, 12, 13, 15, 17, 19, 21, 22, 23, 24, 23, 22, 21, 19, 17, 15, 13, 12, 11, 10, 11, 12, 13, 15 },

{ 17, 20, 23, 25, 26, 27, 26, 25, 23, 20, 17, 14, 11, 9, 8, 7, 8, 9, 11, 14, 17, 20, 23, 25, 26, 27, 26, 25, 23, 20, 17, 14, 11, 9, 8, 7, 8, 9, 11, 14, 17, 20, 23, 25, 26, 27, 26, 25, 23, 20, 17, 14, 11, 9, 8, 7, 8, 9, 11, 14, 17, 20, 23, 25, 26, 27, 26, 25, 23, 20, 17, 14, 11, 9, 8, 7, 8, 9, 11, 14 },

{ 17, 21, 24, 27, 29, 29, 29, 27, 24, 21, 17, 13, 10, 7, 5, 5, 5, 7, 10, 13, 17, 21, 24, 27, 29, 29, 29, 27, 24, 21, 17, 13, 10, 7, 5, 5, 5, 7, 10, 13, 17, 21, 24, 27, 29, 29, 29, 27, 24, 21, 17, 13, 10, 7, 5, 5, 5, 7, 10, 13, 17, 21, 24, 27, 29, 29, 29, 27, 24, 21, 17, 13, 10, 7, 5, 5, 5, 7, 10, 13 },

{ 17, 21, 26, 29, 31, 32, 31, 29, 26, 21, 17, 13, 8, 5, 3, 2, 3, 5, 8, 13, 17, 21, 26, 29, 31, 32, 31, 29, 26, 21, 17, 13, 8, 5, 3, 2, 3, 5, 8, 13, 17, 21, 26, 29, 31, 32, 31, 29, 26, 21, 17, 13, 8, 5, 3, 2, 3, 5, 8, 13, 17, 21, 26, 29, 31, 32, 31, 29, 26, 21, 17, 13, 8, 5, 3, 2, 3, 5, 8, 13 },

{ 17, 22, 27, 30, 32, 33, 32, 30, 27, 22, 17, 12, 7, 4, 2, 1, 2, 4, 7, 12, 17, 22, 27, 30, 32, 33, 32, 30, 27, 22, 17, 12, 7, 4, 2, 1, 2, 4, 7, 12, 17, 22, 27, 30, 32, 33, 32, 30, 27, 22, 17, 12, 7, 4, 2, 1, 2, 4, 7, 12, 17, 22, 27, 30, 32, 33, 32, 30, 27, 22, 17, 12, 7, 4, 2, 1, 2, 4, 7, 12 },

{ 17, 22, 27, 31, 33, 34, 33, 31, 27, 22, 17, 12, 7, 3, 1, 0, 1, 3, 7, 12, 17, 22, 27, 31, 33, 34, 33, 31, 27, 22, 17, 12, 7, 3, 1, 0, 1, 3, 7, 12, 17, 22, 27, 31, 33, 34, 33, 31, 27, 22, 17, 12, 7, 3, 1, 0, 1, 3, 7, 12, 17, 22, 27, 31, 33, 34, 33, 31, 27, 22, 17, 12, 7, 3, 1, 0, 1, 3, 7, 12 },

{ 17, 22, 27, 31, 34, 35, 34, 31, 27, 22, 17, 12, 7, 3, 0, 0, 0, 3, 7, 12, 17, 22, 27, 31, 34, 35, 34, 31, 27, 22, 17, 12, 7, 3, 0, 0, 0, 3, 7, 12, 17, 22, 27, 31, 34, 35, 34, 31, 27, 22, 17, 12, 7, 3, 0, 0, 0, 3, 7, 12, 17, 22, 27, 31, 34, 35, 34, 31, 27, 22, 17, 12, 7, 3, 0, 0, 0, 3, 7, 12 },

{ 17, 22, 27, 31, 33, 34, 33, 31, 27, 22, 17, 12, 7, 3, 1, 0, 1, 3, 7, 12, 17, 22, 27, 31, 33, 34, 33, 31, 27, 22, 17, 12, 7, 3, 1, 0, 1, 3, 7, 12, 17, 22, 27, 31, 33, 34, 33, 31, 27, 22, 17, 12, 7, 3, 1, 0, 1, 3, 7, 12, 17, 22, 27, 31, 33, 34, 33, 31, 27, 22, 17, 12, 7, 3, 1, 0, 1, 3, 7, 12 },

{ 17, 22, 27, 30, 32, 33, 32, 30, 27, 22, 17, 12, 7, 4, 2, 1, 2, 4, 7, 12, 17, 22, 27, 30, 32, 33, 32, 30, 27, 22, 17, 12, 7, 4, 2, 1, 2, 4, 7, 12, 17, 22, 27, 30, 32, 33, 32, 30, 27, 22, 17, 12, 7, 4, 2, 1, 2, 4, 7, 12, 17, 22, 27, 30, 32, 33, 32, 30, 27, 22, 17, 12, 7, 4, 2, 1, 2, 4, 7, 12 },

{ 17, 21, 26, 29, 31, 32, 31, 29, 26, 21, 17, 13, 8, 5, 3, 2, 3, 5, 8, 13, 17, 21, 26, 29, 31, 32, 31, 29, 26, 21, 17, 13, 8, 5, 3, 2, 3, 5, 8, 13, 17, 21, 26, 29, 31, 32, 31, 29, 26, 21, 17, 13, 8, 5, 3, 2, 3, 5, 8, 13, 17, 21, 26, 29, 31, 32, 31, 29, 26, 21, 17, 13, 8, 5, 3, 2, 3, 5, 8, 13 },

{ 17, 21, 24, 27, 29, 29, 29, 27, 24, 21, 17, 13, 10, 7, 5, 5, 5, 7, 10, 13, 17, 21, 24, 27, 29, 29, 29, 27, 24, 21, 17, 13, 10, 7, 5, 5, 5, 7, 10, 13, 17, 21, 24, 27, 29, 29, 29, 27, 24, 21, 17, 13, 10, 7, 5, 5, 5, 7, 10, 13, 17, 21, 24, 27, 29, 29, 29, 27, 24, 21, 17, 13, 10, 7, 5, 5, 5, 7, 10, 13 },

{ 17, 20, 23, 25, 26, 27, 26, 25, 23, 20, 17, 14, 11, 9, 8, 7, 8, 9, 11, 14, 17, 20, 23, 25, 26, 27, 26, 25, 23, 20, 17, 14, 11, 9, 8, 7, 8, 9, 11, 14, 17, 20, 23, 25, 26, 27, 26, 25, 23, 20, 17, 14, 11, 9, 8, 7, 8, 9, 11, 14, 17, 20, 23, 25, 26, 27, 26, 25, 23, 20, 17, 14, 11, 9, 8, 7, 8, 9, 11, 14 },

{ 17, 19, 21, 22, 23, 24, 23, 22, 21, 19, 17, 15, 13, 12, 11, 10, 11, 12, 13, 15, 17, 19, 21, 22, 23, 24, 23, 22, 21, 19, 17, 15, 13, 12, 11, 10, 11, 12, 13, 15, 17, 19, 21, 22, 23, 24, 23, 22, 21, 19, 17, 15, 13, 12, 11, 10, 11, 12, 13, 15, 17, 19, 21, 22, 23, 24, 23, 22, 21, 19, 17, 15, 13, 12, 11, 10, 11, 12, 13, 15 },

{ 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16 },

{ 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17 },

{ 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18 },

{ 17, 15, 13, 12, 11, 10, 11, 12, 13, 15, 17, 19, 21, 22, 23, 24, 23, 22, 21, 19, 17, 15, 13, 12, 11, 10, 11, 12, 13, 15, 17, 19, 21, 22, 23, 24, 23, 22, 21, 19, 17, 15, 13, 12, 11, 10, 11, 12, 13, 15, 17, 19, 21, 22, 23, 24, 23, 22, 21, 19, 17, 15, 13, 12, 11, 10, 11, 12, 13, 15, 17, 19, 21, 22, 23, 24, 23, 22, 21, 19 },

{ 17, 14, 11, 9, 8, 7, 8, 9, 11, 14, 17, 20, 23, 25, 26, 27, 26, 25, 23, 20, 17, 14, 11, 9, 8, 7, 8, 9, 11, 14, 17, 20, 23, 25, 26, 27, 26, 25, 23, 20, 17, 14, 11, 9, 8, 7, 8, 9, 11, 14, 17, 20, 23, 25, 26, 27, 26, 25, 23, 20, 17, 14, 11, 9, 8, 7, 8, 9, 11, 14, 17, 20, 23, 25, 26, 27, 26, 25, 23, 20 },

{ 17, 13, 10, 7, 5, 5, 5, 7, 10, 13, 17, 21, 24, 27, 29, 29, 29, 27, 24, 21, 17, 13, 10, 7, 5, 5, 5, 7, 10, 13, 17, 21, 24, 27, 29, 29, 29, 27, 24, 21, 17, 13, 10, 7, 5, 5, 5, 7, 10, 13, 17, 21, 24, 27, 29, 29, 29, 27, 24, 21, 17, 13, 10, 7, 5, 5, 5, 7, 10, 13, 17, 21, 24, 27, 29, 29, 29, 27, 24, 21 },

{ 17, 13, 8, 5, 3, 2, 3, 5, 8, 13, 17, 21, 26, 29, 31, 32, 31, 29, 26, 21, 17, 13, 8, 5, 3, 2, 3, 5, 8, 13, 17, 21, 26, 29, 31, 32, 31, 29, 26, 21, 17, 13, 8, 5, 3, 2, 3, 5, 8, 13, 17, 21, 26, 29, 31, 32, 31, 29, 26, 21, 17, 13, 8, 5, 3, 2, 3, 5, 8, 13, 17, 21, 26, 29, 31, 32, 31, 29, 26, 21 },

{ 17, 12, 7, 4, 2, 1, 2, 4, 7, 12, 17, 22, 27, 30, 32, 33, 32, 30, 27, 22, 17, 12, 7, 4, 2, 1, 2, 4, 7, 12, 17, 22, 27, 30, 32, 33, 32, 30, 27, 22, 17, 12, 7, 4, 2, 1, 2, 4, 7, 12, 17, 22, 27, 30, 32, 33, 32, 30, 27, 22, 17, 12, 7, 4, 2, 1, 2, 4, 7, 12, 17, 22, 27, 30, 32, 33, 32, 30, 27, 22 },

{ 17, 12, 7, 3, 1, 0, 1, 3, 7, 12, 17, 22, 27, 31, 33, 34, 33, 31, 27, 22, 17, 12, 7, 3, 1, 0, 1, 3, 7, 12, 17, 22, 27, 31, 33, 34, 33, 31, 27, 22, 17, 12, 7, 3, 1, 0, 1, 3, 7, 12, 17, 22, 27, 31, 33, 34, 33, 31, 27, 22, 17, 12, 7, 3, 1, 0, 1, 3, 7, 12, 17, 22, 27, 31, 33, 34, 33, 31, 27, 22 },

{ 17, 12, 7, 3, 0, 0, 0, 3, 7, 12, 17, 22, 27, 31, 34, 35, 34, 31, 27, 22, 17, 12, 7, 3, 0, 0, 0, 3, 7, 12, 17, 22, 27, 31, 34, 35, 34, 31, 27, 22, 17, 12, 7, 3, 0, 0, 0, 3, 7, 12, 17, 22, 27, 31, 34, 35, 34, 31, 27, 22, 17, 12, 7, 3, 0, 0, 0, 3, 7, 12, 17, 22, 27, 31, 34, 35, 34, 31, 27, 22 },

{ 17, 12, 7, 3, 1, 0, 1, 3, 7, 12, 17, 22, 27, 31, 33, 34, 33, 31, 27, 22, 17, 12, 7, 3, 1, 0, 1, 3, 7, 12, 17, 22, 27, 31, 33, 34, 33, 31, 27, 22, 17, 12, 7, 3, 1, 0, 1, 3, 7, 12, 17, 22, 27, 31, 33, 34, 33, 31, 27, 22, 17, 12, 7, 3, 1, 0, 1, 3, 7, 12, 17, 22, 27, 31, 33, 34, 33, 31, 27, 22 },

{ 17, 12, 7, 4, 2, 1, 2, 4, 7, 12, 17, 22, 27, 30, 32, 33, 32, 30, 27, 22, 17, 12, 7, 4, 2, 1, 2, 4, 7, 12, 17, 22, 27, 30, 32, 33, 32, 30, 27, 22, 17, 12, 7, 4, 2, 1, 2, 4, 7, 12, 17, 22, 27, 30, 32, 33, 32, 30, 27, 22, 17, 12, 7, 4, 2, 1, 2, 4, 7, 12, 17, 22, 27, 30, 32, 33, 32, 30, 27, 22 },

{ 17, 13, 8, 5, 3, 2, 3, 5, 8, 13, 17, 21, 26, 29, 31, 32, 31, 29, 26, 21, 17, 13, 8, 5, 3, 2, 3, 5, 8, 13, 17, 21, 26, 29, 31, 32, 31, 29, 26, 21, 17, 13, 8, 5, 3, 2, 3, 5, 8, 13, 17, 21, 26, 29, 31, 32, 31, 29, 26, 21, 17, 13, 8, 5, 3, 2, 3, 5, 8, 13, 17, 21, 26, 29, 31, 32, 31, 29, 26, 21 },

{ 17, 13, 10, 7, 5, 5, 5, 7, 10, 13, 17, 21, 24, 27, 29, 29, 29, 27, 24, 21, 17, 13, 10, 7, 5, 5, 5, 7, 10, 13, 17, 21, 24, 27, 29, 29, 29, 27, 24, 21, 17, 13, 10, 7, 5, 5, 5, 7, 10, 13, 17, 21, 24, 27, 29, 29, 29, 27, 24, 21, 17, 13, 10, 7, 5, 5, 5, 7, 10, 13, 17, 21, 24, 27, 29, 29, 29, 27, 24, 21 },

{ 17, 14, 11, 9, 8, 7, 8, 9, 11, 14, 17, 20, 23, 25, 26, 27, 26, 25, 23, 20, 17, 14, 11, 9, 8, 7, 8, 9, 11, 14, 17, 20, 23, 25, 26, 27, 26, 25, 23, 20, 17, 14, 11, 9, 8, 7, 8, 9, 11, 14, 17, 20, 23, 25, 26, 27, 26, 25, 23, 20, 17, 14, 11, 9, 8, 7, 8, 9, 11, 14, 17, 20, 23, 25, 26, 27, 26, 25, 23, 20 },

{ 17, 15, 13, 12, 11, 10, 11, 12, 13, 15, 17, 19, 21, 22, 23, 24, 23, 22, 21, 19, 17, 15, 13, 12, 11, 10, 11, 12, 13, 15, 17, 19, 21, 22, 23, 24, 23, 22, 21, 19, 17, 15, 13, 12, 11, 10, 11, 12, 13, 15, 17, 19, 21, 22, 23, 24, 23, 22, 21, 19, 17, 15, 13, 12, 11, 10, 11, 12, 13, 15, 17, 19, 21, 22, 23, 24, 23, 22, 21, 19 },

{ 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18, 17, 16, 15, 14, 14, 14, 14, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 19, 18 }
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
	.channels = { {(sequence_t[]){{ .goto_index=-1, .pattern_index=1 },
{ .goto_index=-1, .pattern_index=1 },
{ .goto_index=-1, .pattern_index=1 },
{ .goto_index=-1, .pattern_index=1 },
{ .goto_index=-1, .pattern_index=1 },
{ .goto_index=-1, .pattern_index=1 },
{ .goto_index=-1, .pattern_index=1 },
{ .goto_index=-1, .pattern_index=1 },
{ .goto_index=-1, .pattern_index=1 },
{ .goto_index=-1, .pattern_index=1 },
{ .goto_index=-1, .pattern_index=1 },
{ .goto_index=-1, .pattern_index=1 },
{ .goto_index=-1, .pattern_index=1 },
{ .goto_index=-1, .pattern_index=1 },
{ .goto_index=-1, .pattern_index=1 },
{ .goto_index=-1, .pattern_index=4 },
{ .goto_index=-1, .pattern_index=6 },
{ .goto_index=-1, .pattern_index=6 },
{ .goto_index=-1, .pattern_index=6 },
{ .goto_index=-1, .pattern_index=6 },
{ .goto_index=-1, .pattern_index=9 },
{ .goto_index=-1, .pattern_index=9 },
{ .goto_index=-1, .pattern_index=9 },
{ .goto_index=-1, .pattern_index=9 },
{ .goto_index=-1, .pattern_index=10 },
{ .goto_index=-1, .pattern_index=10 },
{ .goto_index=-1, .pattern_index=10 },
{ .goto_index=-1, .pattern_index=10 },
{ .goto_index=-1, .pattern_index=11 },
{ .goto_index=-1, .pattern_index=18 },
{ .goto_index=-1, .pattern_index=18 },
{ .goto_index=-1, .pattern_index=18 },
{ .goto_index=-1, .pattern_index=18 },
{ .goto_index=-1, .pattern_index=18 },
{ .goto_index=-1, .pattern_index=18 },
{ .goto_index=-1, .pattern_index=18 },
{ .goto_index=-1, .pattern_index=18 },
{ .goto_index=-1, .pattern_index=18 },
{ .goto_index=-1, .pattern_index=18 },
{ .goto_index=-1, .pattern_index=18 },
{ .goto_index=-1, .pattern_index=18 },
{ .goto_index=-1, .pattern_index=18 },
{ .goto_index=-1, .pattern_index=18 },
{ .goto_index=-1, .pattern_index=18 },
{ .goto_index=-1, .pattern_index=4 },
{ .goto_index=-1, .pattern_index=6 },
{ .goto_index=-1, .pattern_index=6 },
{ .goto_index=-1, .pattern_index=6 },
{ .goto_index=-1, .pattern_index=6 },
{ .goto_index=-1, .pattern_index=9 },
{ .goto_index=-1, .pattern_index=9 },
{ .goto_index=-1, .pattern_index=9 },
{ .goto_index=-1, .pattern_index=9 },
{ .goto_index=-1, .pattern_index=10 },
{ .goto_index=-1, .pattern_index=10 },
{ .goto_index=-1, .pattern_index=10 },
{ .goto_index=-1, .pattern_index=10 },
{ .goto_index=-1, .pattern_index=11 },
{ .goto_index=-1, .pattern_index=1 },
{ .goto_index=-1, .pattern_index=1 },
{ .goto_index=-1, .pattern_index=13 },
{ .goto_index=-1, .pattern_index=10 },
{ .goto_index=-1, .pattern_index=10 },
{ .goto_index=-1, .pattern_index=15 },
{ .goto_index=-1, .pattern_index=15 },
{ .goto_index=-1, .pattern_index=9 },
{ .goto_index=-1, .pattern_index=9 },
{ .goto_index=-1, .pattern_index=1 },
{ .goto_index=-1, .pattern_index=1 },
{ .goto_index=0, .pattern_index=16 }}}, {(sequence_t[]){{ .goto_index=-1, .pattern_index=0 },
{ .goto_index=-1, .pattern_index=7 },
{ .goto_index=-1, .pattern_index=0 },
{ .goto_index=-1, .pattern_index=2 },
{ .goto_index=-1, .pattern_index=0 },
{ .goto_index=-1, .pattern_index=3 },
{ .goto_index=-1, .pattern_index=0 },
{ .goto_index=-1, .pattern_index=5 },
{ .goto_index=-1, .pattern_index=8 },
{ .goto_index=-1, .pattern_index=0 },
{ .goto_index=-1, .pattern_index=7 },
{ .goto_index=-1, .pattern_index=0 },
{ .goto_index=-1, .pattern_index=2 },
{ .goto_index=-1, .pattern_index=0 },
{ .goto_index=-1, .pattern_index=3 },
{ .goto_index=-1, .pattern_index=0 },
{ .goto_index=-1, .pattern_index=5 },
{ .goto_index=-1, .pattern_index=8 },
{ .goto_index=-1, .pattern_index=14 },
{ .goto_index=0, .pattern_index=17 }}} },
	.instruments = (instrument_t[]){   {
   // Quick Note
   .frequencies = (int8_t[]) { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
   .volumes = (uint8_t[]) { 0, 2, 4, 5, 5, 4, 3, 2, 1, 0, 0 },
   .sustainStart = 9,
   .releaseStart = 10,
   .waveform = 4,
   .length = 11
},
   {
   // Quick Note
   .frequencies = (int8_t[]) { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
   .volumes = (uint8_t[]) { 0, 2, 4, 5, 5, 4, 3, 2, 1, 0, 0 },
   .sustainStart = 9,
   .releaseStart = 10,
   .waveform = 12,
   .length = 11
},
   {
   // long note
   .frequencies = (int8_t[]) { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
   .volumes = (uint8_t[]) { 0, 1, 2, 3, 3, 3, 3, 3, 3, 2, 1, 0, 0, 0 },
   .sustainStart = 12,
   .releaseStart = 13,
   .waveform = 4,
   .length = 14
},
   {
   // long note
   .frequencies = (int8_t[]) { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
   .volumes = (uint8_t[]) { 0, 1, 2, 3, 3, 3, 3, 3, 3, 2, 1, 0, 0, 0 },
   .sustainStart = 12,
   .releaseStart = 13,
   .waveform = 12,
   .length = 14
},
   {
   // Medium Note
   .frequencies = (int8_t[]) { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
   .volumes = (uint8_t[]) { 0, 2, 4, 5, 5, 5, 5, 5, 5, 4, 4, 3, 3, 3, 2, 2, 1, 0, 0 },
   .sustainStart = 16,
   .releaseStart = 17,
   .waveform = 4,
   .length = 19
},
   {
   // Medium Note
   .frequencies = (int8_t[]) { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
   .volumes = (uint8_t[]) { 0, 2, 4, 5, 5, 5, 5, 5, 5, 4, 4, 3, 3, 3, 2, 2, 1, 0, 0 },
   .sustainStart = 16,
   .releaseStart = 17,
   .waveform = 12,
   .length = 19
},
   {
   // Deep bass
   .frequencies = (int8_t[]) { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
   .volumes = (uint8_t[]) { 0, 1, 2, 2, 3, 1, 1, 1, 1, 0, 0 },
   .sustainStart = 9,
   .releaseStart = 10,
   .waveform = 7,
   .length = 11
},
   {
   // 
   .frequencies = (int8_t[]) { 0, 0 },
   .volumes = (uint8_t[]) { 0, 0 },
   .sustainStart = 0,
   .releaseStart = 1,
   .waveform = 4,
   .length = 2
},
   {
   // 
   .frequencies = (int8_t[]) { 0, 0 },
   .volumes = (uint8_t[]) { 0, 0 },
   .sustainStart = 0,
   .releaseStart = 1,
   .waveform = 12,
   .length = 2
},
   {
   // 
   .frequencies = (int8_t[]) { 0, 0 },
   .volumes = (uint8_t[]) { 0, 0 },
   .sustainStart = 0,
   .releaseStart = 1,
   .waveform = 4,
   .length = 2
},
   {
   // 
   .frequencies = (int8_t[]) { 0, 0 },
   .volumes = (uint8_t[]) { 0, 0 },
   .sustainStart = 0,
   .releaseStart = 1,
   .waveform = 12,
   .length = 2
},
   {
   // 
   .frequencies = (int8_t[]) { 0, 0 },
   .volumes = (uint8_t[]) { 0, 0 },
   .sustainStart = 0,
   .releaseStart = 1,
   .waveform = 4,
   .length = 2
},
   {
   // 
   .frequencies = (int8_t[]) { 0, 0 },
   .volumes = (uint8_t[]) { 0, 0 },
   .sustainStart = 0,
   .releaseStart = 1,
   .waveform = 12,
   .length = 2
}},
	.percussions = (percussion_t[]){},
	.patterns = (pattern_t[]){   {
   // Melody Motif
   .even_speed = 6,
   .odd_speed = 6,
   .notes = (uint8_t[]) { 0x33, 0x08, 0x08, 0x10, 0x32, 0x10, 0x31, 0x08,
0x08, 0x08, 0x32, 0x08, 0x08, 0x00 }
},
   {
   // bass 1
   .even_speed = 6,
   .odd_speed = 6,
   .notes = (uint8_t[]) { 0xee, 0x10, 0xeb, 0x10, 0xf4, 0x10, 0xeb, 0x10,
0x00 }
},
   {
   // Melody 2
   .even_speed = 6,
   .odd_speed = 6,
   .notes = (uint8_t[]) { 0x08, 0x33, 0x10, 0x2b, 0x08, 0x08, 0x08, 0x2f,
0x08, 0xae, 0x08, 0x08, 0x10, 0x33, 0x08, 0x37,
0x10, 0x3a, 0x08, 0x00 }
},
   {
   // melody3
   .even_speed = 6,
   .odd_speed = 6,
   .notes = (uint8_t[]) { 0x08, 0x37, 0x08, 0x34, 0x08, 0x33, 0x08, 0x38,
0x08, 0xb7, 0x08, 0x10, 0x08, 0x4f, 0x10, 0x4c,
0x08, 0x08, 0x08, 0x00 }
},
   {
   // bass 1 end
   .even_speed = 6,
   .odd_speed = 6,
   .notes = (uint8_t[]) { 0xee, 0x10, 0xee, 0x10, 0xed, 0x08, 0xeb, 0x10,
0x00 }
},
   {
   // melody 4
   .even_speed = 6,
   .odd_speed = 6,
   .notes = (uint8_t[]) { 0x08, 0x33, 0x08, 0x35, 0x10, 0x37, 0x08, 0x3a,
0x10, 0xbd, 0x08, 0x08, 0x10, 0x08, 0x08, 0x08,
0x08, 0x08, 0x08, 0x08, 0x08, 0x00 }
},
   {
   // bass 2
   .even_speed = 6,
   .odd_speed = 6,
   .notes = (uint8_t[]) { 0xf6, 0x10, 0xe8, 0x10, 0xee, 0x10, 0xe8, 0x10,
0x00 }
},
   {
   // Melody 1
   .even_speed = 6,
   .odd_speed = 6,
   .notes = (uint8_t[]) { 0x10, 0x34, 0x10, 0x33, 0x08, 0x08, 0x08, 0x38,
0x08, 0xb7, 0x08, 0x08, 0x10, 0x4f, 0x10, 0x4c,
0x08, 0x08, 0x08, 0x00 }
},
   {
   // melody B1
   .even_speed = 6,
   .odd_speed = 6,
   .notes = (uint8_t[]) { 0x08, 0x08, 0x31, 0x08, 0x10, 0x08, 0x31, 0x08,
0x10, 0x08, 0x08, 0x08, 0x32, 0x10, 0x31, 0x08,
0x32, 0x08, 0x31, 0x08, 0xae, 0x08, 0x2e, 0x10,
0x2f, 0x10, 0x31, 0x10, 0x33, 0x08, 0x08, 0x08,
0x08, 0x08, 0x33, 0x08, 0x08, 0x08, 0x33, 0x08,
0x08, 0x08, 0x08, 0x08, 0x34, 0x08, 0x33, 0x08,
0x34, 0x08, 0x33, 0x08, 0xae, 0x08, 0x2e, 0x08,
0x2f, 0x08, 0x31, 0x08, 0x33, 0x08, 0x08, 0x08,
0x08, 0x08, 0x31, 0x08, 0x08, 0x08, 0x31, 0x08,
0x08, 0x08, 0x08, 0x08, 0x32, 0x08, 0x31, 0x08,
0x32, 0x08, 0x31, 0x08, 0xac, 0x08, 0x2c, 0x08,
0x2e, 0x08, 0x2f, 0x08, 0x31, 0x08, 0x54, 0x08,
0x53, 0x08, 0x52, 0x08, 0x51, 0x08, 0x4f, 0x08,
0x4e, 0x08, 0x4c, 0x08, 0x3f, 0x08, 0x3d, 0x08,
0x3f, 0x08, 0x4b, 0x08, 0x4c, 0x08, 0x4e, 0x08,
0x4f, 0x08, 0x51, 0x08, 0x53, 0x08, 0x00 }
},
   {
   // bass 3
   .even_speed = 6,
   .odd_speed = 6,
   .notes = (uint8_t[]) { 0xeb, 0x10, 0xe9, 0x10, 0xee, 0x10, 0xe9, 0x10,
0x00 }
},
   {
   // bass 4
   .even_speed = 6,
   .odd_speed = 6,
   .notes = (uint8_t[]) { 0xed, 0x10, 0xea, 0x10, 0xf1, 0x10, 0xea, 0x10,
0x00 }
},
   {
   // Harmony L
   .even_speed = 6,
   .odd_speed = 6,
   .notes = (uint8_t[]) { 0x5a, 0x08, 0x57, 0x08, 0x55, 0x08, 0x54, 0x08,
0x53, 0x08, 0x51, 0x08, 0x4f, 0x08, 0x4e, 0x08,
0x4f, 0x08, 0x51, 0x08, 0x53, 0x08, 0x54, 0x08,
0x57, 0x08, 0x5a, 0x08, 0x5d, 0x08, 0x5f, 0x08,
0x00 }
},
   {
   // 1
   .even_speed = 6,
   .odd_speed = 6,
   .notes = (uint8_t[]) { 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
0x00 }
},
   {
   // bass 5
   .even_speed = 6,
   .odd_speed = 6,
   .notes = (uint8_t[]) { 0xfc, 0x10, 0xec, 0x10, 0xf2, 0x10, 0xec, 0x10,
0xfc, 0x10, 0xec, 0x10, 0xf2, 0x10, 0xec, 0x10,
0x00 }
},
   {
   // TA melody 1
   .even_speed = 6,
   .odd_speed = 6,
   .notes = (uint8_t[]) { 0xb3, 0x08, 0x08, 0x10, 0x08, 0x08, 0x34, 0x08,
0x35, 0x08, 0x37, 0x08, 0x38, 0x08, 0x3a, 0x08,
0xb2, 0x08, 0x08, 0x08, 0x10, 0x08, 0x33, 0x08,
0x34, 0x08, 0x35, 0x08, 0x37, 0x08, 0x38, 0x08,
0xb1, 0x08, 0x08, 0x08, 0x10, 0x08, 0x32, 0x08,
0x33, 0x08, 0x34, 0x08, 0x35, 0x08, 0x37, 0x08,
0xb0, 0x08, 0x08, 0x08, 0x33, 0x08, 0x08, 0x08,
0x38, 0x08, 0x08, 0x08, 0x33, 0x08, 0x08, 0x08,
0xb0, 0x08, 0x08, 0x08, 0x10, 0x08, 0x31, 0x08,
0x32, 0x08, 0x33, 0x08, 0x34, 0x08, 0x35, 0x08,
0xaf, 0x08, 0x08, 0x08, 0x10, 0x08, 0x30, 0x08,
0x31, 0x08, 0x32, 0x08, 0x33, 0x08, 0x34, 0x08,
0xae, 0x08, 0x08, 0x08, 0x10, 0x08, 0x2f, 0x08,
0x30, 0x08, 0x31, 0x08, 0x32, 0x08, 0x33, 0x08,
0xad, 0x08, 0x08, 0x08, 0x08, 0x08, 0x4a, 0x08,
0x3b, 0x00 }
},
   {
   // bass 6
   .even_speed = 6,
   .odd_speed = 6,
   .notes = (uint8_t[]) { 0xec, 0x10, 0xe9, 0x10, 0xf0, 0x10, 0xe9, 0x10,
0xec, 0x10, 0xe9, 0x10, 0xf0, 0x10, 0xec, 0x10,
0x00 }
},
   {
   // Harmony L2
   .even_speed = 6,
   .odd_speed = 6,
   .notes = (uint8_t[]) { 0x4a, 0x08, 0x08, 0x08, 0x08, 0x08, 0x4d, 0x08,
0x4a, 0x08, 0x08, 0x08, 0x08, 0x08, 0x4d, 0x08,
0x4a, 0x08, 0x08, 0x08, 0x08, 0x08, 0x4d, 0x08,
0x4a, 0x08, 0x08, 0x08, 0x08, 0x08, 0x4d, 0x08,
0x4a, 0x08, 0x4d, 0x08, 0x4a, 0x08, 0x4d, 0x08,
0x4a, 0x08, 0x4d, 0x08, 0x4a, 0x08, 0x4d, 0x08,
0x4a, 0x08, 0x4a, 0x08, 0x4a, 0x08, 0x4a, 0x08,
0x4a, 0x08, 0x4a, 0x08, 0x4a, 0x08, 0x8a, 0x08,
0x00 }
},
   {
   // TA Melody 2
   .even_speed = 6,
   .odd_speed = 6,
   .notes = (uint8_t[]) { 0x08, 0x08, 0x08, 0x08, 0x08, 0x4a, 0x08, 0x3b,
0x08, 0x08, 0x08, 0x08, 0x08, 0x4a, 0x08, 0x3b,
0x08, 0x08, 0x08, 0x08, 0x08, 0x4a, 0x08, 0x3b,
0x08, 0x4a, 0x08, 0x3b, 0x08, 0x4a, 0x08, 0x3b,
0x08, 0x4a, 0x08, 0x3b, 0x08, 0x4a, 0x08, 0x3b,
0x08, 0x3b, 0x08, 0x3a, 0x08, 0x3a, 0x08, 0x38,
0x08, 0x38, 0x08, 0x35, 0x08, 0x75, 0x08, 0x00 }
},
   {
   // bass1a
   .even_speed = 6,
   .odd_speed = 6,
   .notes = (uint8_t[]) { 0xfe, 0x10, 0xee, 0x10, 0xf4, 0x10, 0xe9, 0x10,
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
