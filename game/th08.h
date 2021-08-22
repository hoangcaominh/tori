#pragma once

#include "thxx.h"

class TH08 : public THXX
{
public:
	enum class VERSION
	{
		V100D
	};

	TH08(HANDLE, VERSION);

	void reset() override;
	// Return the value of the current difficulty.
	// Easy = 0, Normal = 1, Hard = 2, Lunatic = 3, Extra = 4.
	uint8_t get_difficulty();
	// Return the value of the current character.
	// Border team = 0, Magic team = 1, Scarlet team = 2, Ghost team = 3,
	// Reimu = 4, Yukari = 5, Marisa = 6, Alice = 7, Sakuya = 8, Remilia = 9, Youmu = 10, Yuyuko = 11.
	uint8_t get_character();
	// Return the value of the current stage.
	// Stage 1 = 0, 2 = 1, 3 = 2, 4A = 3, 4B = 4, 5 = 5, 6A = 6, 6B = 7, Extra = 8.
	uint8_t get_stage();
	uint64_t get_score();
	uint16_t get_miss_count();
	uint16_t get_bomb_count();
	uint16_t get_spell_captured_count();
private:
	// address list for th08
	struct TH08_ADDR_LIST
	{
		ADDRESS_LIST difficulty;
		ADDRESS_LIST character;
		ADDRESS_LIST stage;
		ADDRESS_LIST score;
		ADDRESS_LIST continue_count;
		ADDRESS_LIST miss_count;
		ADDRESS_LIST bomb_count;
		ADDRESS_LIST deathbomb_count;
		ADDRESS_LIST spell_captured_count;
	} th08_addr_list;

	// th08 v1.00d address list
	const TH08_ADDR_LIST TH08_ADDR_LIST_V100D = {
		{ 0x0160F538 },
		{ 0x0164D0B1 },
		{ 0x004E4850 },
		{ 0x0160F510, 0x0 },
		{ 0x004D77DC },
		{ 0x0164CFA4 },
		{ 0x0164CFA8 },
		{ 0x0164CFAC },
		{ 0x0160F510, 0x1C }
	};
private:
	HANDLE process;

	// get_difficulty
	uint8_t difficulty = 0;
	// get shottype
	uint8_t character = 0;
	// get stage
	uint8_t stage = 0;
	// get score
	uint32_t score = 0;
	uint8_t continue_count = 0;
	// get miss count
	uint16_t miss_count = 0;
	// get bomb count
	uint16_t bomb_count = 0, deathbomb_count = 0;
	// get spell captured count
	uint16_t spell_captured_count = 0;
};
