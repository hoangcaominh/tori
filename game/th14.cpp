#include "th14.h"

TH14::TH14(HANDLE process, VERSION version) : process(process)
{
	switch (version)
	{
	case TH14::VERSION::V100B:
		th14_addr_list = {
			{ 0x004F5834 },
			{ 0x004F5828 },
			{ 0x004F582C },
			{ 0x004F5830 },
			{ 0x004F5838 },
			{ 0x004DB67C, 0x684 },
			{ 0x004DB52C, 0x40 }
		};
		break;
	}
}

void TH14::reset()
{

}

const char* TH14::get_difficulty()
{
	if (!read_memory_32(process, th14_addr_list.difficulty, (void*)&difficulty, sizeof(difficulty)))
		fprintf(stderr, "Failed to read memory of difficulty.\n");
	return arr_difficulty[difficulty];
}

const char* TH14::get_character()
{
	if (!read_memory_32(process, th14_addr_list.character, (void*)&character, sizeof(character)))
		fprintf(stderr, "Failed to read memory of character.\n");
	return arr_character[character];
}

const char* TH14::get_subshot()
{
	if (!read_memory_32(process, th14_addr_list.subshot, (void*)&subshot, sizeof(subshot)))
		fprintf(stderr, "Failed to read memory of subshot.\n");
	return arr_subshot[subshot];
}

uint16_t TH14::get_miss_count()
{
	if (!read_memory_32(process, th14_addr_list.p_player_state, (void*)&player_state, sizeof(player_state)))
		fprintf(stderr, "Failed to read memory of player state.\n");

	// if player_state changes form 4 to 2, increase miss_count by 1
	if (player_state == 2 && player_state != _player_state)
		miss_count++;
	_player_state = player_state;

	return miss_count;
}

uint16_t TH14::get_bomb_count()
{
	if (!read_memory_32(process, th14_addr_list.p_bomb_state, (void*)&bomb_state, sizeof(bomb_state)))
		fprintf(stderr, "Failed to read memory of bomb state.\n");

	// if bomb_state changes to 1, increase bomb_count by 1
	if (bomb_state && bomb_state != _bomb_state)
		bomb_count++;
	_bomb_state = bomb_state;

	return bomb_count;
}

uint64_t TH14::get_score()
{
	if (!read_memory_32(process, th14_addr_list.score, (void*)&score, sizeof(uint32_t)))
		fprintf(stderr, "Failed to read memory of score.\n");
	if (!read_memory_32(process, th14_addr_list.continue_count, (void*)&continue_count, sizeof(continue_count)))
		fprintf(stderr, "Failed to read memory of continue.\n");
	return score * 10 + continue_count;
}
