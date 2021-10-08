#pragma once

#include "thxx.h"

namespace tori
{
	class TH16 : public THXX
	{
	public:
		enum class VERSION
		{
			V100A
		};

		TH16(HANDLE, VERSION);

		// Resets all counters of a game handle
		void reset() override;
		// Detects whether the game is being played
		bool is_ingame() override;

		// Return the value of the current difficulty.
		// Easy = 0, Normal = 1, Hard = 2, Lunatic = 3, Extra = 4.
		uint8_t get_difficulty();
		// Return the value of the current character.
		// Reimu = 0, Cirno = 1, Aya = 2, Marisa = 3.
		uint8_t get_character();
		// Return the value of the current season shot
		// Spring = 0, Summer = 1, Autumn = 2, Winter = 3, Ex = 4.
		uint8_t get_seasonshot();
		uint64_t get_score();
		uint16_t get_miss_count();
		uint16_t get_bomb_count();
		uint16_t get_release_count();
	private:
		// address list for th16
		struct TH16_ADDR_LIST
		{
			ADDRESS_LIST p_menu;
			ADDRESS_LIST difficulty;
			ADDRESS_LIST character;
			ADDRESS_LIST season;
			ADDRESS_LIST score;
			ADDRESS_LIST continue_count;
			ADDRESS_LIST p_player_state;
			ADDRESS_LIST p_bomb_state;
			ADDRESS_LIST p_release_state;
		} th16_addr_list;

		// th16 v1.00a address list
		const TH16_ADDR_LIST TH16_ADDR_LIST_V100A = {
			{ 0x004A6F20 },
			{ 0x004A57B4 },
			{ 0x004A57A4 },
			{ 0x004A57AC },
			{ 0x004A57B0 },
			{ 0x004A57B8 },
			{ 0x004A6EF8, 0x165A8 },
			{ 0x004A6DA8, 0x30 },
			{ 0x004A6DA4, 0x30 }
		};
	private:
		HANDLE process;

		// menu pointer, used for detecting in-game state
		uint32_t p_menu = 0;
		// get_difficulty
		uint8_t difficulty = 0;
		// get shottype
		uint8_t character = 0, season = 0;
		// get score
		uint32_t score = 0;
		uint8_t continue_count = 0;
		// get miss count
		uint8_t player_state = 0, _player_state = 0;
		uint16_t miss_count = 0;
		// get bomb count
		uint8_t bomb_state = 0, _bomb_state = 0;
		uint16_t bomb_count = 0;
		// get reelase count
		uint8_t release_state = 0, _release_state = 0;
		uint16_t release_count = 0;
	};
}
