#pragma once

#include "thxx.h"

class TH16 : public THXX
{
public:
	enum class VERSION
	{
		V100A
	};

	TH16(HANDLE, VERSION);

	void reset() override;
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
	HANDLE process;

	// address list for th16
	struct TH16_ADDR_LIST
	{
		ADDRESS_LIST difficulty;
		ADDRESS_LIST character;
		ADDRESS_LIST season;
		ADDRESS_LIST score;
		ADDRESS_LIST continue_count;
		ADDRESS_LIST p_player_state;
		ADDRESS_LIST p_bomb_state;
		ADDRESS_LIST p_release_state;
	} th16_addr_list;

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
