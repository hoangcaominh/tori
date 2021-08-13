#pragma once

#include <cstdint>
#include <Windows.h>

// The base class for all game classes
class THXX
{
public:
	virtual void read_memory() = 0;
};
