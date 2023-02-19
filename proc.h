#pragma once

#include <vector>
#include <windows.h>
#include <TlHelp32.h>

DWORD GetProcessId(const WCHAR* procName);

uintptr_t GetmoduleAddress(DWORD procId, const WCHAR* modName);

uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);
