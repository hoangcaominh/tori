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

	// Resets all counters of a game handle
	void reset() override;
	// Detects whether the game is being played
	bool is_ingame() override;

	// Return the value of the current difficulty.
	// Easy = 0, Normal = 1, Hard = 2, Lunatic = 3, Extra = 4.
	uint8_t get_difficulty();
	// Return the value of the current character.
	// Reimu = 0, Marisa = 1.
	uint8_t get_character();
	// Return the value of the current beast shot
	// Wolf = 0, Otter = 1, Eagle = 2.
	uint8_t get_beastshot();
	uint64_t get_score();
	uint16_t get_miss_count();
	uint16_t get_bomb_count();
	Hypers get_hyper_count();
private:
	// address list for th17
	struct TH17_ADDR_LIST
	{
		ADDRESS_LIST p_menu;
		ADDRESS_LIST difficulty;
		ADDRESS_LIST character;
		ADDRESS_LIST beastshot;
		ADDRESS_LIST score;
		ADDRESS_LIST continue_count;
		ADDRESS_LIST p_player_state;
		ADDRESS_LIST p_bomb_state;
		ADDRESS_LIST hyper_type;
		ADDRESS_LIST hyper_state;
	} th17_addr_list;

	// th17 v1.00b address list
	const TH17_ADDR_LIST TH17_ADDR_LIST_V100B = {
		{ 0x004B77F0 },
		{ 0x004B5A00 },
		{ 0x004B59F4 },
		{ 0x004B59F8 },
		{ 0x004B59FC },
		{ 0x004B5A04 },
		{ 0x004B77D0, 0x18DB0 },
		{ 0x004B7688, 0x30 },
		{ 0x004B5ABC },
		{ 0x004B5AC4 }
	};
private:
	HANDLE process;

	// menu pointer, used for detecting in-game state
	uint32_t p_menu = 0;
	// get_difficulty
	uint8_t difficulty = 0;
	// get shottype
	uint8_t character = 0, beastshot = 0;
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
