#include "sprites.h"
#include "vcsLib.h"

#define GlyphHeight 16
#define MaxRows (192 / GlyphHeight)

static void kernelA(uint8_t textBuffer[18]);
static void kernelB(uint8_t textBuffer[18]);

static int frameCount = 0;

__attribute__((section(".noinit"))) static uint8_t textBuffer[18 * GlyphHeight * MaxRows];

static uint16_t font[128 * 3] =
	{
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		// *** BEGIN PRINTABLE CHARACTERS ***
		0, 0, 0,										// Space
		0b010010010010, 0b010010000000, 0b010010000000, // !
		0b101101101000, 0b000000000000, 0b000000000000, // "
		0b001001101111, 0b111101101111, 0b111101100100, // #
		0b010010111101, 0b100110011001, 0b101111010010, // $
		0b100101001011, 0b010010110100, 0b101001000000, // %
		0b010111101011, 0b110101101101, 0b111011001000, // &
		0b010010010010, 0b010000000000, 0b000000000000, // '
		0b001011010110, 0b100100100100, 0b110010011001, // (
		0b100110010011, 0b001001001001, 0b011010110100, // )
		0b000000101101, 0b010111111010, 0b101101000000, // *
		0b000000010010, 0b010111111010, 0b010010000000, // +
		0b000000000000, 0b000000000010, 0b010010100100, // ,
		0b000000000000, 0b000111111000, 0b000000000000, // -
		0b000000000000, 0b000000000010, 0b010010000000, // .
		0b001001001001, 0b010010010010, 0b100100100100, // /
		0b010111101101, 0b101101101101, 0b111110000000, // 0
		0b010110110010, 0b010010010010, 0b010010000000, // 1
		0b110111001001, 0b001011110100, 0b111111000000, // 2
		0b110111001001, 0b010011001001, 0b111110000000, // 3
		0b001001101101, 0b101111111001, 0b001001000000, // 4
		0b111111100110, 0b111001001001, 0b111110000000, // 5
		0b011111100110, 0b111101101101, 0b111010000000, // 6
		0b111111001001, 0b001010010010, 0b010010000000, // 7
		0b010111101101, 0b110011101101, 0b111110000000, // 8
		0b011111101101, 0b101111011001, 0b001001000000, // 9
		0b000000000010, 0b010010000010, 0b010010000000, // :
		0b000000000010, 0b010010000010, 0b010010100100, // ;
		0b000001001010, 0b010100100010, 0b010001001000, // <
		0b000000000111, 0b111000000111, 0b111000000000, // =
		0b000100100010, 0b010001001010, 0b010100100000, // >
		0b110111001001, 0b011010010000, 0b010010000000, // ?
		0b010010101101, 0b000010010000, 0b101101010010, // @
		0b011111101101, 0b101111111101, 0b101101000000, // A
		0b110111101101, 0b110111101101, 0b111110000000, // B
		0b011111100100, 0b100100100100, 0b111011000000, // C
		0b110111101101, 0b101101101101, 0b111110000000, // D
		0b111111100100, 0b110110100100, 0b111111000000, // E
		0b111111100100, 0b110110100100, 0b100100000000, // F
		0b011111100100, 0b100101101101, 0b111011000000, // G
		0b101101101101, 0b111111101101, 0b101101000000, // H
		0b111111010010, 0b010010010010, 0b111111000000, // I
		0b001001001001, 0b001001001001, 0b111110000000, // J
		0b101101101111, 0b110110101101, 0b101101000000, // K
		0b100100100100, 0b100100100100, 0b111111000000, // L
		0b101101111111, 0b111101101101, 0b101101000000, // M
		0b001001101101, 0b111111111101, 0b101100000000, // N
		0b010111101101, 0b101101101101, 0b111010000000, // O
		0b110111101101, 0b101111110100, 0b100100000000, // P
		0b010111101101, 0b101101101101, 0b110011001000, // Q
		0b110111101101, 0b101110111101, 0b101101000000, // R
		0b011111100100, 0b110011001001, 0b111110000000, // S
		0b111111010010, 0b010010010010, 0b010010000000, // T
		0b101101101101, 0b101101101101, 0b111010000000, // U
		0b101101101101, 0b101101111111, 0b010010000000, // V
		0b101101101101, 0b101111111111, 0b101101000000, // W
		0b101101101111, 0b010010111101, 0b101101000000, // X
		0b101101101101, 0b111111010010, 0b010010000000, // Y
		0b111111001001, 0b011010110100, 0b111111000000, // Z
		0b011011010010, 0b010010010010, 0b010010011011, // [
		0b100100100100, 0b010010010010, 0b001001001001, // \ (BackSlash)
		0b110110010010, 0b010010010010, 0b010010110110, // ]
		0b010010111101, 0b101000000000, 0b000000000000, // ^
		0b000000000000, 0b000000000000, 0b000000111111, // _
		0b100100110010, 0b010000000000, 0b000000000000, // `
		0b000000110111, 0b001011111101, 0b111011000000, // a
		0b100100110111, 0b101101101101, 0b111110000000, // b
		0b000000011111, 0b100100100100, 0b111011000000, // c
		0b001001011111, 0b101101101101, 0b111011000000, // d
		0b000000010111, 0b101111110100, 0b111011000000, // e
		0b001011010010, 0b111111010010, 0b010010000000, // f
		0b000000011111, 0b101101101111, 0b011001111110, // g
		0b100100110111, 0b101101101101, 0b101101000000, // h
		0b010010000010, 0b010010010010, 0b010010000000, // i
		0b010010000010, 0b010010010010, 0b010010110100, // j
		0b100100101101, 0b111110110101, 0b101101000000, // k
		0b110110010010, 0b010010010010, 0b010010000000, // l
		0b000000101111, 0b111111101101, 0b101101000000, // m
		0b000000110111, 0b101101101101, 0b101101000000, // n
		0b000000010111, 0b101101101101, 0b111010000000, // o
		0b000000110111, 0b101101101101, 0b111110100100, // p
		0b000000011111, 0b101101101101, 0b111011001001, // q
		0b000000101111, 0b110100100100, 0b100100000000, // r
		0b000000011111, 0b100110011001, 0b111110000000, // s
		0b010010111111, 0b010010010010, 0b011001000000, // t
		0b000000101101, 0b101101101101, 0b111011000000, // u
		0b000000101101, 0b101101101111, 0b010010000000, // v
		0b000000101101, 0b101101111111, 0b111101000000, // w
		0b000000101101, 0b111010010111, 0b101101000000, // x
		0b000000101101, 0b101101101111, 0b011001111110, // y
		0b000000111111, 0b001010010100, 0b111111000000, // z
		0b001011010010, 0b010100100010, 0b010010011001, // {
		0b010010010010, 0b010010010010, 0b010010010010, // |
		0b100110010010, 0b010001001010, 0b010010110100, // }
		0b000000000000, 0b001111111100, 0b000000000000, // ~
		// *** END PRINTABLE CHARACTERS ***
		0, 0, 0, // Delete
};

