#include "thjudge-core.h"

/*
wchar_t* get_process_fullpath(DWORD proc_id)
{
	wchar_t* fullpath = L"";

	HANDLE h_module_snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32 | TH32CS_SNAPMODULE, proc_id);
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

bool is_process_alive(HANDLE process)
{
	DWORD proc_status;
	if (!GetExitCodeProcess(process, &proc_status))
	{
		fprintf(stderr, "Failed to get process' exit code. Error code: %d", GetLastError());
		return false;
	}
	return proc_status == STILL_ACTIVE;
}
