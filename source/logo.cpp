#include "logo.h"
#include "vcsLib.h"

static const uint8_t LogoSmallGraphics[504] = { 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x3f, 0xf8, 0x0f, 0x00, 0x00, 0x00, 0x3f, 0xfc, 0x0f, 0x00, 0x00, 0x00, 0x3f, 0xfc, 0x0f, 0x00, 0x00, 0x00, 0x3f, 0xfe, 0x0f, 0x00, 0x00, 0x00, 0x3f, 0xfe, 0x0f, 0x00, 0x00, 0x00, 0x3f, 0xfe, 0x0f, 0x00, 0x00, 0x00, 0x3f, 0xfc, 0x0f, 0x00, 0x00, 0x00, 0x3f, 0xfc, 0x0f, 0x00, 0x00, 0x00, 0x3f, 0xf8, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x20, 0x72, 0x00, 0x20, 0x01, 0x00, 0x00, 0x4a, 0x00, 0x70, 0x01, 0x00, 0x00, 0x4b, 0x1b, 0x24, 0xd1, 0x11, 0x26, 0x4a, 0xaa, 0xaa, 0xa9, 0x2a, 0xa8, 0x72, 0xaa, 0xaa, 0xa9, 0x2a, 0xa8, 0x42, 0xaa, 0xaa, 0xa9, 0x2a, 0xa8, 0x42, 0xaa, 0xaa, 0xa9, 0x2a, 0xa8, 0x42, 0x9a, 0xa4, 0xa9, 0xd1, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x02, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x3b, 0xba, 0x80, 0x00, 0x00, 0x04, 0x8a, 0x8a, 0x80, 0x00, 0x00, 0x05, 0xba, 0xbb, 0xc0, 0x00, 0x00, 0x05, 0xa2, 0xa3, 0xc0, 0x00, 0x00, 0x04, 0xbb, 0xb8, 0x80, 0x00, 0x00, 0x03, 0x3b, 0xb8, 0x80, 0x00 };

void ShowLogo()
{
	const int Cyan = 0x9A;
	const int Blue = 0x82;
	const int Magenta = 0x56;

	for(int frame = 0; frame < 120; frame++)
	{
		vcsEndOverblank();

		vcsWrite5(ENABL, 0);
		vcsWrite5(PF2, 0);
		vcsWrite5(COLUP0, Blue);
		vcsWrite5(COLUP1, Magenta);
		vcsWrite5(NUSIZ0, 3);
		vcsWrite5(NUSIZ1, 3);
		vcsWrite5(CTRLPF, 0x21);
		vcsWrite5(VDELP0, 1);
		vcsWrite5(VDELP1, 1);
		vcsWrite5(COLUBK, 0);
		vcsWrite5(COLUPF, Cyan);
		vcsSta3(HMCLR);
		vcsSta3(WSYNC);
		vcsNop2n(20);
		vcsSta4(RESBL);
		vcsSta3(WSYNC);
		vcsNop2n(19);
		vcsSta3(RESP0);
		vcsSta3(RESPONE);
		vcsWrite5(HMP0, 0x40);
		vcsWrite5(HMP1, 0x50);
		vcsWrite5(HMBL, 0x20);
		vcsSta3(WSYNC);
		vcsSta3(HMOVE);
		vcsWrite5(VBLANK, 0);
		vcsJmp3();
		vcsNop2n(31);
		vcsSta3(HMCLR);
		vcsSta3(WSYNC);

		int line = 0;
		for (int i = 0; i < 54; i++)
		{
			vcsSta3(WSYNC);
			line++;
		}

		// Top section
		const uint8_t LogoTopHmbl[84] =
			{
				0x10, 0x10, 0x00, 0, 0, 0, 0, 0xf0,
				0x10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0xf0, 0, 0xf0, 0, 0xf0, 0, 0xf0, 0, 0xf0, 0, 0xf0, 0, 0xf0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

		int gi = 0;
		for (int i = 0; i < 84; i++)
		{
			vcsSta3(HMOVE);
			vcsJmp3();
			vcsWrite5(PF2, i < 8 || i > 50 ? 0xe0 : 0x10);
			if (i == 50)
			{
				vcsWrite5(COLUPF, Blue);
			}
			else if(i == 58)
			{
				vcsWrite5(COLUPF, 0);
			}
			else
			{
				vcsWrite5(ENABL, 2);
			}
			vcsWrite5(GRP0, LogoSmallGraphics[gi++]);
			vcsWrite5(GRP1, LogoSmallGraphics[gi++]);
			vcsWrite5(GRP0, LogoSmallGraphics[gi++]);
			vcsWrite5(COLUP0, i > 58 ? 0xf : i > 7 ? Magenta : Blue);
			vcsLda2(LogoSmallGraphics[gi++]);
			vcsLdx2(LogoSmallGraphics[gi++]);
			vcsLdy2(LogoSmallGraphics[gi++]);
			vcsSta3(GRP1);
			vcsStx3(GRP0);
			vcsSty3(GRP1);
			vcsSta3(GRP0);
			vcsWrite5(HMBL, LogoTopHmbl[i]);
			vcsWrite5(COLUP1, i > 58 ? 0xf : Magenta);
			vcsSta3(WSYNC);
			line++;
		}

		vcsWrite5(COLUPF, 0);
		vcsSta3(GRP0);
		vcsSta3(GRP1);
		vcsSta3(GRP0);
		vcsWrite5(COLUP0, 0x0f);
		vcsWrite5(COLUP1, 0x0f);
		for (int i = 0; i < 6; i++)
		{
			vcsSta3(WSYNC);
			line++;
		}

		for (int i = 0; line < 192; i++)
		{
			vcsWrite5(COLUPF, 0);
			vcsSta3(GRP0);
			vcsSta3(GRP1);
			vcsSta3(GRP0);
			vcsSta3(WSYNC);
			line++;
		}

		vcsSta3(WSYNC);
		vcsWrite5(VBLANK, 2);
		vcsStartOverblank();
	}
}

