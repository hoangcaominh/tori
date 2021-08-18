#pragma once

#include "thxx.h"

class TH08 : public THXX
{
public:
	enum class VERSION
	{
		V100D
	};

	TH08(HANDLE, VERSION);

	void reset() override;
	const char* get_difficulty();
	const char* get_character();
	const char* get_stage();
	uint64_t get_score();
	uint16_t get_miss_count();
	uint16_t get_bomb_count();
	uint16_t get_spell_captured_count();
private:
	HANDLE process;

	// address list for th08
	struct TH08_ADDR_LIST
	{
		ADDRESS_LIST difficulty;
		ADDRESS_LIST character;
		ADDRESS_LIST stage;
		ADDRESS_LIST score;
		ADDRESS_LIST continue_count;
		ADDRESS_LIST miss_count;
		ADDRESS_LIST bomb_count;
		ADDRESS_LIST deathbomb_count;
		ADDRESS_LIST spell_captured_count;
	} th08_addr_list;

	// get_difficulty
	const char* arr_difficulty[5] = { "Easy", "Normal", "Hard", "Lunatic", "Extra" };
	uint8_t difficulty = 0;
	// get shottype
	const char* arr_character[12] = { "Reimu & Yukari", "Marisa & Alice", "Sakuya & Remilia", "Youmu & Yuyuko", "Reimu", "Yukari", "Marisa", "Alice", "Sakuya", "Remilia", "Youmu", "Yuyuko" };
	uint8_t character = 0;
	// get stage
	const char* arr_stage[9] = { "1", "2", "3", "4A", "4B", "5", "6A", "6B", "Ex" };
	uint8_t stage = 0;
	// get score
	uint32_t score = 0;
	uint8_t continue_count = 0;
	// get miss count
	uint16_t miss_count = 0;
	// get bomb count
	uint16_t bomb_count = 0, deathbomb_count = 0;
	// get spell captured count
	uint16_t spell_captured_count = 0;
};
