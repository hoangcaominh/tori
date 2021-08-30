#pragma once

#include "thxx.h"

class TH13 : public THXX
{
public:
	enum class VERSION
	{
		V100C
	};

	TH13(HANDLE, VERSION);

	// Resets all counters of a game handle
	void reset() override;
	// Detects whether the game is being played
	bool is_ingame() override;

	// Return the value of the current difficulty.
	// Easy = 0, Normal = 1, Hard = 2, Lunatic = 3, Extra = 4, Overdrive = 5.
	uint8_t get_difficulty();
	// Return the value of the current character.
	// Reimu = 0, Marisa = 1, Sanae = 2, Youmu = 3.
	uint8_t get_character();
	uint64_t get_score();
	uint16_t get_miss_count();
	uint16_t get_bomb_count();
	uint16_t get_trance_count();
private:
	// address list for th13
	struct TH13_ADDR_LIST
	{
		ADDRESS_LIST p_menu;
		ADDRESS_LIST difficulty;
		ADDRESS_LIST character;
		ADDRESS_LIST score;
		ADDRESS_LIST continue_count;
		ADDRESS_LIST p_player_state;
		ADDRESS_LIST p_bomb_state;
		ADDRESS_LIST trance_state;
	} th13_addr_list;

	// th13 v1.00c address list
	const TH13_ADDR_LIST TH13_ADDR_LIST_V100C = {
		{ 0x004C22E0 },
		{ 0x004BE7C4 },
		{ 0x004BE7B8 },
		{ 0x004BE7C0 },
		{ 0x004BE7C8 },
		{ 0x004C22C4, 0x65C },
		{ 0x004C2170, 0x40 },
		{ 0x004BE831 }
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
	// get trance count
	uint8_t trance_state = 0, _trance_state = 0;
	uint16_t trance_count = 0;
};
