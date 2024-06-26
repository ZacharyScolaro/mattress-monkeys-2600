import json
import math
from typing import Sequence
import png

reverse_byte_lookup = []
for x in range(0, 256):
	reverse_byte_lookup.append( \
		((x >> 7) & 1) | \
		((x >> 5) & 2) | \
		((x >> 3) & 4) | \
		((x >> 1) & 8) | \
		((x << 1) & 16) | \
		((x << 3) & 32) | \
		((x << 5) & 64) | \
		((x << 7) & 128))

def reverse_byte(b):
	return reverse_byte_lookup[b & 0xff]

init_ttt_typedefs_called = False

y = 0;

def parse_palette(png_name):
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
	return palette

ntsc_palette = parse_palette('palette-ntsc.png')

pal_palette = parse_palette('palette-pal.png')

def rgb_to_ntsc_colu(rgb):
	closest = 0
	min_dist = 256*256*256
	for i in range(0,128):
		dist = math.sqrt((rgb[0] - ntsc_palette[i][0])**2 +(rgb[1] - ntsc_palette[i][1])**2 + (rgb[2] - ntsc_palette[i][2])**2)
		if dist < min_dist:
			min_dist = dist
			closest = i
	return closest * 2

def rgb_to_pal_colu(rgb):
	closest = 0
	min_dist = 256*256*256
	for i in range(0,128):
		dist = math.sqrt((rgb[0] - pal_palette[i][0])**2 +(rgb[1] - pal_palette[i][1])**2 + (rgb[2] - pal_palette[i][2])**2)
		if dist < min_dist:
			min_dist = dist
			closest = i
	return closest * 2


def parse_png(png_name, pixel_width, pixel_height, item_x, item_y, item_width, item_height, alpha_color, stringify = True):
	global y
	y = 0

	graphic_bytes = []
	ntsc_color_bytes = []
	pal_color_bytes = []

	f = open('../assets/' + png_name, 'rb')
	r = png.Reader(f)
	width, height, rows, info = r.read()
#	print(info)
	planes = info['planes']
#	print(png_name, width, height, pixel_width, pixel_height, planes)
	pixel_y = 0
	for row in rows:
#		print("row", y)
		if y % pixel_height == 0:
			if pixel_y >= item_y:
				ntsc_colu = 0
				pal_colu = 0
				b = 0
				mask = 0x80
				for x in range(item_x*pixel_width*planes, (item_x + item_width)*pixel_width*planes, pixel_width*planes):
					color = (row[x], row[x+1], row[x+2])
					if (alpha_color == None and row[x+3] > 0) or (alpha_color != None and color  != alpha_color):
						b |= mask
						ntsc_colu = rgb_to_ntsc_colu(color)
						pal_colu = rgb_to_pal_colu(color)
					mask = mask >> 1
					if mask == 0:
						graphic_bytes.append('0x{:02x}'.format(b) if stringify else b)
						b = 0
						mask = 0x80
				if mask != 0x80:
					graphic_bytes.append('0x{:02x}'.format(b) if stringify else b)
				ntsc_color_bytes.append('0x{:02x}'.format(ntsc_colu) if stringify else b)
				pal_color_bytes.append('0x{:02x}'.format(pal_colu) if stringify else b)
			pixel_y = pixel_y + 1
			if pixel_y >= item_y + item_height:
				break
		y+=1
	f.close()
	return graphic_bytes, ntsc_color_bytes, pal_color_bytes

