#include "Helpers.hpp"

void Helpers::Log(const char* logText, int color, int GAME_VERSION)
{
	if (GAME_VERSION == 384)
	{
		static DWORD missionOffset = 0x658330;
		static DWORD func = 0x54BE80 ;
		_asm
		{
			push color
			push logText
			mov ecx, missionOffset
			call func	
		}
	}

	if (GAME_VERSION == 395)
	{
		static DWORD missionOffset = 0x6BF980;
		static DWORD func = 0x5F9D50;
		_asm
		{
			push color
			push logText
			mov ecx, missionOffset
			call func	
		}
	}
}

DWORD Helpers::GetPointerAddress(DWORD baseAddress, std::vector<DWORD> offsets)
{
	DWORD addr = baseAddress;
	for (size_t i = 0; i < offsets.size(); i++)
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

void Helpers::Nop(DWORD hookAddress, int count)
{
	DWORD tempAddress = hookAddress;
	DWORD protect[2];
	VirtualProtect((void*)hookAddress, count, PAGE_EXECUTE_READWRITE, &protect[0]);
	for (int i = 0; i < count; tempAddress++, i++)
	{
		*(BYTE*)tempAddress = 0x90;
	}
	VirtualProtect((void*)hookAddress, count, protect[0], &protect[1]);
}