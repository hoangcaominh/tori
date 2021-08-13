#include "thxx.h"

bool read_memory_32(HANDLE process, ADDRESS_LIST address_list, void* buffer, size_t buffer_size)
{
	size_t length = address_list.size();
	uint32_t address = 0;
	BOOL success;

	for (size_t i = 0; i < length - 1; ++i)
	{
		success = ReadProcessMemory(process, (void*)(address + address_list[i]), &address, sizeof(address), 0);
		if (!success)
		{
			fprintf(stderr, "Failed to get memory from address %u\n", address + address_list[i]);
			return false;
		}
	}
	success = ReadProcessMemory(process, (void*)(address + address_list[length - 1]), buffer, buffer_size, 0);
	if (!success)
	{
		fprintf(stderr, "Failed to get memory from address %u\n", address + address_list[length - 1]);
		return false;
	}
	return true;
}