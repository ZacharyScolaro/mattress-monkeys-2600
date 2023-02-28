import math
import png

palette = []

y = 0;

def parse_palette(png_name):
	global palette;
	y = 0;
	f = open('../assets/' + png_name, 'rb')
	r = png.Reader(f)
	width, height, rows, info = r.read()
	pixel_width = width // 8
	pixel_height = height // 16
	planes = info['planes']
	pixel_y = 0
	palette = []
	for row in rows:
		if y % pixel_height == pixel_height // 2:
			for x in range(0, 8, 1):
				offset = ((x * pixel_width) + (pixel_width // 2)) * planes
				color = (row[offset], row[offset+1], row[offset+2])
				palette.append(color)
			pixel_y = pixel_y + 1
		y+=1
	f.close()

def rgb_to_colu(rgb):
	closest = 0
	min_dist = 256*256*256
	for i in range(0,128):
		dist = math.sqrt((rgb[0] - palette[i][0])**2 +(rgb[0] - palette[i][0])**2 + (rgb[0] - palette[i][0])**2)
		if dist < min_dist:
			min_dist = dist
			closest = i
	return closest * 2


def parse_png(png_name, pixel_width, pixel_height, item_x, item_y, item_width, item_height, alpha_color):
	global y
	y = 0

	graphic_bytes = []
	color_bytes = []

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
				colu = 0
				b = 0
				mask = 0x80
				for x in range(item_x*pixel_width*planes, (item_x + item_width)*pixel_width*planes, pixel_width*planes):
					color = (row[x], row[x+1], row[x+2])
					if color  != alpha_color:
						b |= mask
						colu = rgb_to_colu(color)
					mask = mask >> 1
					if mask == 0:
						graphic_bytes.append('0x{:02x}'.format(b))
						b = 0
						mask = 0x80
				if mask != 0x80:
					graphic_bytes.append('0x{:02x}'.format(b))
				color_bytes.append('0x{:02x}'.format(colu))
			pixel_y = pixel_y + 1
			if pixel_y > item_y + item_height:
				break
		y+=1
	f.close()
	return graphic_bytes, color_bytes

def parse_sprite_strip(f_header, f_source, png_name, item_name, item_width, item_height, item_count, pixel_width, pixel_height, item_x, item_y, alpha_color):
	color_bytes = None
	item_size = math.ceil(item_width/8) * item_height # figure out how many bytes to hold it all
	first_dimension = '[' + str(item_count) + ']' if item_count > 1 else ''
	f_header.write('\r\nextern const uint8_t ' + item_name + 'Graphics' + first_dimension + '[' + str(item_size) + '];\r\n')
	f_source.write('\r\nconst uint8_t ' + item_name + 'Graphics' + first_dimension + '[' + str(item_size) + '] = { ')
	for x in range(0, item_count):
		graphic_bytes, color_bytes = parse_png(png_name, pixel_width, pixel_height, x * item_width + item_x, item_y, item_width, item_height, alpha_color)
		if item_count > 1:
			f_source.write('\r\n{ ')
		f_source.write(', '.join(graphic_bytes))
		if item_count > 1:
			f_source.write(' }' + ('' if x == item_count-1 else ',') +'\r\n')
	f_source.write(' };\r\n')
	if color_bytes != None:
		f_header.write('\r\nextern const uint8_t ' + item_name + 'Colu[' + str(len(color_bytes)) + '];\r\n')
		f_source.write('\r\nconst uint8_t ' + item_name + 'Colu[' + str(len(color_bytes)) + '] = { ')
		f_source.write(', '.join(color_bytes))
		f_source.write(' };\r\n')

def generate_sine_tables(f_header, f_source):
	item_count = 32
	f_header.write('\r\nextern const uint8_t SineTables[' + str(item_count) + '][80];\r\n')
	f_source.write('\r\nconst uint8_t SineTables[' + str(item_count) + '][80] = { ')
	for x in range(0, item_count):
		heights = generate_sine_wave(math.sin((x * 2 * math.pi)/item_count) * 17.5)
		if item_count > 1:
			f_source.write('\r\n{ ')
		f_source.write(', '.join(heights))
		if item_count > 1:
			f_source.write(' }' + ('' if x == item_count-1 else ',') +'\r\n')
	f_source.write(' };\r\n')


def generate_sine_wave(height):
	heights = []
	for x in range(0,80):
		heights.append(str(int((math.sin((x * math.pi)/10.0) * height) + 17.5)))
	return heights

def bin_to_c_array(f_header, f_source, bin_path, array_name):
	line = []
	lines = []
	with open(bin_path, mode='rb') as f:
		data = f.read()
		for b in data:
			line.append('0x{:02x}'.format(b))
			if len(line) > 15:
				lines.append(', '.join(line))
				line = []
		if len(line) > 0:
			lines.append(', '.join(line))
			line = []

	f_header.write('\r\nextern const uint8_t ' + array_name +'['+ str(len(data)) +'];\r\n');
	
	f_source.write('\r\nconst uint8_t ' + array_name +'['+ str(len(data)) +'] = {\r\n');
	f_source.write(',\r\n'.join(lines))
	f_source.write('};');


parse_palette('palette.png')

f_header = open('sprites.h', 'wt')
f_header.write('#include <stdint.h>\r\n')

f_source = open('sprites.c', 'wt')
f_source.write('#include "sprites.h"\r\n')

png_name = 'score-sprites.png'
item_name = 'ScoreSprites'
graphic_bytes, color_bytes = parse_png(png_name, 8, 4, 0, 0, 13*8, 14, (0,0,0))
f_header.write('\r\nextern const uint8_t ' + item_name + 'Graphics[14*13];\r\n')
f_source.write('\r\nconst uint8_t ' + item_name + 'Graphics[14*13] = { ')
f_source.write(', '.join(graphic_bytes))
f_source.write(' };\r\n')

parse_sprite_strip(f_header, f_source, 'pf-fan-blade-animation.png', 'FanBlade', 10, 7, 7, 4, 1, 0, 0, (0,0,0))

parse_sprite_strip(f_header, f_source, 'player-2-cycle-walk.png', 'MonkeyWalking', 8, 12, 2, 1, 1, 0, 0, (0,0,0))
parse_sprite_strip(f_header, f_source, 'player-bed-idle.png', 'MonkeyIdle', 8, 12, 1, 1, 1, 0, 0, (0,0,0))
parse_sprite_strip(f_header, f_source, 'fan-chasis.png', 'FanChasis', 8, 28, 1, 1, 1, 0, 0, (195,195,195))
parse_sprite_strip(f_header, f_source, 'bonus-banana.png', 'BonusBanana', 8, 13, 1, 1, 1, 0, 0, (0,0,0))
parse_sprite_strip(f_header, f_source, 'headboard-king.png', 'HeadBoardWide', 40, 40, 1, 1, 1, 0, 0, (0,0,0))

generate_sine_tables(f_header, f_source)

bin_to_c_array(f_header, f_source, 'kernel_7800.bin', 'kernel_7800')