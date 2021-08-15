#include "th13.h"

TH13::TH13(HANDLE process, VERSION version) : process(process)
{
	switch (version)
	{
	case TH13::VERSION::V100C:
		th13_addr_list = {
			{ 0x004BE7C4 },
			{ 0x004BE7B8 },
			{ 0x004BE7C0 },
			{ 0x004BE7C8 },
			{ 0x004C22C4, 0x65C },
			{ 0x004C2170, 0x40 },
			{ 0x004BE831 }
		};
		break;
	}
}

void TH13::reset()
{

}

const char* TH13::get_difficulty()
{
	if (!read_memory_32(process, th13_addr_list.difficulty, (void*)&difficulty, sizeof(difficulty)))
		fprintf(stderr, "Failed to read memory of difficulty.\n");
	return arr_difficulty[difficulty];
}

const char* TH13::get_character()
{
	if (!read_memory_32(process, th13_addr_list.character, (void*)&character, sizeof(character)))
		fprintf(stderr, "Failed to read memory of character.\n");
	return arr_character[character];
}

uint64_t TH13::get_score()
{
	if (!read_memory_32(process, th13_addr_list.score, (void*)&score, sizeof(score)))
		fprintf(stderr, "Failed to read memory of score.\n");
	if (!read_memory_32(process, th13_addr_list.continue_count, (void*)&continue_count, sizeof(continue_count)))
		fprintf(stderr, "Failed to read memory of continue.\n");
	return (uint64_t)score * 10 + continue_count;
}

uint16_t TH13::get_miss_count()
{
	if (!read_memory_32(process, th13_addr_list.p_player_state, (void*)&player_state, sizeof(player_state)))
		fprintf(stderr, "Failed to read memory of player state.\n");

	// if player_state changes form 4 to 2, increase miss_count by 1
	if (player_state == 2 && player_state != _player_state)
		miss_count++;
	_player_state = player_state;

	return miss_count;
}

uint16_t TH13::get_bomb_count()
{
	if (!read_memory_32(process, th13_addr_list.p_bomb_state, (void*)&bomb_state, sizeof(bomb_state)))
		fprintf(stderr, "Failed to read memory of bomb state.\n");

	// if bomb_state changes to 1, increase bomb_count by 1
	if (bomb_state && bomb_state != _bomb_state)
		bomb_count++;
	_bomb_state = bomb_state;

	return bomb_count;
}

uint16_t TH13::get_trance_count()
{
	if (!read_memory_32(process, th13_addr_list.p_player_state, (void*)&player_state, sizeof(player_state)))
		fprintf(stderr, "Failed to read memory of player state.\n");
	if (!read_memory_32(process, th13_addr_list.trance_state, (void*)&trance_state, sizeof(trance_state)))
		fprintf(stderr, "Failed to read memory of trance state.\n");

	// If trance is over, check if the player dies
	if ((!trance_state && trance_state != _trance_state) && player_state != 2)
		trance_count++;
	_trance_state = trance_state;

	return trance_count;
}
