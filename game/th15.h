#pragma once

#include "thxx.h"

class TH15 : public THXX
{
public:
	enum class VERSION
	{
		V100B
	};

	TH15(HANDLE, VERSION);

	void reset() override;
	// Return the value of the current difficulty.
	// Easy = 0, Normal = 1, Hard = 2, Lunatic = 3, Extra = 4.
	uint8_t get_difficulty();
	// Return the value of the current character.
	// Reimu = 0, Marisa = 1, Sanae = 2, Reisen = 3.
	uint8_t get_character();
	uint64_t get_score();
	uint16_t get_miss_count();
	uint16_t get_bomb_count();
private:
	// address list for th15
	struct TH15_ADDR_LIST
	{
		ADDRESS_LIST difficulty;
		ADDRESS_LIST character;
		ADDRESS_LIST score;
		ADDRESS_LIST continue_count;
		ADDRESS_LIST p_player_state;
		ADDRESS_LIST p_bomb_state;
	} th15_addr_list;

	// th15 v1.00b address list
	const TH15_ADDR_LIST TH15_ADDR_LIST_V100B = {
		{ 0x004E7410 },
		{ 0x004E7404 },
		{ 0x004E740C },
		{ 0x004E7414 },
		{ 0x004E9BB8, 0x16220 },
		{ 0x004E9A68, 0x24 }
	};
private:
	HANDLE process;

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
