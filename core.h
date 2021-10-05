#pragma once

#include <Windows.h>

// verify executable version using sha256 hash
bool verify_version(HANDLE, const char*);

// get process from a specified game
HANDLE get_process(const wchar_t*);

// check process status
bool is_process_alive(HANDLE);
