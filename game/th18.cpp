#include "th18.h"

TH18::TH18(HANDLE process, VERSION version) : process(process)
{
	switch (version)
	{
	case TH18::VERSION::V100A:
		th18_addr_list = {
			{ 0x004CCD00 },
			{ 0x004CCCF4 },
			{ 0x004CCCFC },
			{ 0x004CCD04 },
			{ 0x004CF410, 0x476AC },
			{ 0x004CF2B8, 0x30 }
		};
		break;
	}
}

void TH18::reset()
{

}

const char* TH18::get_difficulty()
{
	if (!read_memory_32(process, th18_addr_list.difficulty, (void*)&difficulty, sizeof(difficulty)))
		fprintf(stderr, "Failed to read memory of difficulty.\n");
	return arr_difficulty[difficulty];
}

const char* TH18::get_character()
{
	if (!read_memory_32(process, th18_addr_list.character, (void*)&character, sizeof(character)))
		fprintf(stderr, "Failed to read memory of character.\n");
	return arr_character[character];
}

uint64_t TH18::get_score()
{
	if (!read_memory_32(process, th18_addr_list.score, (void*)&score, sizeof(score)))
		fprintf(stderr, "Failed to read memory of score.\n");
	if (!read_memory_32(process, th18_addr_list.continue_count, (void*)&continue_count, sizeof(continue_count)))
		fprintf(stderr, "Failed to read memory of continue.\n");
	return (uint64_t)score * 10 + continue_count;
}

uint16_t TH18::get_miss_count()
{
	if (!read_memory_32(process, th18_addr_list.p_player_state, (void*)&player_state, sizeof(player_state)))
		fprintf(stderr, "Failed to read memory of player state.\n");

	// if player_state changes form 4 to 2, increase miss_count by 1
	if (player_state == 2 && player_state != _player_state)
		miss_count++;
	_player_state = player_state;

	return miss_count;
}

uint16_t TH18::get_bomb_count()
{
	if (!read_memory_32(process, th18_addr_list.p_bomb_state, (void*)&bomb_state, sizeof(bomb_state)))
		fprintf(stderr, "Failed to read memory of bomb state.\n");

	// if bomb_state changes to 1, increase bomb_count by 1
	if (bomb_state && bomb_state != _bomb_state)
		bomb_count++;
	_bomb_state = bomb_state;

	return bomb_count;
}
