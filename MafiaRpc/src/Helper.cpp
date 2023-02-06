#include "Helper.hpp"

DWORD Helpers::GetPointerAddress(DWORD baseAddress, std::vector<DWORD> offsets)
{
	DWORD addr = baseAddress;
	for (int i = 0; i < offsets.size(); i++)
	{
		addr = *(DWORD*)addr;
		addr += offsets[i];
	}
	return addr;
}

void Helpers::InstallJmpHook(DWORD hookAddress, DWORD myFunction)
{
	DWORD protect[2];
	VirtualProtect((void*)hookAddress, 5, PAGE_EXECUTE_READWRITE, &protect[0]);
	*(BYTE*)hookAddress = 0xE9;
	*(DWORD*)(hookAddress + 1) = (myFunction - hookAddress) - 5;
	VirtualProtect((void*)hookAddress, 5, protect[0], &protect[1]);
}

void Helpers::InstallCallHook(DWORD hookAddress, DWORD myFunction)
{
	DWORD protect[2];
	VirtualProtect((void*)hookAddress, 5, PAGE_EXECUTE_READWRITE, &protect[0]);
	*(BYTE*)hookAddress = 0xE8;
	*(DWORD*)(hookAddress + 1) = (myFunction - hookAddress) - 5;
	VirtualProtect((void*)hookAddress, 5, protect[0], &protect[1]);
}