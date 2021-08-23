#pragma once

#include <string>
#include <Windows.h>

struct GAME_PROCESS
{
	HANDLE process;
	int index;
};

// wchar_t* get_process_fullpath(DWORD);

// get process from a list of game's process name
GAME_PROCESS get_process(std::wstring*, size_t);
bool is_process_alive(HANDLE);
