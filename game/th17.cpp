#include "th17.h"

TH17::TH17(HANDLE process, VERSION version) : process(process)
{
	switch (version)
	{
	case TH17::VERSION::V100B:
		th17_addr_list = {
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
		break;
	}
}

void TH17::reset()
{

}

uint8_t TH17::get_difficulty()
{
	if (!read_memory_32(process, th17_addr_list.difficulty, (void*)&difficulty, sizeof(difficulty)))
		fprintf(stderr, "Failed to read memory of difficulty.\n");
	return difficulty;
}

uint8_t TH17::get_character()
{
	if (!read_memory_32(process, th17_addr_list.character, (void*)&character, sizeof(character)))
		fprintf(stderr, "Failed to read memory of character.\n");
	return character;
}

uint8_t TH17::get_beastshot()
{
	if (!read_memory_32(process, th17_addr_list.beastshot, (void*)&beastshot, sizeof(beastshot)))
		fprintf(stderr, "Failed to read memory of beast shot.\n");
	return beastshot;
}

uint64_t TH17::get_score()
{
	if (!read_memory_32(process, th17_addr_list.score, (void*)&score, sizeof(score)))
		fprintf(stderr, "Failed to read memory of score.\n");
	if (!read_memory_32(process, th17_addr_list.continue_count, (void*)&continue_count, sizeof(continue_count)))
		fprintf(stderr, "Failed to read memory of continue.\n");
	return (uint64_t)score * 10 + continue_count;
}

uint16_t TH17::get_miss_count()
{
	if (!read_memory_32(process, th17_addr_list.p_player_state, (void*)&player_state, sizeof(player_state)))
		fprintf(stderr, "Failed to read memory of player state.\n");

	// if player_state changes form 4 to 2, increase miss_count by 1
	if (player_state == 2 && player_state != _player_state)
		miss_count++;
	_player_state = player_state;

	return miss_count;
}

uint16_t TH17::get_bomb_count()
{
	if (!read_memory_32(process, th17_addr_list.p_bomb_state, (void*)&bomb_state, sizeof(bomb_state)))
		fprintf(stderr, "Failed to read memory of bomb state.\n");

	// if bomb_state changes to 1, increase bomb_count by 1
	if (bomb_state && bomb_state != _bomb_state)
		bomb_count++;
	_bomb_state = bomb_state;

	return bomb_count;
}

TH17::Hypers TH17::get_hyper_count()
{
	if (!read_memory_32(process, th17_addr_list.hyper_type, (void*)&hyper_type, sizeof(hyper_type)))
		fprintf(stderr, "Failed to read memory of hyper type.\n");
	if (!read_memory_32(process, th17_addr_list.hyper_state, (void*)&hyper_state, sizeof(hyper_state)))
		fprintf(stderr, "Failed to read memory of bomb state.\n");

	hyper_active = hyper_state & (1 << 1);
	hyper_break = hyper_state & (1 << 2);
	
	// if bit 2 of hyper state is set, the player is in hyper mode
	// if bit 3 of hyper state is set, the player breaks the hyper
	if (hyper_active && hyper_active ^ _hyper_active)
		if (hyper_type == 1)
			hypers.wolf++;
		else if (hyper_type == 2)
			hypers.otter++;
		else if (hyper_type == 3)
			hypers.eagle++;
		else if (hyper_type == 4)
			hypers.neutral++;
	if (hyper_break && hyper_break ^ _hyper_break)
		hypers.break_count++;

	_hyper_active = hyper_active;
	_hyper_break = hyper_break;

	return hypers;
}
