#include "th11.h"

namespace tori
{
	TH11::TH11(HANDLE process, VERSION version) : process(process)
	{
		switch (version)
		{
		case TH11::VERSION::V100A:
			th11_addr_list = TH11_ADDR_LIST_V100A;
			break;
		}
	}

	void TH11::reset()
	{
		miss_count = 0;
		bomb_count = 0;
	}

	bool TH11::is_ingame()
	{
		if (!read_memory_32(process, th11_addr_list.p_menu, (void*)&p_menu, sizeof(p_menu)))
			fprintf(stderr, "Failed to read memory of menu pointer.\n");
		return p_menu == NULL;
	}

	uint8_t TH11::get_difficulty()
	{
		if (!read_memory_32(process, th11_addr_list.difficulty, (void*)&difficulty, sizeof(difficulty)))
			fprintf(stderr, "Failed to read memory of difficulty.\n");
		return difficulty;
	}

	uint8_t TH11::get_character()
	{
		if (!read_memory_32(process, th11_addr_list.character, (void*)&character, sizeof(character)))
			fprintf(stderr, "Failed to read memory of character.\n");
		return character;
	}

	uint8_t TH11::get_subshot()
	{
		if (!read_memory_32(process, th11_addr_list.subshot, (void*)&subshot, sizeof(subshot)))
			fprintf(stderr, "Failed to read memory of subshot.\n");
		return subshot;
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
}
