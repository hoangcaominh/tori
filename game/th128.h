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

	const char* get_difficulty();
	const char* get_route();
	uint16_t get_miss_count();
	uint16_t get_bomb_count();
	uint64_t get_score();
	Medals get_medals();
private:
	HANDLE process;

	// address list for 
	struct TH128_ADDR_LIST
	{
		ADDRESS_LIST difficulty;
		ADDRESS_LIST stage;
		ADDRESS_LIST p_player_state;
		ADDRESS_LIST p_bomb_state;
		ADDRESS_LIST score;
		ADDRESS_LIST p_medal_state;
	} th128_addr_list;
	
	// get_difficulty
	const char* arr_difficulty[5] = { "Easy", "Normal", "Hard", "Lunatic", "Extra" };
	uint16_t difficulty = 0;
	// get route
	const char* arr_route[17] = { "?", "A", "A1", "A1", "A2", "A2", "B", "B1", "B1", "B2", "B2", "C", "C1", "C1", "C2", "C2", "Ex" };
	uint16_t stage = 0;
	// get miss count
	uint8_t player_state = 0, _player_state = 0;
	uint16_t miss_count = 0;
	// get bomb count
	uint8_t bomb_state = 0, _bomb_state = 0;
	uint16_t bomb_count = 0;
	// get score
	uint64_t score = 0;
	// get medals
	uint8_t medal_state = 0, _medal_state = 0;
	Medals medals = { 0, 0, 0 };
};