def parse_sprite_strip(f_header, f_source, png_name, item_name, item_width, item_height, item_count, pixel_width, pixel_height, item_x, item_y, alpha_color, padding_x = 0, save_colors = False):
	ntsc_colus = []
	pal_colus = []
	item_size = math.ceil(item_width/8) * item_height # figure out how many bytes to hold it all
	first_dimension = '[' + str(item_count) + ']' if item_count > 1 else ''
	f_header.write('\nextern const uint8_t ' + item_name + 'Graphics' + first_dimension + '[' + str(item_size) + '];\n')
	f_source.write('\nconst uint8_t ' + item_name + 'Graphics' + first_dimension + '[' + str(item_size) + '] = { ')
	for x in range(0, item_count):
		graphic_bytes, ntsc_colu_bytes, pal_colu_bytes = parse_png(png_name, pixel_width, pixel_height, x * (item_width + padding_x) + item_x, item_y, item_width, item_height, alpha_color)
		ntsc_colus.append(ntsc_colu_bytes)
		pal_colus.append(pal_colu_bytes)
		if item_count > 1:
			f_source.write('\n{ ')
		f_source.write(', '.join(graphic_bytes))
		if item_count > 1:
			f_source.write(' }' + ('' if x == item_count-1 else ',') +'\n')
	f_source.write(' };\n')
	if save_colors:
		#Colu NTSC
		f_header.write('\nextern const uint8_t ' + item_name + 'ColuNtsc' + first_dimension + '[' + str(item_size) + '];\n')
		f_source.write('\nconst uint8_t ' + item_name + 'ColuNtsc' + first_dimension + '[' + str(item_size) + '] = { ')
		for x in range(0, item_count):
			colu_bytes = ntsc_colus[x]
			if item_count > 1:
				f_source.write('\n{ ')
			f_source.write(', '.join(colu_bytes))
			if item_count > 1:
				f_source.write(' }' + ('' if x == item_count-1 else ',') +'\n')
		f_source.write(' };\n')
		#Colu PAL
		f_header.write('\nextern const uint8_t ' + item_name + 'ColuPal' + first_dimension + '[' + str(item_size) + '];\n')
		f_source.write('\nconst uint8_t ' + item_name + 'ColuPal' + first_dimension + '[' + str(item_size) + '] = { ')
		for x in range(0, item_count):
			colu_bytes = pal_colus[x]
			if item_count > 1:
				f_source.write('\n{ ')
			f_source.write(', '.join(colu_bytes))
			if item_count > 1:
				f_source.write(' }' + ('' if x == item_count-1 else ',') +'\n')
		f_source.write(' };\n')


def parse_playfield(f_header, f_source, png_name, item_name, item_height, pixel_width, pixel_height, item_x, item_y, alpha_color):
	pf_bytes = []
	item_width = 40;
	item_size = 6 * item_height # figure out how many bytes to hold it all
	f_header.write('\nextern const uint8_t ' + item_name + 'Playfield' + '[' + str(item_size) + '];\n')
	f_source.write('\nconst uint8_t ' + item_name + 'Playfield' + '[' + str(item_size) + '] = { ')
	graphic_bytes, _, _ = parse_png(png_name, pixel_width, pixel_height, item_x, item_y, item_width, item_height, alpha_color, False)
	for i in range(0, item_height):
		gi = i * 5
		pf_bytes.append('0x{:02x}'.format(reverse_byte(graphic_bytes[gi] >> 4)))
		pf_bytes.append('0x{:02x}'.format(0xff & ((graphic_bytes[gi] << 4) | (graphic_bytes[gi+1] >> 4))))
		pf_bytes.append('0x{:02x}'.format(reverse_byte((graphic_bytes[gi+1] << 4) | (graphic_bytes[gi+2] >> 4))))
		pf_bytes.append('0x{:02x}'.format(reverse_byte(graphic_bytes[gi+2])))
		pf_bytes.append('0x{:02x}'.format(graphic_bytes[gi+3]))
		pf_bytes.append('0x{:02x}'.format(reverse_byte(graphic_bytes[gi+4])))
	f_source.write(', '.join(pf_bytes))
	f_source.write(' };\n')



