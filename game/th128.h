#pragma once

#include "thxx.h"

class TH128 : public THXX
{
public:
	enum class VERSION
	{
		V100A
	};

	TH128(HANDLE, VERSION);

	void reset() override;

	struct Medals
	{
		uint16_t bronze, silver, gold;
	};

	// Return the value of the current difficulty.
	// Easy = 0, Normal = 1, Hard = 2, Lunatic = 3, Extra = 4.
	uint8_t get_difficulty();
	// Return the value of the current stage.
	// A1-1 = 1, A1-2 = 2, A1-3 = 3, A2-2 = 4, A2-3 = 5,
	// B1-1 = 5, B1-2 = 7, B1-3 = 8, B2-2 = 9, B2-3 = 10,
	// C1-1 = 11, C1-2 = 12, C1-3 = 13, C2-2 = 14, C2-3 = 15,
	// Ex = 16.
	uint8_t get_stage();
	uint64_t get_score();
	uint16_t get_miss_count();
	uint16_t get_bomb_count();
	Medals get_medals();
private:
	HANDLE process;

	// address list for th128
	struct TH128_ADDR_LIST
	{
		ADDRESS_LIST difficulty;
		ADDRESS_LIST stage;
		ADDRESS_LIST score;
		ADDRESS_LIST continue_count;
		ADDRESS_LIST p_player_state;
		ADDRESS_LIST p_bomb_state;
		ADDRESS_LIST p_medal_state;
	} th128_addr_list;
	
	// get_difficulty
	uint8_t difficulty = 0;
	// get stage/route
	uint8_t stage = 0;
	// get miss count
	uint8_t player_state = 0, _player_state = 0;
	uint16_t miss_count = 0;
	// get bomb count
	uint8_t bomb_state = 0, _bomb_state = 0;
	uint16_t bomb_count = 0;
	// get score
	uint32_t score = 0;
	uint8_t continue_count = 0;
	// get medals
	uint8_t medal_state = 0, _medal_state = 0;
	Medals medals = { 0, 0, 0 };
};
