#pragma once

#include "thxx.h"

class TH17 : public THXX
{
public:
	enum class VERSION
	{
		V100B
	};

	TH17(HANDLE, VERSION);

	struct Hypers
	{
		uint16_t wolf, otter, eagle, neutral, break_count;
	};
	
	void reset() override;
	const char* get_difficulty();
	const char* get_character();
	const char* get_subshot();
	uint64_t get_score();
	uint16_t get_miss_count();
	uint16_t get_bomb_count();
	Hypers get_hyper_count();
private:
	HANDLE process;

	// address list for th17
	struct TH17_ADDR_LIST
	{
		ADDRESS_LIST difficulty;
		ADDRESS_LIST character;
		ADDRESS_LIST subshot;
		ADDRESS_LIST score;
		ADDRESS_LIST continue_count;
		ADDRESS_LIST p_player_state;
		ADDRESS_LIST p_bomb_state;
		ADDRESS_LIST hyper_type;
		ADDRESS_LIST hyper_state;
	} th17_addr_list;

	// get_difficulty
	const char* arr_difficulty[5] = { "Easy", "Normal", "Hard", "Lunatic", "Extra" };
	uint8_t difficulty = 0;
	// get shottype
	const char* arr_character[3] = { "Reimu", "Marisa", "Sakuya" };
	const char* arr_subshot[2] = { "A", "B" };
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
	// get hypers
	uint8_t hyper_type = 0;
	uint16_t hyper_state = 0;
	bool hyper_active = false, _hyper_active = false;
	bool hyper_break = false, _hyper_break = false;
	Hypers hypers = { 0, 0, 0, 0, 0 };
};
