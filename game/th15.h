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
	const char* get_difficulty();
	const char* get_character();
	uint64_t get_score();
	uint16_t get_miss_count();
	uint16_t get_bomb_count();
private:
	HANDLE process;

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

	// get_difficulty
	const char* arr_difficulty[5] = { "Easy", "Normal", "Hard", "Lunatic", "Extra" };
	uint8_t difficulty = 0;
	// get shottype
	const char* arr_character[4] = { "Reimu", "Marisa", "Sanae", "Reisen" };
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
