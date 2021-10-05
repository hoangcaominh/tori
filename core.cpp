#include "core.h"

#include <cstdio>
#include <TlHelp32.h>
#include <Psapi.h>
#include "sha256.h"

bool verify_version(HANDLE process, const char* sha256_hash_string)
{
	wchar_t path[MAX_PATH];
	FILE* file = nullptr;
	long filesize;
	unsigned char* buffer = 0;

	// get file path
	if (!GetModuleFileNameEx(process, NULL, path, MAX_PATH))
	{
		fprintf(stderr, "Failed to get executable path from process. Error: %d\n", GetLastError());
		return false;
	}

	// get file size
	_wfopen_s(&file, path, L"rb");
	if (!file)
	{
		fprintf(stderr, "Failed to open executable from process. Error: %d\n", GetLastError());
		return false;
	}
	fseek(file, 0, SEEK_END);
	filesize = ftell(file);
	fseek(file, 0, SEEK_SET);

	// read file content to buffer
	buffer = (unsigned char*)malloc(filesize + 1);
	if (!buffer)
	{
		fprintf(stderr, "Failed to allocate memory for buffer. Error: %d\n", GetLastError());
		return false;
	}
	fread(buffer, 1, filesize, file);
	fclose(file);
	buffer[filesize] = '\0';

	// sha256 hashing
	SHA256_CTX ctx;
	BYTE hash[32];
	char result[65];

	sha256_init(&ctx);
	sha256_update(&ctx, buffer, filesize);
	sha256_final(&ctx, hash);

	result[64] = '\0';
	for (int i = 0; i < 32; i++)
	{
		// sprintf(result + (i * 2), "%02x", hash[i]);
		snprintf(result + (i * 2), 32, "%02x", hash[i]);
	}

	// clear buffer memory
	free(buffer);
	printf("%s\n", result);

	return strcmp(result, sha256_hash_string) == 0;
}

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
			// Skip if process name doesn't match
			if (wcscmp(pe32.szExeFile, process_name))
				continue;

			// Open game process
			process = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_LIMITED_INFORMATION, false, pe32.th32ProcessID);

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
