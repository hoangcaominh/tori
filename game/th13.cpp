#include "th13.h"

namespace tori
{
	TH13::TH13(HANDLE process, VERSION version) : process(process)
	{
		switch (version)
		{
		case TH13::VERSION::V100C:
			th13_addr_list = TH13_ADDR_LIST_V100C;
			break;
		}
	}

	void TH13::reset()
	{
		miss_count = 0;
		bomb_count = 0;
		trance_count = 0;
	}

	bool TH13::is_ingame()
	{
		if (!read_memory_32(process, th13_addr_list.p_menu, (void*)&p_menu, sizeof(p_menu)))
			fprintf(stderr, "Failed to read memory of menu pointer.\n");
		return p_menu == NULL;
	}

	uint8_t TH13::get_difficulty()
	{
		if (!read_memory_32(process, th13_addr_list.difficulty, (void*)&difficulty, sizeof(difficulty)))
			fprintf(stderr, "Failed to read memory of difficulty.\n");
		return difficulty;
	}

	uint8_t TH13::get_character()
	{
		if (!read_memory_32(process, th13_addr_list.character, (void*)&character, sizeof(character)))
			fprintf(stderr, "Failed to read memory of character.\n");
		return character;
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
}
