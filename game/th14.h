#pragma once

#include "thxx.h"

namespace tori
{
	class TH14 : public THXX
	{
	public:
		enum class VERSION
		{
			V100B
		};

		TH14(HANDLE, VERSION);

		// Resets all counters of a game handle
		void reset() override;
		// Detects whether the game is being played
		bool is_ingame() override;

		// Return the value of the current difficulty.
		// Easy = 0, Normal = 1, Hard = 2, Lunatic = 3, Extra = 4.
		uint8_t get_difficulty();
		// Return the value of the current character.
		// Reimu = 0, Marisa = 1, Sakuya = 2.
		uint8_t get_character();
		// Return the value of the current subshot
		// A = 0, B = 1.
		uint8_t get_subshot();
		uint64_t get_score();
		uint16_t get_miss_count();
		uint16_t get_bomb_count();
	private:
		// address list for th14
		struct TH14_ADDR_LIST
		{
			ADDRESS_LIST p_menu;
			ADDRESS_LIST difficulty;
			ADDRESS_LIST character;
			ADDRESS_LIST subshot;
			ADDRESS_LIST score;
			ADDRESS_LIST continue_count;
			ADDRESS_LIST p_player_state;
			ADDRESS_LIST p_bomb_state;
		} th14_addr_list;

		// th14 v1.00b address list
		const TH14_ADDR_LIST TH14_ADDR_LIST_V100B = {
			{ 0x004DB6A4 },
			{ 0x004F5834 },
			{ 0x004F5828 },
			{ 0x004F582C },
			{ 0x004F5830 },
			{ 0x004F5838 },
			{ 0x004DB67C, 0x684 },
			{ 0x004DB52C, 0x40 }
		};
	private:
		HANDLE process;

		// menu pointer, used for detecting in-game state
		uint32_t p_menu = 0;
		// get_difficulty
		uint8_t difficulty = 0;
		// get shottype
		uint8_t character = 0, subshot = 0;
		// get score
		uint32_t score = 0;
		uint8_t continue_count = 0;
		// get miss count
		uint8_t player_state = 0, _player_state = 0;
		uint16_t miss_count = 0;
		// get bomb count
		uint8_t bomb_state = 0, _bomb_state = 0;
		uint16_t bomb_count = 0;
	};
}
