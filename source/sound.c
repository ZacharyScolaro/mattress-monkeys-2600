#include "sound.h"

void init_audio_player(track_player* player, uint8_t channel_index, const track_t* track)
{
	player->channel_index = channel_index;
	player->control = player->frequency = player->volume = 0;
	player->sequence_index = player->tick_count = 0;
	player->track = track;
	player->tick_count = 254;
	player->note_index = -1;
}

void get_note(track_player* player)
{
	player->debug = &player->ppattern->notes[player->note_index];
	player->note = player->ppattern->notes[player->note_index];
	//player->note = player->ppattern->notes[0]; // Uncomment this line fixes issue
}

void next_audio_frame(track_player* player) {
	const sequence_t* sequence = &player->track->channels[player->channel_index].sequenced_patterns[player->sequence_index];
	const pattern_t* pattern = &player->track->patterns[sequence->pattern_index];
	uint8_t tempo = (player->note_index & 1) ? pattern->odd_speed : pattern->even_speed;
	player->tick_count++;
	if (player->tick_count >= tempo)
	{
		player->tick_count = 0;
		// time to get the next note
		player->note_index++;
		while (pattern->notes[player->note_index] == 0)
		{
			// time to get the next pattern
			if (sequence->goto_index == -1)
			{
				player->sequence_index++;
			}
			else
			{
				player->sequence_index = sequence->goto_index;
			}
			sequence = &player->track->channels[player->channel_index].sequenced_patterns[player->sequence_index];
			pattern = &player->track->patterns[sequence->pattern_index];
			player->note_index = 0;
		}

		player->ppattern = pattern;
		get_note(player);
		player->is_release = 0;
		if ((player->note & 0xe0))
		{
			// new melodic
			player->instrument_index = (player->note >> 5) - 1;
			player->envelope_index = -1; // account for increment
			player->base_frequency = player->note & 0x1f;
		}
		else if (player->note > 16)
		{
			// new percussion
			player->instrument_index = player->note - 17;
			player->envelope_index = -1; // account for increment
		}
		else if (player->note == 8)
		{
			// Hold
		}
		else if (player->note == 16)
		{
			// Pause
			player->is_release = 1;
		}
	}

	player->envelope_index++;
	if ((player->note & 0xe0) || player->note == 8 || player->note == 16)
	{
		const instrument_t* instrument = &player->track->instruments[player->instrument_index];
		if (player->envelope_index >= instrument->length)
		{
			player->volume = 0;
			return;
		}
		if (player->is_release && player->envelope_index < instrument->releaseStart)
		{
			player->envelope_index = instrument->releaseStart;
		}
		if (!player->is_release && player->envelope_index >= instrument->releaseStart)
		{
			player->envelope_index = instrument->sustainStart;
		}
		player->control = instrument->waveform;
		player->frequency = player->base_frequency + instrument->frequencies[player->envelope_index];
		player->volume = instrument->volumes[player->envelope_index];
	}
	else if (player->note > 16)
	{
		const percussion_t* percussion = &player->track->percussions[player->instrument_index];
		if (player->envelope_index >= percussion->length)
		{
			player->volume = 0;
			return;
		}
		player->control = percussion->waveforms[player->envelope_index];
		player->frequency = percussion->frequencies[player->envelope_index];
		player->volume = percussion->volumes[player->envelope_index];
	}

	// TODO slide
}