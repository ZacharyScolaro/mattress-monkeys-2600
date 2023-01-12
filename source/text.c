#include "sprites.h"
#include "vcsLib.h"

#define GlyphHeight 14

static void kernelA(uint8_t textBuffer[18]);
static void kernelB(uint8_t textBuffer[18]);

static int frameCount = 0;

__attribute__((section(".noinit")))
static uint8_t textBuffer[18 * GlyphHeight];

void PrintScore(const int8_t* ptext)
{
	int index = 0;
	for (int y = 0; y < GlyphHeight; y++)
	{
		for (int x = 0; x < 18; x++)
		{
			textBuffer[index++] = ScoreSpritesGraphics[y * 13 + ptext[x]];
		}
	}
}

void DisplayText()
{
	int RowCount = 1;
	frameCount++;
	int frameToggle = frameCount & 1;

	vcsLda2(0);//	lda #$0
	vcsSta3(PF0);//	sta PF0
	vcsSta3(PF1);//	sta PF1
	vcsSta3(PF2);//	sta PF2
	vcsSta3(ENAM0);
	vcsSta3(ENAM1);
	vcsSta3(ENABL);
	vcsSta3(VDELP0);
	vcsSta3(VDELP1);
	vcsWrite5(COLUBK, 0x00);//	lda #$04//	sta COLUBK
	vcsWrite5(COLUP0, 0x0e);//	lda #$88//	sta COLUP0
	vcsWrite5(COLUP1, 0x0e);//	sta COLUP1
	vcsWrite5(NUSIZ0, 3);
	vcsWrite5(NUSIZ1, 3);

	vcsSta3(WSYNC);//	sta WSYNC
	if (frameToggle)
	{
		vcsNop2n(17);
		vcsWrite5(HMP1, 0xe0);
	}
	else
	{
		vcsNop2n(16);
		vcsWrite5(HMP1, 0xf0);
	}
	vcsSta4(RESPONE);//	sta RESP1
	vcsSta3(WSYNC);//	sta WSYNC
	vcsSta3(HMOVE);//	sta HMOVE
	vcsSta3(WSYNC);//	sta WSYNC

	vcsSta3(HMCLR);//	sta HMCLR
	vcsJmp3();
	vcsNop2n(32);
	// Need to position P0 just right in blank lines to avoid it showing up on the next line in the left margin
	if (frameToggle)
	{
		vcsJmp3();
		vcsSta3(RESP0);
		// 192 lines
		for (int i = 0; ;)
		{
			for (int j = 0; j < GlyphHeight; )
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
			vcsNop2n(5);
			vcsJmp3();
			vcsSta3(RESP0); // Simulates Kernel B
			vcsJmp3();
			i++;
			if (i == RowCount) { break; }

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
			vcsNop2n(5);
			vcsWrite5(HMP1, 0x90);
			vcsSta3(RESP0); // Simulates Kernel A
			i++;
			if (i == RowCount) { break; }

		}
	}
	else
	{
		vcsSta3(RESP0);
		vcsJmp3();
		// 192 lines
		for (int i = 0; ;)
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
			vcsNop2n(5);
			vcsWrite5(HMP1, 0x90);
			vcsSta3(RESP0); // Simulates Kernel A
			i++;
			if (i == RowCount) { break; }

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
			vcsNop2n(5);
			vcsJmp3();
			vcsSta3(RESP0); // Simulates Kernel B
			vcsJmp3();

			i++;
			if (i == RowCount) { break; }
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
	vcsLdy2(textBuffer[13] << 1);				// qqq_rrr_
	vcsWrite5(GRP0, textBuffer[0]);			// _000_111
	vcsLda2(textBuffer[6] << 1);				// ccc_ddd_
	vcsSta3(GRP1);
	vcsSta3(RESP0);
	vcsWrite5(GRP0, textBuffer[2]);			// _444_555
	vcsWrite5(GRP0, textBuffer[4]);			// _888_999
	vcsWrite5(HMP1, 0x90);
	vcsLdx2(textBuffer[10] << 1);				// kkk_lll_
	vcsWrite5(GRP1, textBuffer[8] << 1);	// ggg_hhh_
	vcsStx4(GRP1);
	vcsSta3(RESP0);
	vcsSty3(GRP0);
	vcsSta3(RESP0);
	vcsWrite5(GRP0, textBuffer[15] << 1);	// uuu_vvv_
	vcsWrite5(GRP0, textBuffer[17] << 1);	// yyy_zzz_
	vcsJmp3();//	SLEEP 3
	vcsSta3(RESP0);//	sta RESP0 
}

static void kernelB(uint8_t textBuffer[18])
{
	vcsSta3(HMOVE);
	vcsWrite5(VBLANK, 0);
	vcsWrite5(GRP1, textBuffer[7]);			// _eee_fff
	vcsLdx2(textBuffer[11]);					// _mmm_nnn
	vcsWrite5(HMP1, 0x70);
	vcsWrite5(GRP0, textBuffer[1] << 1);	// 222_333_
	vcsSta3(RESP0);
	vcsWrite5(GRP0, textBuffer[3] << 1);	// 666_777_
	vcsWrite5(GRP0, textBuffer[5] << 1);	// aaa_bbb_
	vcsWrite5(GRP0, textBuffer[12]);			// _ooo_ppp
	vcsWrite5(GRP1, textBuffer[9]);			// _iii_jjj
	vcsSta3(RESP0);
	vcsStx3(GRP1);
	vcsSta3(RESP0);
	vcsWrite5(GRP0, textBuffer[14]);			// _sss_ttt
	vcsWrite5(GRP0, textBuffer[16]);			// _www_xxx
	vcsJmp3();
	vcsSta3(RESP0);
	vcsJmp3();
}