void InvertCharacter(int row, int col)
{
	int index = row * 18 * GlyphHeight + col;
	for (int y = 0; y < GlyphHeight; y++)
	{
		textBuffer[index] = ~textBuffer[index] & 0x7f;
		index += 18;
	}
}


void Print48Small(uint8_t* pBuffer, const char *ptext, int row)
{
	int index = row * 6 * GlyphHeight;
	for (int offset = 0; offset < 3; offset++)
	{
		for (int y = 3; y >= 0; y--)
		{
			for (int x = 0; x < 12;)
			{
				uint8_t b = ((font[(int)ptext[x++] * 3 + offset] >> (y * 3)) & 7) << 4;
				b |= (font[(int)ptext[x++] * 3 + offset] >> (y * 3)) & 7;
				pBuffer[index++] = b;
			}
		}
	}
}


void PrintSmall(const char *ptext, int row, int col, int len)
{
	int index;
	int inc;
	index = row * 18 * GlyphHeight + col / 2;
	inc = 18 - len / 2;
	for (int offset = 0; offset < 3; offset++)
	{
		for (int y = 3; y >= 0; y--)
		{
			for (int x = 0; x < len;)
			{
				uint8_t b = ((font[(int)ptext[x++] * 3 + offset] >> (y * 3)) & 7) << 4;
				b |= (font[(int)ptext[x++] * 3 + offset] >> (y * 3)) & 7;
				textBuffer[index++] = b;
			}
			index += inc;
		}
	}
}

