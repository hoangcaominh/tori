#pragma once

#include "thxx.h"

namespace tori
{
	class TH10 : public THXX
	{
	public:
		enum class VERSION
		{
			V100A
		};

		TH10(HANDLE, VERSION);

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
		// A = 0, B = 1, C = 2.
		uint8_t get_subshot();
		uint64_t get_score();
		uint16_t get_miss_count();
		uint16_t get_bomb_count();
	private:
		// address list for th10
		struct TH10_ADDR_LIST
		{
			ADDRESS_LIST p_menu;
			ADDRESS_LIST difficulty;
			ADDRESS_LIST character;
			ADDRESS_LIST subshot;
			ADDRESS_LIST score;
			ADDRESS_LIST continue_count;
			ADDRESS_LIST p_player_state;
			ADDRESS_LIST p_bomb_state;
		} th10_addr_list;

		// th10 v1.00a address list
		const TH10_ADDR_LIST TH10_ADDR_LIST_V100A = {
			{ 0x0047784C },
			{ 0x00474C74 },
			{ 0x00474C68 },
			{ 0x00474C6C },
			{ 0x00474C44 },
			{ 0x00474C90 },
			{ 0x00477834, 0x458 },
			{ 0x004776EC, 0x28 }
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