def generate_sine_tables(f_header, f_source):
	item_count = 32
	f_header.write('\nextern const uint8_t SineTables[' + str(item_count) + '][80];\n')
	f_source.write('\nconst uint8_t SineTables[' + str(item_count) + '][80] = { ')
	for x in range(0, item_count):
		max_height = 17.5
		#if x > 22:
		#	max_height *= .25
		#elif x > 11:
		#	max_height *= .5
		heights = generate_sine_wave(math.sin((x * 2 * math.pi)/item_count) * max_height)
		if item_count > 1:
			f_source.write('\n{ ')
		f_source.write(', '.join(heights))
		if item_count > 1:
			f_source.write(' }' + ('' if x == item_count-1 else ',') +'\n')
	f_source.write(' };\n')


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

	f_header.write('\nextern const uint8_t ' + array_name +'['+ str(len(data)) +'];\n');
	
	f_source.write('\nconst uint8_t ' + array_name +'['+ str(len(data)) +'] = {\n');
	f_source.write(',\n'.join(lines))
	f_source.write('};');

def make_sine_lookup_table(f_header, f_source, array_name, count):
	sines = []
	for i in range(0,count):
		sines.append(str(int(math.sin(i*2*math.pi/count) * 0x10000)))

	f_header.write('\nextern const int32_t ' + array_name +'['+ str(count) +'];\n');
	
	f_source.write('\nconst int32_t ' + array_name +'['+ str(count) +'] = { ');
	f_source.write(', '.join(sines))
	f_source.write(' };');

def init_ttt_typedefs(f_header):
	global init_ttt_typedefs_called
	if init_ttt_typedefs_called:
		return
	init_ttt_typedefs_called = True
	f_header.write("""

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
""")

def parse_ttp(f_header, f_source, ttp_path, track_name):
	init_ttt_typedefs(f_header)
	with open('../assets/sound/' +ttp_path, mode='rt') as f:
		ttt_json = json.load(f)
		sequence0 = '0' 
		sequence1 = '(sequence_t[]){ { .goto_index=-1, .pattern_index=0 } }'
		instruments = ['0']
		d, p = parse_ttt_percussion(ttt_json)
		percussions = [ p ]
		patterns = [ ttt_pattern_to_cpp('SFX', d['length'], d['length'], ['0x11', '0x00']) ]  
		write_ttt(f_header, f_source, track_name, sequence0, sequence1, instruments, percussions, patterns)

def parse_ttt(f_header, f_source, ttt_path, track_name, parse_0, parse_1):
	init_ttt_typedefs(f_header)
	with open('../assets/sound/' +ttt_path, mode='rt') as f:
		ttt_json = json.load(f)
		sequence0 = '0' if not parse_0 else parse_ttt_sequence(ttt_json, 0)
		sequence1 = '0' if not parse_1 else parse_ttt_sequence(ttt_json, 1)
		instruments, iids = parse_ttt_instruments(ttt_json)
		percussions = parse_ttt_percussions(ttt_json)
		patterns = parse_ttt_patterns(ttt_json, iids)
		write_ttt(f_header, f_source, track_name, sequence0, sequence1, instruments, percussions, patterns)

def write_ttt(f_header, f_source, track_name, sequence0, sequence1, instruments, percussions, patterns):
	f_header.write('\nextern const track_t {name};'.format(name=track_name))
	f_source.write("""

const track_t {name} =
{{
	.channels = {{ {{{sequence0}}}, {{{sequence1}}} }},
	.instruments = (instrument_t[]){{{instruments}}},
	.percussions = (percussion_t[]){{{percussions}}},
	.patterns = (pattern_t[]){{{patterns}}}
}};
""".format(name=track_name, instruments=',\n'.join(instruments), percussions=',\n'.join(percussions), \
			 patterns=',\n'.join(patterns), sequence0=sequence0, sequence1=sequence1))

def parse_ttt_sequence(ttt_json, index):
	sequences = []
	for sequence in ttt_json['channels'][index]['sequence']:
		sequences.append('{{ .goto_index={goto}, .pattern_index={pattern} }}' \
			.format(goto=sequence['gototarget'], pattern=sequence['patternindex']))
	return '(sequence_t[])' + '{' + ',\n'.join(sequences) + '}'

