#include "th08.h"

namespace tori
{
	TH08::TH08(HANDLE process, VERSION version) : process(process)
	{
		switch (version)
		{
		case TH08::VERSION::V100D:
			th08_addr_list = TH08_ADDR_LIST_V100D;
			break;
		}
	}

	void TH08::reset()
	{

	}

	bool TH08::is_ingame()
	{
		if (!read_memory_32(process, th08_addr_list.menu, (void*)&menu, sizeof(menu)))
			fprintf(stderr, "Failed to read memory of menu.\n");
		return menu == 2;
	}

	uint8_t TH08::get_difficulty()
	{
		if (!read_memory_32(process, th08_addr_list.difficulty, (void*)&difficulty, sizeof(difficulty)))
			fprintf(stderr, "Failed to read memory of difficulty.\n");
		return difficulty;
	}

	uint8_t TH08::get_character()
	{
		if (!read_memory_32(process, th08_addr_list.character, (void*)&character, sizeof(character)))
			fprintf(stderr, "Failed to read memory of character.\n");
		return character;
	}

	uint8_t TH08::get_stage()
	{
		if (!read_memory_32(process, th08_addr_list.stage, (void*)&stage, sizeof(stage)))
			fprintf(stderr, "Failed to read memory of stage.\n");
		return stage;
	}

	uint64_t TH08::get_score()
	{
		if (!read_memory_32(process, th08_addr_list.score, (void*)&score, sizeof(score)))
			fprintf(stderr, "Failed to read memory of score.\n");
		if (!read_memory_32(process, th08_addr_list.continue_count, (void*)&continue_count, sizeof(continue_count)))
			fprintf(stderr, "Failed to read memory of continue.\n");
		// continue can exceed 9 in th08
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
}
