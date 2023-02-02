#include "Helper.hpp"

DWORD GetPointerAddress(DWORD baseAddress, std::vector<DWORD> offsets)
{
	DWORD addr = baseAddress;
	for (int i = 0; i < offsets.size(); i++)
	{
		addr = *(DWORD*)addr;
		addr += offsets[i];
	}
	return addr;
}