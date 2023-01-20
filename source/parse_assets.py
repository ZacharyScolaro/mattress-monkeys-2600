import math
import png

y = 0;

def parse_png(png_name, pixel_width, pixel_height, item_x, item_y, item_width, item_height):
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

def parse_sprite_strip(f_header, f_source, png_name, item_name, item_width, item_height, item_count, pixel_width, pixel_height, item_x, item_y):
	item_size = math.ceil(item_width/8) * item_height # figure out how many bytes to hold it all
	first_dimension = '[' + str(item_count) + ']' if item_count > 1 else ''
	f_header.write('\r\nextern const uint8_t ' + item_name + 'Graphics' + first_dimension + '[' + str(item_size) + '];\r\n')
	f_source.write('\r\nconst uint8_t ' + item_name + 'Graphics' + first_dimension + '[' + str(item_size) + '] = { ')
	for x in range(0, item_count):
		graphic_bytes = parse_png(png_name, pixel_width, pixel_height, x * item_width + item_x, item_y, item_width, item_height)
		if item_count > 1:
			f_source.write('\r\n{ ')
		f_source.write(', '.join(graphic_bytes))
		if item_count > 1:
			f_source.write(' }' + ('' if x == item_count-1 else ',') +'\r\n')
	f_source.write(' };\r\n')

f_header = open('sprites.h', 'wt')
f_header.write('#include <stdint.h>\r\n')

f_source = open('sprites.c', 'wt')
f_source.write('#include "sprites.h"\r\n')

png_name = 'score-sprites.png'
item_name = 'ScoreSprites'
graphic_bytes = parse_png(png_name, 8, 4, 0, 0, 13*8, 14)
f_header.write('\r\nextern const uint8_t ' + item_name + 'Graphics[14*13];\r\n')
f_source.write('\r\nconst uint8_t ' + item_name + 'Graphics[14*13] = { ')
f_source.write(', '.join(graphic_bytes))
f_source.write(' };\r\n')

parse_sprite_strip(f_header, f_source, 'pf-fan-blade-animation.png', 'FanBlade', 10, 7, 7, 4, 1, 0, 0)

parse_sprite_strip(f_header, f_source, 'player-2-cycle-walk.png', 'MonkeyWalking', 8, 12, 2, 1, 1, 0, 0)
parse_sprite_strip(f_header, f_source, 'player-bed-idle.png', 'MonkeyIdle', 8, 12, 1, 1, 1, 0, 0)
parse_sprite_strip(f_header, f_source, 'fan-chasis.png', 'FanChasis', 8, 28, 1, 1, 1, 0, 0)