def parse_ttt_instruments(ttt_json):
	instruments_ids = []
	instruments = []
	iid = 0
	for instrument in ttt_json['instruments']:
		iid+=1
		d = { \
			'length': str(instrument['envelopeLength']), \
			'waveform': str(instrument['waveform']), \
			'sustainStart': str(instrument['sustainStart']), \
			'releaseStart': str(instrument['releaseStart']), \
			'name': str(instrument['name']), \
			'frequencies': str(', '.join(map(str, instrument['frequencies']))), \
			'volumes': str(', '.join(map(str, instrument['volumes']))), \
			}
		instruments_ids.append(iid)
		if d['name'] != '---':
			if instrument['waveform'] == 16: # waveform 16 is actually 4 + 16, split it into two instruments and fix up patterns to match
				d['waveform'] = 4
				append_instrument(instruments, d)
				d['waveform'] = 12
				iid+=1
			append_instrument(instruments, d)
	return instruments, instruments_ids

def append_instrument(instruments, d):
	instruments.append('''   {{
   // {name}
   .frequencies = (int8_t[]) {{ {frequencies} }},
   .volumes = (uint8_t[]) {{ {volumes} }},
   .sustainStart = {sustainStart},
   .releaseStart = {releaseStart},
   .waveform = {waveform},
   .length = {length}
}}'''.format(**d))

def parse_ttt_percussions(ttt_json):
	percussions = []
	for percussion in ttt_json['percussion']:
		d, a = parse_ttt_percussion(percussion)
		if d['name'] != '---':
			percussions.append(a)
	return percussions

def parse_ttt_percussion(percussion):
	d = { \
		'length': str(percussion['envelopeLength']), \
		'name': str(percussion['name']), \
		'frequencies': str(', '.join(map(str, percussion['frequencies']))), \
		'volumes': str(', '.join(map(str, percussion['volumes']))), \
		'waveforms': str(', '.join(map(str, percussion['waveforms']))), \
		}
	return d, '''   {{
   // {name}
   .frequencies = (uint8_t[]) {{ {frequencies} }},
   .volumes = (uint8_t[]) {{ {volumes} }},
   .waveforms = (uint8_t[]) {{ {waveforms} }},
   .length = {length}
}}'''.format(**d)

def parse_ttt_note(note_json, instrument_ids):
	if note_json['type'] == 0:
		return 8 # hold
	if note_json['type'] == 1:
		iid = instrument_ids[note_json['number']]
		frequency = note_json['value']
		if(frequency > 31):
			frequency -= 32
			iid+=1
		return (iid << 5) | frequency #instrument
	if note_json['type'] == 2:
		return 16 # pause
	if note_json['type'] == 3:
		return note_json['number'] + 17 # percussion
	print(note_json)
	raise 'Unknown note type'

def parse_ttt_patterns(ttt_json, instrument_ids):
	patterns = []
	try:
		global_speed = ttt_json['globalspeed']
	except KeyError:
		global_speed = True # if globalspeed is not present it defaults to True
	if global_speed:
		evenspeed = ttt_json['evenspeed'] #let this crash if it's missing 
		oddspeed = ttt_json['oddspeed']	
	for p in ttt_json['patterns']:
		if not global_speed:
			evenspeed = p['evenspeed'] #let this crash if it's missing 
			oddspeed = p['oddspeed']	
		notes = []
		for n in p['notes']:
			notes.append('0x{:02x}'.format(parse_ttt_note(n, instrument_ids)))
		notes.append('0x00') # end of notes marker
		#print(p['name'])		
		#print(evenspeed)		
		#print(oddspeed)		
		#print(',\n'.join([', '.join(notes[i:i + 8]) for i in range(0, len(notes), 8)]))
		patterns.append(ttt_pattern_to_cpp(p['name'], evenspeed, oddspeed, notes))
	return patterns

