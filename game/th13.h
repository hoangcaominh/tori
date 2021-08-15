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

	void reset() override;
	const char* get_difficulty();
	const char* get_character();
	uint16_t get_miss_count();
	uint16_t get_bomb_count();
	uint16_t get_trance_count();
	uint64_t get_score();
private:
	HANDLE process;

	// address list for th13
	struct TH13_ADDR_LIST
	{
		ADDRESS_LIST difficulty;
		ADDRESS_LIST character;
		ADDRESS_LIST score;
		ADDRESS_LIST continue_count;
		ADDRESS_LIST p_player_state;
		ADDRESS_LIST p_bomb_state;
		ADDRESS_LIST trance_state;
	} th13_addr_list;

	// get_difficulty
	const char* arr_difficulty[5] = { "Easy", "Normal", "Hard", "Lunatic", "Extra" };
	uint16_t difficulty = 0;
	// get shottype
	const char* arr_character[4] = { "Reimu", "Marisa", "Sanae", "Youmu" };
	uint8_t character = 0;
	// get miss count
	uint8_t player_state = 0, _player_state = 0;
	uint16_t miss_count = 0;
	// get bomb count
	uint8_t bomb_state = 0, _bomb_state = 0;
	uint16_t bomb_count = 0;
	// get trance count
	uint8_t trance_state = 0, _trance_state = 0;
	uint16_t trance_count = 0;
	// get score
	uint64_t score = 0;
	uint8_t continue_count = 0;
};
