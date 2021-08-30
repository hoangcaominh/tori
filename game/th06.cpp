#include "th06.h"

TH06::TH06(HANDLE process, VERSION version) : process(process)
{
	switch (version)
	{
	case TH06::VERSION::V102H:
		th06_addr_list = TH06_ADDR_LIST_V102H;
		break;
	}
}

void TH06::reset()
{
	miss_count = 0;
}

bool TH06::is_ingame()
{
	if (!read_memory_32(process, th06_addr_list.menu_showing, (void*)&menu_showing, sizeof(menu_showing)))
		fprintf(stderr, "Failed to read memory of menu showing.\n");
	if (!read_memory_32(process, th06_addr_list.menu, (void*)&menu, sizeof(menu)))
		fprintf(stderr, "Failed to read memory of menu.\n");
	return menu_showing == 0 && !(menu == 16 || menu == 1 || menu == 2 || menu == 10);
}

uint8_t TH06::get_difficulty()
{
	if (!read_memory_32(process, th06_addr_list.difficulty, (void*)&difficulty, sizeof(difficulty)))
		fprintf(stderr, "Failed to read memory of difficulty.\n");
	return difficulty;
}

uint8_t TH06::get_character()
{
	if (!read_memory_32(process, th06_addr_list.character, (void*)&character, sizeof(character)))
		fprintf(stderr, "Failed to read memory of character.\n");
	return character;
}

uint8_t TH06::get_subshot()
{
	if (!read_memory_32(process, th06_addr_list.subshot, (void*)&subshot, sizeof(subshot)))
		fprintf(stderr, "Failed to read memory of subshot.\n");
	return subshot;
}

uint64_t TH06::get_score()
{
	if (!read_memory_32(process, th06_addr_list.score, (void*)&score, sizeof(score)))
		fprintf(stderr, "Failed to read memory of score.\n");
	return score;
}

uint16_t TH06::get_miss_count()
{
	if (!read_memory_32(process, th06_addr_list.deathbomb_window, (void*)&deathbomb_window, sizeof(deathbomb_window)))
		fprintf(stderr, "Failed to read memory of deathbomb window.\n");

	// for some reasons when the player dies the deathbomb window gets set to 0
	if (deathbomb_window == 0 && deathbomb_window != _deathbomb_window)
		miss_count++;
	_deathbomb_window = deathbomb_window;
	
	return miss_count;
}

uint16_t TH06::get_bomb_count()
{
	if (!read_memory_32(process, th06_addr_list.bomb_count, (void*)&bomb_count, sizeof(bomb_count)))
		fprintf(stderr, "Failed to read memory of bomb count.\n");
	return bomb_count;
}
