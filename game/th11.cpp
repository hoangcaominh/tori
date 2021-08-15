#include "th11.h"

TH11::TH11(HANDLE process, VERSION version) : process(process)
{
	switch (version)
	{
	case TH11::VERSION::V100A:
		th11_addr_list = {
			{ 0x004A5720 },
			{ 0x004A5710 },
			{ 0x004A5714 },
			{ 0x004A56E4 },
			{ 0x004A573C },
			{ 0x004A8EB4, 0x928 },
			{ 0x004A8D64, 0x3C }
		};
		break;
	}
}

void TH11::reset()
{

}

const char* TH11::get_difficulty()
{
	if (!read_memory_32(process, th11_addr_list.difficulty, (void*)&difficulty, sizeof(difficulty)))
		fprintf(stderr, "Failed to read memory of difficulty.\n");
	return arr_difficulty[difficulty];
}

const char* TH11::get_character()
{
	if (!read_memory_32(process, th11_addr_list.character, (void*)&character, sizeof(character)))
		fprintf(stderr, "Failed to read memory of character.\n");
	return arr_character[character];
}

const char* TH11::get_subshot()
{
	if (!read_memory_32(process, th11_addr_list.subshot, (void*)&subshot, sizeof(subshot)))
		fprintf(stderr, "Failed to read memory of subshot.\n");
	return arr_subshot[subshot];
}

uint64_t TH11::get_score()
{
	if (!read_memory_32(process, th11_addr_list.score, (void*)&score, sizeof(score)))
		fprintf(stderr, "Failed to read memory of score.\n");
	if (!read_memory_32(process, th11_addr_list.continue_count, (void*)&continue_count, sizeof(continue_count)))
		fprintf(stderr, "Failed to read memory of continue.\n");
	return (uint64_t)score * 10 + continue_count;
}

uint16_t TH11::get_miss_count()
{
	if (!read_memory_32(process, th11_addr_list.p_player_state, (void*)&player_state, sizeof(player_state)))
		fprintf(stderr, "Failed to read memory of player state.\n");

	// if player_state changes form 4 to 2, increase miss_count by 1
	if (player_state == 2 && player_state != _player_state)
		miss_count++;
	_player_state = player_state;

	return miss_count;
}

uint16_t TH11::get_bomb_count()
{
	if (!read_memory_32(process, th11_addr_list.p_bomb_state, (void*)&bomb_state, sizeof(bomb_state)))
		fprintf(stderr, "Failed to read memory of bomb state.\n");

	// if bomb_state changes to 1, increase bomb_count by 1
	if (bomb_state && bomb_state != _bomb_state)
		bomb_count++;
	_bomb_state = bomb_state;

	return bomb_count;
}
