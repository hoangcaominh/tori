#pragma once

#include "thxx.h"

namespace tori
{
	class TH128 : public THXX
	{
	public:
		enum class VERSION
		{
			V100A
		};

		TH128(HANDLE, VERSION);

		// Resets all counters of a game handle
		void reset() override;
		// Detects whether the game is being played
		bool is_ingame() override;

		struct Medals
		{
			uint16_t bronze, silver, gold;
		};

		// Return the value of the current difficulty.
		// Easy = 0, Normal = 1, Hard = 2, Lunatic = 3, Extra = 4.
		uint8_t get_difficulty();
		// Return the value of the current stage.
		// A1-1 = 1, A1-2 = 2, A1-3 = 3, A2-2 = 4, A2-3 = 5,
		// B1-1 = 5, B1-2 = 7, B1-3 = 8, B2-2 = 9, B2-3 = 10,
		// C1-1 = 11, C1-2 = 12, C1-3 = 13, C2-2 = 14, C2-3 = 15,
		// Ex = 16.
		uint8_t get_stage();
		uint64_t get_score();
		uint16_t get_miss_count();
		uint16_t get_bomb_count();
		Medals get_medals();
	private:
		// address list for th128
		struct TH128_ADDR_LIST
		{
			ADDRESS_LIST p_menu;
			ADDRESS_LIST difficulty;
			ADDRESS_LIST stage;
			ADDRESS_LIST score;
			ADDRESS_LIST continue_count;
			ADDRESS_LIST p_player_state;
			ADDRESS_LIST p_bomb_state;
			ADDRESS_LIST p_medal_state;
		} th128_addr_list;

		// th128 v1.00a address list
		const TH128_ADDR_LIST TH128_ADDR_LIST_V100A = {
			{ 0x004B8A9C },
			{ 0x004B4D0C },
			{ 0x004B4D14 },
			{ 0x004B4CC4 },
			{ 0x004B4D28 },
			{ 0x004B8A80, 0xF78 },
			{ 0x004B892C, 0x40 },
			{ 0x004B8934, 0x7C }
		};
	private:
		HANDLE process;

		// menu pointer, used for detecting in-game state
		uint32_t p_menu = 0;
		// get_difficulty
		uint8_t difficulty = 0;
		// get stage/route
		uint8_t stage = 0;
		// get miss count
		uint8_t player_state = 0, _player_state = 0;
		uint16_t miss_count = 0;
		// get bomb count
		uint8_t bomb_state = 0, _bomb_state = 0;
		uint16_t bomb_count = 0;
		// get score
		uint32_t score = 0;
		uint8_t continue_count = 0;
		// get medals
		uint8_t medal_state = 0, _medal_state = 0;
		Medals medals = { 0, 0, 0 };
	};
}
