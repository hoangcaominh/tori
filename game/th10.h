#pragma once

#include "thxx.h"

class TH10 : public THXX
{
public:
	enum class VERSION
	{
		V100A
	};

	TH10(HANDLE, VERSION);

	void reset() override;
	const char* get_difficulty();
	const char* get_character();
	const char* get_subshot();
	uint64_t get_score();
	uint16_t get_miss_count();
	uint16_t get_bomb_count();
private:
	HANDLE process;

	// address list for th10
	struct TH10_ADDR_LIST
	{
		ADDRESS_LIST difficulty;
		ADDRESS_LIST character;
		ADDRESS_LIST subshot;
		ADDRESS_LIST score;
		ADDRESS_LIST continue_count;
		ADDRESS_LIST p_player_state;
		ADDRESS_LIST p_bomb_state;
	} th10_addr_list;

	// get_difficulty
	const char* arr_difficulty[5] = { "Easy", "Normal", "Hard", "Lunatic", "Extra" };
	uint8_t difficulty = 0;
	// get shottype
	const char* arr_character[2] = { "Reimu", "Marisa" };
	const char* arr_subshot[3] = { "A", "B", "C" };
	uint8_t character = 0, subshot = 0;
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