void PrintText(const char *ptext, const int row)
{
	int index = row * 18 * GlyphHeight;
	for (int y = 0; y < GlyphHeight; y++)
	{
		for (int x = 0; x < 18; x++)
		{
			textBuffer[index++] = ScoreSpritesGraphics[(y / 2) * (sizeof(ScoreSpritesGraphics) / (GlyphHeight / 2)) + ptext[x]];
		}
	}
}

void DisplayText(uint8_t colu_background, int row_count)
{
	frameCount++;
	int frameToggle = frameCount & 1;

	vcsSta3(HMOVE); //	sta HMOVE
	vcsLdx2(0);		//	lda #$0
	vcsStx3(ENAM0);
	vcsStx3(ENAM1);
	vcsStx3(ENABL);
	vcsStx3(GRP0);
	vcsStx3(GRP1);
	vcsLda2(colu_background);
	vcsSta3(COLUBK);
	vcsSta3(COLUPF);
	vcsJmp3();
	if (frameToggle)
	{
		vcsJmp3();
		vcsWrite5(HMP1, 0xe0);
	}
	else
	{
		vcsLda2(0xf0);
		vcsSta4(HMP1);
	}
	vcsSta4(RESPONE); //	sta RESP1
	vcsLda2(0x0e);
	vcsSta3(COLUP0);
	vcsSta3(COLUP1);
	vcsLda2(3);
	vcsSta3(NUSIZ0);
	vcsSta3(NUSIZ1);
	vcsStx3(VDELP0);
	vcsStx3(VDELP1);
	vcsSta3(WSYNC); //	sta WSYNC

	vcsSta3(HMOVE); //	sta HMOVE
	vcsJmp3();
	vcsJmp3();
	vcsNop2n(20);
	vcsSta3(HMCLR); //	sta HMCLR
	vcsNop2n(9);
	// Need to position P0 just right in blank lines to avoid it showing up on the next line in the left margin
	if (frameToggle)
	{
		vcsJmp3();
		vcsSta3(RESP0);
		// 192 lines
		for (int i = 0;;)
		{
			for (int j = 0; j < GlyphHeight;)
			{
				kernelB(&textBuffer[i * 18 * GlyphHeight + j * 18]);
				j++;
				kernelA(&textBuffer[i * 18 * GlyphHeight + j * 18]);
				j++;
			}

			vcsSta3(HMOVE);
			vcsWrite5(GRP1, 0);
			vcsWrite5(GRP0, 0);
			vcsNop2n(15);
			vcsWrite5(HMP1, 0x70);
			vcsSta3(RESP0);
			vcsJmp3();
			vcsSta3(RESP0);
			if (i+1 == row_count)
			{
				vcsSta3(WSYNC);
				break;
			}
			vcsNop2n(5);
			vcsJmp3();
			vcsSta3(RESP0); // Simulates Kernel B
			vcsJmp3();
			i++;


			for (int j = 0; j < GlyphHeight;)
			{
				kernelA(&textBuffer[i * 18 * GlyphHeight + j * 18]);
				j++;
				kernelB(&textBuffer[i * 18 * GlyphHeight + j * 18]);
				j++;
			}

			vcsSta3(HMOVE);
			vcsWrite5(GRP0, 0);
			vcsWrite5(GRP1, 0);
			if (i+1 == row_count)
			{
				vcsSta3(WSYNC);
				break;
			}
			vcsNop2n(18);
			vcsSta3(RESP0);
			vcsJmp3();
			vcsSta3(RESP0);
			vcsNop2n(5);
			vcsWrite5(HMP1, 0x90);
			vcsSta3(RESP0); // Simulates Kernel A
			i++;
		}
	}
	else
	{
		vcsSta3(RESP0);
		vcsJmp3();
		// 192 lines
		for (int i = 0;;)
		{
			for (int j = 0; j < GlyphHeight;)
			{
				kernelA(&textBuffer[i * 18 * GlyphHeight + j * 18]);
				j++;
				kernelB(&textBuffer[i * 18 * GlyphHeight + j * 18]);
				j++;
			}

			vcsSta3(HMOVE);
			vcsWrite5(GRP0, 0);
			vcsWrite5(GRP1, 0);
			vcsNop2n(18);
			vcsSta3(RESP0);
			vcsJmp3();
			vcsSta3(RESP0);
			if (i+1 == row_count)
			{
				vcsSta3(WSYNC);
				break;
			}
			vcsNop2n(5);
			vcsWrite5(HMP1, 0x90);
			vcsSta3(RESP0); // Simulates Kernel A
			i++;


			for (int j = 0; j < GlyphHeight;)
			{
				kernelB(&textBuffer[i * 18 * GlyphHeight + j * 18]);
				j++;
				kernelA(&textBuffer[i * 18 * GlyphHeight + j * 18]);
				j++;
			}

			vcsSta3(HMOVE);
			vcsWrite5(GRP1, 0);
			vcsWrite5(GRP0, 0);
			vcsNop2n(15);
			vcsWrite5(HMP1, 0x70);
			vcsSta3(RESP0);
			vcsJmp3();
			vcsSta3(RESP0);
			if (i+1 == row_count)
			{
				vcsSta3(WSYNC);
				break;
			}
			vcsNop2n(5);
			vcsJmp3();
			vcsSta3(RESP0); // Simulates Kernel B
			vcsJmp3();

			i++;

		}
	}
}