def ttt_pattern_to_cpp(name, evenspeed, oddspeed, notes):
	return '''   {{
   // {name}
   .even_speed = {evenspeed},
   .odd_speed = {oddspeed},
   .notes = (uint8_t[]) {{ {notes} }}
}}'''.format(name=name, evenspeed=evenspeed, oddspeed=oddspeed, notes=',\n'.join([', '.join(notes[i:i + 8]) for i in range(0, len(notes), 8)]))


f_header = open('sprites.h', 'wt', newline='\n')
f_header.write('''#ifndef SPRITES_H
#define SPRITES_H
#include <stdint.h>
#include "fp32.hpp"
''')

f_source = open('sprites.cpp', 'wt', newline='\n')
f_source.write('#include "sprites.h"\n')

png_name = 'ascii.png'
item_name = 'ScoreSprites'
graphic_bytes, _, _ = parse_png(png_name, 1, 1, 0, 0, 1024, 8, (0,0,0))
f_header.write('\nextern const uint8_t ' + item_name + 'Graphics[128*8];\n')
f_source.write('\nconst uint8_t ' + item_name + 'Graphics[128*8] = { ')
f_source.write(', '.join(graphic_bytes))
f_source.write(' };\n')

png_name = 'game-over.png'
item_name = 'GameOver'
graphic_bytes, _, _ = parse_png(png_name, 1, 1, 0, 0, 48, 23, None)
f_header.write('\nextern const uint8_t ' + item_name + 'Graphics[6*23];\n')
f_source.write('\nconst uint8_t ' + item_name + 'Graphics[6*23] = { ')
f_source.write(', '.join(graphic_bytes))
f_source.write(' };\n')

parse_sprite_strip(f_header, f_source, 'title-art.png', 'TitleArt', 48, 23, 2, 1, 1, 0, 0, (0,0,0))
parse_sprite_strip(f_header, f_source, 'menu-options.png', 'MenuOptions', 48, 5, 8, 1, 1, 0, 0, (0,0,0))
parse_sprite_strip(f_header, f_source, 'pf-fan-blade-animation.png', 'FanBlade', 11, 7, 7, 4, 1, 0, 0, (0,0,0))
parse_sprite_strip(f_header, f_source, 'fan-chasis.png', 'FanChasis', 8, 20, 1, 1, 1, 0, 0, (195,195,195), 0, True)
parse_sprite_strip(f_header, f_source, 'monkey-player-sprites.png', 'Monkey', 8, 13, 8, 1, 1, 0,  0, (0,0,0), 1)
parse_sprite_strip(f_header, f_source, 'monkey-player-sprites.png', 'Spider', 8, 13, 8, 1, 1, 0, 14, (0,0,0), 1)
parse_sprite_strip(f_header, f_source, 'monkey-player-sprites.png', 'Octopus', 8, 13, 8, 1, 1, 0, 28, (0,0,0), 1)
parse_sprite_strip(f_header, f_source, 'bonus-banana.png', 'BonusBanana', 8, 13, 1, 1, 1, 0, 0, (0,0,0), 0, True)
parse_sprite_strip(f_header, f_source, 'headboard-king.png', 'HeadBoardWide', 40, 40, 1, 1, 1, 0, 0, (0,0,0))
parse_sprite_strip(f_header, f_source, 'headboard-full.png', 'HeadBoardMedium', 40, 40, 1, 1, 1, 0, 0, (0,0,0))
parse_sprite_strip(f_header, f_source, 'headboard-twin.png', 'HeadBoardNarrow', 40, 40, 1, 1, 1, 0, 0, (0,0,0))
parse_sprite_strip(f_header, f_source, 'challenge-monkey-hand-open.png', 'MonkeyHandOpen', 8, 136, 1, 1, 1, 0, 0, None)
parse_sprite_strip(f_header, f_source, 'challenge-monkey-hand-closed.png', 'MonkeyHandClosed', 8, 136, 1, 1, 1, 0, 0, None)
parse_sprite_strip(f_header, f_source, 'challenge-cat-paw-open.png', 'CatPawOpen', 8, 136, 1, 1, 1, 0, 0, None)
parse_sprite_strip(f_header, f_source, 'challenge-cat-paw-closed.png', 'CatPawClosed', 8, 136, 1, 1, 1, 0, 0, None)
parse_sprite_strip(f_header, f_source, 'challenge-octopus-tentacle-open.png', 'TentacleOpen', 8, 136, 1, 1, 1, 0, 0, None)
parse_sprite_strip(f_header, f_source, 'challenge-octopus-tentacle-closed.png', 'TentacleClosed', 8, 136, 1, 1, 1, 0, 0, None)
parse_sprite_strip(f_header, f_source, 'challenge-bubbles-sprites.png', 'Bubble', 8, 15, 7, 1, 1, 1, 0, None, 1, True)
parse_sprite_strip(f_header, f_source, 'challenge-fly-2cycle.png', 'Fly', 8, 11, 2, 1, 1, 0, 0, None, 0, True)
parse_sprite_strip(f_header, f_source, 'player-1-challenge-countdown_1px_gap+48px_sprite.png', 'Countdown',   48, 31, 3, 1, 1, 0, 0, None, 1)
parse_sprite_strip(f_header, f_source, 'player-2-challenge-countdown_1px_gap+48px_sprite.png', 'CountdownP2', 48, 31, 3, 1, 1, 0, 0, None, 1)
parse_sprite_strip(f_header, f_source, 'palette.png', 'Palette', 8, 20, 1, 1, 21, 1, 0, None, 0, True)

