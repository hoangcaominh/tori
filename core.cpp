#include "core.h"

#include <cstdio>
#include <TlHelp32.h>
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
HANDLE get_process(const wchar_t* process_name)
{
	HANDLE h_process_snap, process;

	// Take a snapshot of all processes in the system.
	h_process_snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (h_process_snap == INVALID_HANDLE_VALUE)
	{
		// Failed to snap process
		fprintf(stderr, "Error: Invalid handle value for process snapping!\n");
		return NULL;
	}

	PROCESSENTRY32 pe32;

	// Set the size of the structure before using it.
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// Now walk the snapshot of processes
	if (Process32First(h_process_snap, &pe32))
		do
		{
			if (wcscmp(pe32.szExeFile, process_name))
				continue;

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
			// Open game process
			process = OpenProcess(PROCESS_ALL_ACCESS, false, pe32.th32ProcessID);

			if (!process)
			{
				// Failed to open process
				fprintf(stderr, "Failed to open process. Error code: %d\n", GetLastError());
				break;
			}

			// Found game, exit loop
			return process;
		} while (Process32Next(h_process_snap, &pe32));

	CloseHandle(h_process_snap);
	return NULL;
}

bool is_process_alive(HANDLE process)
{
	DWORD proc_status;
	if (!GetExitCodeProcess(process, &proc_status))
	{
		fprintf(stderr, "Failed to get process exit code. Error code: %d\n", GetLastError());
		return false;
	}
	return proc_status == STILL_ACTIVE;
}
