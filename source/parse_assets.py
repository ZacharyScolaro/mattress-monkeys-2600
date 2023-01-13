import png

y = 0;

def parse_score_sprites():
	global y
	y = 0

	sprites = []

	f = open('../assets/score-sprites.png', 'rb')
	r = png.Reader(f)
	width, height, rows, info = r.read()
	print(info)
	planes = info['planes']
	pixel_width = width // (13*8)
	print(width, height, pixel_width, planes)
	for row in rows:
		if y % 4 == 0:
			for x in range(0, width*planes, pixel_width*8*planes):
				b = 0
				i = x
				mask = 0x40
				while(mask != 0):
					if row[i] != 0:
						b |= mask
					mask = mask >> 1
					i = i + (pixel_width * planes)
				sprites.append('0x{:02x}'.format(b))
		y+=1
	f.close()

	f_header = open('sprites.h', 'wt')
	f_header.write('#include <stdint.h>\r\n')
	f_header.write('extern const int8_t ScoreSpritesGraphics[14*13];\r\n')
	f_header.close()

	f_out = open('sprites.c', 'wt')
	f_out.write('#include "sprites.h"\r\n')
	f_out.write('const int8_t ScoreSpritesGraphics[14*13] = { ')

	f_out.write(', '.join(sprites))

	f_out.write(' };\r\n')

	f_out.close()

parse_score_sprites()