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
	const char* get_difficulty();
	const char* get_character();
	const char* get_subshot();
	uint64_t get_score();
	uint16_t get_miss_count();
	uint16_t get_bomb_count();
	uint16_t get_border_break_count();
private:
	HANDLE process;

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

	// get_difficulty
	const char* arr_difficulty[6] = { "Easy", "Normal", "Hard", "Lunatic", "Extra", "Phantasm" };
	uint8_t difficulty = 0;
	// get shottype
	const char* arr_character[3] = { "Reimu", "Marisa", "Sakuya" };
	const char* arr_subshot[2] = { "A", "B" };
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
