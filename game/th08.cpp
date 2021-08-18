#include "th08.h"

TH08::TH08(HANDLE process, VERSION version) : process(process)
{
	switch (version)
	{
	case TH08::VERSION::V100D:
		th08_addr_list = {
			{ 0x0160F538 },
			{ 0x0164D0B1 },
			{ 0x004E4850 },
			{ 0x0160F510, 0x0 },
			{ 0x004D77DC },
			{ 0x0164CFA4 },
			{ 0x0164CFA8 },
			{ 0x0164CFAC },
			{ 0x0160F510, 0x1C }
		};
		break;
	}
}

void TH08::reset()
{

}

const char* TH08::get_difficulty()
{
	if (!read_memory_32(process, th08_addr_list.difficulty, (void*)&difficulty, sizeof(difficulty)))
		fprintf(stderr, "Failed to read memory of difficulty.\n");
	return arr_difficulty[difficulty];
}

const char* TH08::get_character()
{
	if (!read_memory_32(process, th08_addr_list.character, (void*)&character, sizeof(character)))
		fprintf(stderr, "Failed to read memory of character.\n");
	return arr_character[character];
}

const char* TH08::get_stage()
{
	if (!read_memory_32(process, th08_addr_list.stage, (void*)&stage, sizeof(stage)))
		fprintf(stderr, "Failed to read memory of stage.\n");
	return arr_stage[stage];
}

uint64_t TH08::get_score()
{
	if (!read_memory_32(process, th08_addr_list.score, (void*)&score, sizeof(score)))
		fprintf(stderr, "Failed to read memory of score.\n");
	if (!read_memory_32(process, th08_addr_list.continue_count, (void*)&continue_count, sizeof(continue_count)))
		fprintf(stderr, "Failed to read memory of continue.\n");
	return (uint64_t)score * 10 + ((continue_count > 9) ? 9 : continue_count);
}

uint16_t TH08::get_miss_count()
{
	if (!read_memory_32(process, th08_addr_list.miss_count, (void*)&miss_count, sizeof(miss_count)))
		fprintf(stderr, "Failed to read memory of miss count.\n");
	return miss_count;
}

uint16_t TH08::get_bomb_count()
{
	if (!read_memory_32(process, th08_addr_list.bomb_count, (void*)&bomb_count, sizeof(bomb_count)))
		fprintf(stderr, "Failed to read memory of bomb count.\n");
	if (!read_memory_32(process, th08_addr_list.deathbomb_count, (void*)&deathbomb_count, sizeof(deathbomb_count)))
		fprintf(stderr, "Failed to read memory of deathbomb count.\n");
	return bomb_count + deathbomb_count;
}

uint16_t TH08::get_spell_captured_count()
{
	if (!read_memory_32(process, th08_addr_list.spell_captured_count, (void*)&spell_captured_count, sizeof(spell_captured_count)))
		fprintf(stderr, "Failed to read memory of spell captured count.\n");
	return spell_captured_count;
}
