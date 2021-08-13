#include "th128.h"

TH128::TH128(HANDLE process) : process(process)
{
}

void TH128::reset()
{

}

const char* TH128::get_difficulty()
{
	ReadProcessMemory(process, (void*)0x004B4D0C, (void*)&difficulty, sizeof(difficulty), 0);
	return arr_difficulty[difficulty];
}

const char* TH128::get_route()
{
	ReadProcessMemory(process, (void*)0x004B4D14, (void*)&stage, sizeof(stage), 0);
	return arr_route[stage];
}

uint16_t TH128::get_miss_count()
{
	ReadProcessMemory(process, (void*)0x004B8A80, (void*)&p_player_state, sizeof(p_player_state), 0);
	ReadProcessMemory(process, (void*)(p_player_state + 0xF78), (void*)&player_state, sizeof(player_state), 0);

	// if player_state changes form 4 to 2, increase miss_count by 1
	if (player_state == 2 && player_state != _player_state)
		miss_count++;
	_player_state = player_state;

	return miss_count;
}

uint16_t TH128::get_bomb_count()
{
	ReadProcessMemory(process, (void*)0x004B892C, (void*)&p_bomb_state, sizeof(p_bomb_state), 0);
	ReadProcessMemory(process, (void*)(p_bomb_state + 0x40), (void*)&bomb_state, sizeof(bomb_state), 0);
	
	// if bomb_state changes to 1, increase bomb_count by 1
	if (bomb_state && bomb_state != _bomb_state)
		bomb_count++;
	_bomb_state = bomb_state;

	return bomb_count;
}

uint64_t TH128::get_score()
{
	ReadProcessMemory(process, (void*)0x004B4CC4, (void*)&score, sizeof(uint32_t), 0);
	return score * 10;
}

TH128::Medals TH128::get_medals()
{
	ReadProcessMemory(process, (void*)0x004B8934, (void*)&p_medal_state, sizeof(p_medal_state), 0);
	ReadProcessMemory(process, (void*)(p_medal_state + 0x7C), (void*)&medal_state, sizeof(medal_state), 0);

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
