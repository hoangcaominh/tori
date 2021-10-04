#pragma once

#include <Windows.h>

// wchar_t* get_process_fullpath(DWORD);

// get process from a specified game
HANDLE get_process(const wchar_t*);
bool is_process_alive(HANDLE);
