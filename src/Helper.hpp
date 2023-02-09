#pragma once
#include <Windows.h>
#include <vector>

namespace Helpers
{
    DWORD GetPointerAddress(DWORD baseAddress, std::vector<DWORD> offsets);
    void InstallJmpHook(DWORD hookAddress, DWORD myFunction);
    void InstallCallHook(DWORD hookAddress, DWORD myFunction);
}