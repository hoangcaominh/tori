#pragma once

#include "thxx.h"

class TH07 : public THXX
{
public:
	enum class VERSION
	{
		V100B
	};

	TH07(HANDLE, VERSION);

	void reset() override;
	// Return the value of the current difficulty.
	// Easy = 0, Normal = 1, Hard = 2, Lunatic = 3, Extra = 4, Phantasm = 5.
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
	uint16_t get_border_break_count();
private:
	// address list for th07
	struct TH07_ADDR_LIST
	{
		ADDRESS_LIST difficulty;
		ADDRESS_LIST character;
		ADDRESS_LIST subshot;
		ADDRESS_LIST score;
		ADDRESS_LIST continue_count;
		ADDRESS_LIST miss_count;
		ADDRESS_LIST bomb_count;
		ADDRESS_LIST cherryp_state;
		ADDRESS_LIST border_state;
	} th07_addr_list;

	// th07 v1.00b address list
	const TH07_ADDR_LIST TH07_ADDR_LIST_V100B = {
		{ 0x00626280 },
		{ 0x0062F645 },
		{ 0x0062F646 },
		{ 0x00626278, 0x0 },
		{ 0x00626278, 0x20 },
		{ 0x00626278, 0x50 },
		{ 0x00626278, 0x6C },
		{ 0x004BFEE5 },
		{ 0x01346218 }
	};
private:
	HANDLE process;

	// get_difficulty
	uint8_t difficulty = 0;
	// get shottype
	uint8_t character = 0, subshot = 0;
	// get score
	uint32_t score = 0;
	uint8_t continue_count = 0;
	// get miss count
	float miss_count = 0;
	// get bomb count
	float bomb_count = 0;
	// get border break count
	uint8_t cherryp_state = 0, _cherryp_state = 0, border_state = 0; // this one weird doe
	uint16_t border_break_count = 0;
};
