#pragma once
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include "proc.h"
#include "infiniteAmmo.h"
#include "BombInfinite.h"
#include "Armor.h"
#include "health.h"

class JumpInfinite
{
public:
	static int jump() {


		int offset1 = 0x0017E0A8;

		std::vector<unsigned int> offset2 = { 0x5C };

		DWORD PID = GetProcessId(L"ac_client.exe");

		if (PID == 0) {
			getchar();
			return 0;
		}

		uintptr_t moduleBase = GetmoduleAddress(PID, L"ac_client.exe");

		HANDLE hProcess = 0;

		hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, PID);

		uintptr_t dynamicptr = moduleBase + offset1;
		uintptr_t fullAdress = FindDMAAddy(hProcess, dynamicptr, offset2);

		DWORD ewExit = 0;

		while (ewExit == 0) {

			int newValue = 256;

			WriteProcessMemory(hProcess, (BYTE*)fullAdress, &newValue, sizeof(newValue), nullptr),
				Sleep(1);
		}

	}
};

