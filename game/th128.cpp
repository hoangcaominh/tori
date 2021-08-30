#include "th128.h"

TH128::TH128(HANDLE process, VERSION version) : process(process)
{
	switch (version)
	{
	case TH128::VERSION::V100A:
		th128_addr_list = TH128_ADDR_LIST_V100A;
		break;
	}
}

void TH128::reset()
{
	miss_count = 0;
	bomb_count = 0;
	medals = { 0, 0, 0 };
}

bool TH128::is_ingame()
{
	if (!read_memory_32(process, th128_addr_list.p_menu, (void*)&p_menu, sizeof(p_menu)))
		fprintf(stderr, "Failed to read memory of menu pointer.\n");
	return p_menu == NULL;
}

uint8_t TH128::get_difficulty()
{
	if (!read_memory_32(process, th128_addr_list.difficulty, (void*)&difficulty, sizeof(difficulty)))
		fprintf(stderr, "Failed to read memory of difficulty.\n");
	return difficulty;
}

uint8_t TH128::get_stage()
{
	if (!read_memory_32(process, th128_addr_list.stage, (void*)&stage, sizeof(stage)))
		fprintf(stderr, "Failed to read memory of stage.\n");
	return stage;
}

uint64_t TH128::get_score()
{
	if (!read_memory_32(process, th128_addr_list.score, (void*)&score, sizeof(score)))
		fprintf(stderr, "Failed to read memory of score.\n");
	if (!read_memory_32(process, th128_addr_list.continue_count, (void*)&continue_count, sizeof(continue_count)))
		fprintf(stderr, "Failed to read memory of continue.\n");
	return (uint64_t)score * 10 + continue_count;
}

uint16_t TH128::get_miss_count()
{
	if (!read_memory_32(process, th128_addr_list.p_player_state, (void*)&player_state, sizeof(player_state)))
		fprintf(stderr, "Failed to read memory of player state.\n");

	// if player_state changes form 4 to 2, increase miss_count by 1
	if (player_state == 2 && player_state != _player_state)
		miss_count++;
	_player_state = player_state;

	return miss_count;
}

uint16_t TH128::get_bomb_count()
{
	if (!read_memory_32(process, th128_addr_list.p_bomb_state, (void*)&bomb_state, sizeof(bomb_state)))
		fprintf(stderr, "Failed to read memory of bomb state.\n");
	
	// if bomb_state changes to 1, increase bomb_count by 1
	if (bomb_state && bomb_state != _bomb_state)
		bomb_count++;
	_bomb_state = bomb_state;

	return bomb_count;
}

TH128::Medals TH128::get_medals()
{
	if (!read_memory_32(process, th128_addr_list.p_medal_state, (void*)&medal_state, sizeof(medal_state)))
		fprintf(stderr, "Failed to read memory of medal state.\n");

	// if the MSB changes to 0 -> spell card ends, count medals
	if ((medal_state & 128) == 0 && (_medal_state & 128) > 0)
	{
		// 3rd bit is the gold medal check
		if ((medal_state & 4) > 0)
			medals.gold++;
		// 2nd bit is the silver medal check
		else if ((medal_state & 2) > 0)
			medals.silver++;
		else
			medals.bronze++;
	}
	_medal_state = medal_state;

	return medals;
}
