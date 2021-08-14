#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <cstdint>
#include <Windows.h>

typedef std::vector<uint32_t> ADDRESS_LIST;

bool read_memory_32(HANDLE, ADDRESS_LIST, void*, size_t);

// The base class for all game classes
class THXX
{
public:
	virtual void reset() = 0;
};
