#include "game/th06.h"
#include "game/th07.h"
#include "game/th08.h"
#include "game/th09.h"
#include "game/th10.h"
#include "game/th11.h"
#include "game/th12.h"
#include "game/th128.h"
#include "game/th13.h"
#include "game/th14.h"
#include "game/th15.h"
#include "game/th16.h"
#include "game/th17.h"
#include "game/th18.h"

#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <Windows.h>
#include <TlHelp32.h>

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

// wchar_t* get_process_fullpath(DWORD);
std::pair<HANDLE, int> get_process();
bool is_process_alive(HANDLE);
