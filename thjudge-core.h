#pragma once

#include <string>
#include <Windows.h>

std::wstring GAME_LIST[] = {
	L"",
	L"",
	L"",
	L"",
	L"",
	L"東方紅魔郷.exe",
	L"th07.exe",
	L"th08.exe",
	L"th09.exe",
	L"th10.exe",
	L"th11.exe",
	L"th12.exe",
	L"th128.exe",
	L"th13.exe",
	L"th14.exe",
	L"th15.exe",
	L"th16.exe",
	L"th17.exe",
	L"th18.exe"
};
const int GAME_COUNT = sizeof(GAME_LIST) / sizeof(std::wstring);

struct GAME_PROCESS
{
	HANDLE process;
	int game;
};

// wchar_t* get_process_fullpath(DWORD);
GAME_PROCESS get_process();
bool is_process_alive(HANDLE);
