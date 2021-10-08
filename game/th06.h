#pragma once

#include "thxx.h"

namespace tori
{
	class TH06 : public THXX
	{
	public:
		enum class VERSION
		{
			V102H
		};

		TH06(HANDLE, VERSION);

		// Resets all counters of a game handle
		void reset() override;
		// Detects whether the game is being played
		bool is_ingame() override;

		// Return the value of the current difficulty.
		// Easy = 0, Normal = 1, Hard = 2, Lunatic = 3, Extra = 4.
		uint8_t get_difficulty();
		// Return the value of the current character.
		// Reimu = 0, Marisa = 1.
		uint8_t get_character();
		// Return the value of the current subshot
		// A = 0, B = 1.
		uint8_t get_subshot();
		uint64_t get_score();
		uint16_t get_miss_count();
		uint16_t get_bomb_count();
	private:
		// address list for th06
		struct TH06_ADDR_LIST
		{
			ADDRESS_LIST menu_showing;
			ADDRESS_LIST menu;
			ADDRESS_LIST difficulty;
			ADDRESS_LIST character;
			ADDRESS_LIST subshot;
			ADDRESS_LIST score;
			ADDRESS_LIST deathbomb_window;
			ADDRESS_LIST bomb_count;
		} th06_addr_list;

		// th06 v1.02h address list
		const TH06_ADDR_LIST TH06_ADDR_LIST_V102H = {
			{ 0x006DC8F8 },
			{ 0x006DC8B0 },
			{ 0x0069BCB0 },
			{ 0x0069D4BD },
			{ 0x0069D4BE },
			{ 0x0069BCA0 },
			{ 0x006CB000 },
			{ 0x0069BCC4 }
		};
	private:
		HANDLE process;

		// menu values used for detecting in-game state using touhourpc method
		bool menu_showing = false;
		uint8_t menu = 0;
		// get_difficulty
		uint8_t difficulty = 0;
		// get shottype
		uint8_t character = 0, subshot = 0;
		// get miss count
		uint8_t deathbomb_window = 0, _deathbomb_window = 0;
		uint16_t miss_count = 0;
		// get bomb count
		uint16_t bomb_count = 0;
		// get score
		uint32_t score = 0;
	};
}
