import png

y = 0;

def parse_png(png_name, pixel_width, pixel_height, item_name, item_x, item_y, item_width, item_height):
	global y
	y = 0

	graphic_bytes = []

	f = open('../assets/' + png_name, 'rb')
	r = png.Reader(f)
	width, height, rows, info = r.read()
#	print(info)
	planes = info['planes']
#	print(width, height, pixel_width, planes)
	pixel_y = 0
	for row in rows:
		if y % pixel_height == 0:
			if pixel_y >= item_y:
				b = 0
				mask = 0x80
				for x in range(item_x*pixel_width*planes, (item_x + item_width)*pixel_width*planes, pixel_width*planes):
					if row[x] != 0:
						b |= mask
					mask = mask >> 1
					if mask == 0:
						graphic_bytes.append('0x{:02x}'.format(b))
						b = 0
						mask = 0x80
				if mask != 0x80:
					graphic_bytes.append('0x{:02x}'.format(b))
			pixel_y = pixel_y + 1
			if pixel_y > item_y + item_height:
				break
		y+=1
	f.close()
	return graphic_bytes


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

#parse_score_sprites()

#pf-fan-blade-animation.png


f_header = open('sprites.h', 'wt')
f_header.write('#include <stdint.h>\r\n')

f_source = open('sprites.c', 'wt')
f_source.write('#include "sprites.h"\r\n')

png_name = 'score-sprites.png'
item_name = 'ScoreSprites'
graphic_bytes = parse_png(png_name, 8, 4, item_name, 0, 0, 13*8, 14)
f_header.write('\r\nextern const uint8_t ' + item_name + 'Graphics[14*13];\r\n')
f_source.write('\r\nconst uint8_t ' + item_name + 'Graphics[14*13] = { ')
f_source.write(', '.join(graphic_bytes))
f_source.write(' };\r\n')

png_name = 'pf-fan-blade-animation.png'
item_name = 'FanBlade'
item_width = 10
f_header.write('\r\nextern const uint8_t ' + item_name + 'Graphics[7][14];\r\n')
f_source.write('\r\nconst uint8_t ' + item_name + 'Graphics[7][14] = { ')
for x in range(0, 7):
	graphic_bytes = parse_png(png_name, 4, 1, item_name, x * item_width, 0, item_width, 7)
	f_source.write('\r\n{ ')
	f_source.write(', '.join(graphic_bytes))
	f_source.write(' }' + ('' if x == 6 else ',') +'\r\n')
f_source.write(' };\r\n')
