#include "sprites.h"

typedef struct {
	uint8_t volume;
	uint8_t base_frequency;
	uint8_t frequency;
	uint8_t control;
	uint8_t last_note; // melodic or percussion only, so we can hold or slide it on subsequent beats
	uint8_t channel_index;
	uint8_t sequence_index;
	uint8_t instrument_index;
	int8_t envelope_index;
	uint8_t tick_count;
	uint8_t note;
	uint8_t is_release;
	int16_t note_index;
	const track_t* track;
} track_player;

void init_audio_player(track_player* player, uint8_t channel_index, const track_t* track);

void next_audio_frame(track_player* player);