#include "th15.h"

TH15::TH15(HANDLE process, VERSION version) : process(process)
{
	switch (version)
	{
	case TH15::VERSION::V100B:
		th15_addr_list = {
			{ 0x004E7410 },
			{ 0x004E7404 },
			{ 0x004E9BB8, 0x16220 },
			{ 0x004E9A68, 0x24 },
			{ 0x004E740C },
			{ 0x004E7414 },
		};
		break;
	}
}

void TH15::reset()
{

}

const char* TH15::get_difficulty()
{
	if (!read_memory_32(process, th15_addr_list.difficulty, (void*)&difficulty, sizeof(difficulty)))
		fprintf(stderr, "Failed to read memory of difficulty.\n");
	return arr_difficulty[difficulty];
}

std::string TH15::get_shottype()
{
	std::string shottype;
	if (!read_memory_32(process, th15_addr_list.character, (void*)&character, sizeof(character)))
		fprintf(stderr, "Failed to read memory of character.\n");
	shottype += character;
	return shottype;
}

uint16_t TH15::get_miss_count()
{
	if (!read_memory_32(process, th15_addr_list.p_player_state, (void*)&player_state, sizeof(player_state)))
		fprintf(stderr, "Failed to read memory of player state.\n");

	// if player_state changes form 4 to 2, increase miss_count by 1
	if (player_state == 2 && player_state != _player_state)
		miss_count++;
	_player_state = player_state;

	return miss_count;
}

uint16_t TH15::get_bomb_count()
{
	if (!read_memory_32(process, th15_addr_list.p_bomb_state, (void*)&bomb_state, sizeof(bomb_state)))
		fprintf(stderr, "Failed to read memory of bomb state.\n");

	// if bomb_state changes to 1, increase bomb_count by 1
	if (bomb_state && bomb_state != _bomb_state)
		bomb_count++;
	_bomb_state = bomb_state;

	return bomb_count;
}

uint64_t TH15::get_score()
{
	if (!read_memory_32(process, th15_addr_list.score, (void*)&score, sizeof(uint32_t)))
		fprintf(stderr, "Failed to read memory of score.\n");
	if (!read_memory_32(process, th15_addr_list.continue_count, (void*)&continue_count, sizeof(continue_count)))
		fprintf(stderr, "Failed to read memory of continue.\n");
	return score * 10 + continue_count;
}
