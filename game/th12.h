#pragma once

#include "thxx.h"

class TH12 : public THXX
{
public:
	enum class VERSION
	{
		V100B
	};

	TH12(HANDLE, VERSION);

	void reset() override;

	struct UFOs
	{
		uint16_t red, blue, green, rainbow;
	};

	// Return the value of the current difficulty.
	// Easy = 0, Normal = 1, Hard = 2, Lunatic = 3, Extra = 4.
	uint8_t get_difficulty();
	// Return the value of the current character.
	// Reimu = 0, Marisa = 1, Sanae = 2.
	uint8_t get_character();
	// Return the value of the current subshot
	// A = 0, B = 1.
	uint8_t get_subshot();
	uint64_t get_score();
	uint16_t get_miss_count();
	uint16_t get_bomb_count();
	UFOs get_ufo_count();
private:
	HANDLE process;

	// address list for th12
	struct TH12_ADDR_LIST
	{
		ADDRESS_LIST difficulty;
		ADDRESS_LIST character;
		ADDRESS_LIST subshot;
		ADDRESS_LIST score;
		ADDRESS_LIST continue_count;
		ADDRESS_LIST p_player_state;
		ADDRESS_LIST p_bomb_state;
		ADDRESS_LIST vaults;
		ADDRESS_LIST vault_count;
	} th12_addr_list;

	// get_difficulty
	uint8_t difficulty = 0;
	// get shottype
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
	// get UFO count
	uint32_t vaults[3], vault_count = 0, _vault_count = 0;
	UFOs ufos = { 0, 0, 0 };
};
