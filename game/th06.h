#pragma once

#include "thxx.h"

class TH06 : public THXX
{
public:
	enum class VERSION
	{
		V102H
	};

	TH06(HANDLE, VERSION);

	void reset() override;
	// Return the value of the current difficulty.
	// Easy = 0, Normal = 1, Hard = 2, Lunatic = 3, Extra = 4.
	uint8_t get_difficulty();
	// Return the value of the current character.
	// Reimu = 0, Marisa = 1.
	uint8_t get_character();
	// Return the value of the current subshot
	// A = 0, B = 1.
	uint8_t get_subshot();
	uint32_t get_score();
	uint16_t get_miss_count();
	uint16_t get_bomb_count();
private:
	HANDLE process;

	// address list for th06
	struct TH06_ADDR_LIST
	{
		ADDRESS_LIST difficulty;
		ADDRESS_LIST character;
		ADDRESS_LIST subshot;
		ADDRESS_LIST score;
		ADDRESS_LIST deathbomb_window;
		ADDRESS_LIST bomb_count;
	} th06_addr_list;

	// get_difficulty
	uint16_t difficulty = 0;
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
