#pragma once

#include "thxx.h"

class TH18 : public THXX
{
public:
	enum class VERSION
	{
		V100A
	};

	TH18(HANDLE, VERSION);

	// Resets all counters of a game handle
	void reset() override;
	// Detects whether the game is being played
	bool is_ingame() override;

	// Return the value of the current difficulty.
	// Easy = 0, Normal = 1, Hard = 2, Lunatic = 3, Extra = 4.
	uint8_t get_difficulty();
	// Return the value of the current character.
	// Reimu = 0, Marisa = 1, Sakuya = 2, Sanae = 3.
	uint8_t get_character();
	uint64_t get_score();
	uint16_t get_miss_count();
	uint16_t get_bomb_count();
private:
	// address list for th18
	struct TH18_ADDR_LIST
	{
		ADDRESS_LIST p_menu;
		ADDRESS_LIST difficulty;
		ADDRESS_LIST character;
		ADDRESS_LIST score;
		ADDRESS_LIST continue_count;
		ADDRESS_LIST p_player_state;
		ADDRESS_LIST p_bomb_state;
	} th18_addr_list;

	// th18 v1.00a address list
	const TH18_ADDR_LIST TH18_ADDR_LIST_V100A = {
		{ 0x004CF43C },
		{ 0x004CCD00 },
		{ 0x004CCCF4 },
		{ 0x004CCCFC },
		{ 0x004CCD04 },
		{ 0x004CF410, 0x476AC },
		{ 0x004CF2B8, 0x30 }
	};
private:
	HANDLE process;

	// menu pointer, used for detecting in-game state
	uint32_t p_menu = 0;
	// get_difficulty
	uint8_t difficulty = 0;
	// get shottype
	uint8_t character = 0;
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
