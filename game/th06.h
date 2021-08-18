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
	const char* get_difficulty();
	const char* get_character();
	const char* get_subshot();
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
	const char* arr_difficulty[5] = { "Easy", "Normal", "Hard", "Lunatic", "Extra" };
	uint16_t difficulty = 0;
	// get shottype
	const char* arr_character[2] = { "Reimu", "Marisa" };
	const char* arr_subshot[2] = { "A", "B" };
	uint8_t character = 0, subshot = 0;
	// get miss count
	uint8_t deathbomb_window = 0, _deathbomb_window = 0;
	uint16_t miss_count = 0;
	// get bomb count
	uint16_t bomb_count = 0;
	// get score
	uint32_t score = 0;
};