// 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ
// 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7
static void kernelA(uint8_t textBuffer[18])
{
	vcsSta3(HMOVE);
	vcsWrite5(VBLANK, 0);
	vcsNop2();
	vcsLdy2(textBuffer[13] << 1);	// qqq_rrr_
	vcsWrite5(GRP0, textBuffer[0]); // _000_111
	vcsLda2(textBuffer[6] << 1);	// ccc_ddd_
	vcsSta3(GRP1);
	vcsSta3(RESP0);
	vcsWrite5(GRP0, textBuffer[2]); // _444_555
	vcsWrite5(GRP0, textBuffer[4]); // _888_999
	vcsWrite5(HMP1, 0x90);
	vcsLdx2(textBuffer[10] << 1);		 // kkk_lll_
	vcsWrite5(GRP1, textBuffer[8] << 1); // ggg_hhh_
	vcsStx4(GRP1);
	vcsSta3(RESP0);
	vcsSty3(GRP0);
	vcsSta3(RESP0);
	vcsWrite5(GRP0, textBuffer[15] << 1); // uuu_vvv_
	vcsWrite5(GRP0, textBuffer[17] << 1); // yyy_zzz_
	vcsJmp3();							  //	SLEEP 3
	vcsSta3(RESP0);						  //	sta RESP0
}

static void kernelB(uint8_t textBuffer[18])
{
	vcsSta3(HMOVE);
	vcsWrite5(VBLANK, 0);
	vcsWrite5(GRP1, textBuffer[7]); // _eee_fff
	vcsLdx2(textBuffer[11]);		// _mmm_nnn
	vcsWrite5(HMP1, 0x70);
	vcsWrite5(GRP0, textBuffer[1] << 1); // 222_333_
	vcsSta3(RESP0);
	vcsWrite5(GRP0, textBuffer[3] << 1); // 666_777_
	vcsWrite5(GRP0, textBuffer[5] << 1); // aaa_bbb_
	vcsWrite5(GRP0, textBuffer[12]);	 // _ooo_ppp
	vcsWrite5(GRP1, textBuffer[9]);		 // _iii_jjj
	vcsSta3(RESP0);
	vcsStx3(GRP1);
	vcsSta3(RESP0);
	vcsWrite5(GRP0, textBuffer[14]); // _sss_ttt
	vcsWrite5(GRP0, textBuffer[16]); // _www_xxx
	vcsJmp3();
	vcsSta3(RESP0);
	vcsJmp3();
}