# Previews
parse_sprite_strip(f_header, f_source, 'previews/fly_hunter.png', 'PreviewFlyHunter', 48, 192, 1, 4, 2, 0, 0, (152,92,40))
parse_sprite_strip(f_header, f_source, 'previews/bigfoots_bluff.png', 'PreviewBigfoot', 48, 192, 1, 4, 2, 0, 0, (6,57,32))
parse_sprite_strip(f_header, f_source, 'previews/octopusher.png', 'PreviewOctopusher', 48, 192, 1, 4, 2, 0, 0, (0,51,102))


parse_playfield(f_header, f_source, 'challenge-light.png', 'ChallengeLight', 34, 4, 1, 0, 0, (0,0,0))

# TODO DEPRECATE THIS FUCNTION generate_sine_tables(f_header, f_source)

bin_to_c_array(f_header, f_source, 'kernel_7800.bin', 'kernel_7800')

# Music
parse_ttt(f_header, f_source, 'MONKEYS.ttt', 'SongMonkeys', True, True)
# Sound Effects
parse_ttp(f_header, f_source, 'BedBounce.ttp', 'SfxBounce')
parse_ttp(f_header, f_source, 'BananaBonus.ttp', 'SfxBonus')
parse_ttp(f_header, f_source, 'FlyCaught.ttp', 'SfxFlyCaught')
parse_ttp(f_header, f_source, 'FanWhack.ttp', 'SfxFan')
# SFX for Challenge mode
parse_ttp(f_header, f_source, 'FlyIdle.ttp', 'SfxFlyIdle')
parse_ttp(f_header, f_source, 'FlySquish.ttp', 'SfxFlySquish')
parse_ttp(f_header, f_source, 'BubblePop.ttp', 'SfxBubblePop')
parse_ttp(f_header, f_source, 'BellShort.ttp', 'SfxBellShort')
parse_ttp(f_header, f_source, 'BellLong.ttp', 'SfxBellLong')
parse_ttp(f_header, f_source, 'TimeBonus.ttp', 'SfxTimeBonus')
parse_ttp(f_header, f_source, 'BedFall.ttp', 'SfxBedFall')

make_sine_lookup_table(f_header, f_source, 'Sine', 256);

f_header.write('\n\n#endif // SPRITES_H')
