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

/*
wchar_t* get_process_fullpath(DWORD procid)
{
	wchar_t* fullpath = L"";

	HANDLE h_module_snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32 | TH32CS_SNAPMODULE, procid);
	if (h_module_snap == INVALID_HANDLE_VALUE)
	{
		fprintf(stderr, "Error: Invalid handle value for module snapping!\n");
		return nullptr;
	}

	MODULEENTRY32 me32;
	me32.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(h_module_snap, &me32))
		wcscpy_s(fullpath, wcslen(me32.szExePath) + 1, me32.szExePath);

	CloseHandle(h_module_snap);
	return fullpath;
}
*/
std::pair<HANDLE, int> get_process()
{
	HANDLE h_process_snap = NULL;
	int found_index = -1;

	// Take a snapshot of all processes in the system.
	h_process_snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (h_process_snap == INVALID_HANDLE_VALUE)
	{
		// Failed to snap process
		fprintf(stderr, "Error: Invalid handle value for process snapping!\n");
		return std::pair<HANDLE, int>(NULL, -1);
	}

	PROCESSENTRY32 pe32;

	// Set the size of the structure before using it.
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// Now walk the snapshot of processes
	if (Process32First(h_process_snap, &pe32))
		do
		{
			std::wstring proc_name = pe32.szExeFile;
			// lowercase all letters
			std::transform(proc_name.begin(), proc_name.end(), proc_name.begin(), ::tolower);
			std::wstring* found = std::find(GAME_LIST, GAME_LIST + GAME_COUNT, proc_name);

			if (found == GAME_LIST + GAME_COUNT)
				continue;

			found_index = found - GAME_LIST;
			/*
			wchar_t* path = get_process_fullpath(pe32.th32ProcessID);

			BOOL verify = VerifyVersion(fullpath, game);
			if (verify >= 0)
			{
				// Open game process
				gameProc = OpenProcess(PROCESS_ALL_ACCESS, false, pe32.th32ProcessID);

				if (!gameProc)
				{
					// Failed to open process
					CloseHandle(h_process_snap);
					return -2;
				}
			}
			*/

			// Found game, exit loop
			return std::make_pair(h_process_snap, found_index);
		} while (Process32Next(h_process_snap, &pe32));

	CloseHandle(h_process_snap);
	return std::pair<HANDLE, int>(NULL, GAME_COUNT);
}
