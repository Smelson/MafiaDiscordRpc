#pragma once
#include <Windows.h>
#include <vector>
#include <chrono>

namespace Helpers
{
	void Log(const char* logText);
	DWORD GetPointerAddress(DWORD baseAddress, std::vector<DWORD> offsets);
	void InstallJmpHook(DWORD hookAddress, DWORD myFunction);
	void InstallCallHook(DWORD hookAddress, DWORD myFunction);
	void Nop(DWORD hookAddress);
}