#include "th07.h"

TH07::TH07(HANDLE process, VERSION version) : process(process)
{
	switch (version)
	{
	case TH07::VERSION::V100B:
		th07_addr_list = TH07_ADDR_LIST_V100B;
		break;
	}
}

void TH07::reset()
{

}

uint8_t TH07::get_difficulty()
{
	if (!read_memory_32(process, th07_addr_list.difficulty, (void*)&difficulty, sizeof(difficulty)))
		fprintf(stderr, "Failed to read memory of difficulty.\n");
	return difficulty;
}

uint8_t TH07::get_character()
{
	if (!read_memory_32(process, th07_addr_list.character, (void*)&character, sizeof(character)))
		fprintf(stderr, "Failed to read memory of character.\n");
	return character;
}

uint8_t TH07::get_subshot()
{
	if (!read_memory_32(process, th07_addr_list.subshot, (void*)&subshot, sizeof(subshot)))
		fprintf(stderr, "Failed to read memory of subshot.\n");
	return subshot;
}

uint64_t TH07::get_score()
{
	if (!read_memory_32(process, th07_addr_list.score, (void*)&score, sizeof(score)))
		fprintf(stderr, "Failed to read memory of score.\n");
	if (!read_memory_32(process, th07_addr_list.continue_count, (void*)&continue_count, sizeof(continue_count)))
		fprintf(stderr, "Failed to read memory of continue.\n");
	return (uint64_t)score * 10 + continue_count;
}

uint16_t TH07::get_miss_count()
{
	if (!read_memory_32(process, th07_addr_list.miss_count, (void*)&miss_count, sizeof(miss_count)))
		fprintf(stderr, "Failed to read memory of miss count.\n");
	return (uint16_t)miss_count;
}

uint16_t TH07::get_bomb_count()
{
	if (!read_memory_32(process, th07_addr_list.bomb_count, (void*)&bomb_count, sizeof(bomb_count)))
		fprintf(stderr, "Failed to read memory of bomb count.\n");
	return (uint16_t)bomb_count;
}

uint16_t TH07::get_border_break_count()
{
	if (!read_memory_32(process, th07_addr_list.cherryp_state, (void*)&cherryp_state, sizeof(cherryp_state)))
		fprintf(stderr, "Failed to read memory of cherry+ state.\n");
	if (!read_memory_32(process, th07_addr_list.border_state, (void*)&border_state, sizeof(border_state)))
		fprintf(stderr, "Failed to read memory of border state.\n");

	// if cherry+ state is 0 and border state is 1, increment border break
	if (cherryp_state != _cherryp_state && cherryp_state == 0 && border_state == 1)
		border_break_count++;
	_cherryp_state = cherryp_state;

	return border_break_count;
}
