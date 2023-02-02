#pragma once
#include <Windows.h>
#include <vector>

DWORD GetPointerAddress(DWORD baseAddress, std::vector<DWORD> offsets);
