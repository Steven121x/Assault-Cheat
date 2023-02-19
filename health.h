#pragma once
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include "proc.h"
#include "infiniteAmmo.h"
#include "BombInfinite.h"
#include "Armor.h"

class health
{
public:
	static int healthI() {

		int offsetHealth = 0x0017E0A8;

		std::vector<unsigned int> healthOffsets = { 0xEC };

		DWORD PID = GetProcessId(L"ac_client.exe");

		if (PID == 0) {
			std::cout << "Process Not Found.";
			getchar();
			return 0;
		}

		uintptr_t ModuleBase = GetmoduleAddress(PID, L"ac_client.exe");

		HANDLE hProcess = 0;

		hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, PID);

		uintptr_t dynamicptr = ModuleBase + offsetHealth;

		uintptr_t healthAdress = FindDMAAddy(hProcess, dynamicptr, healthOffsets);

		DWORD dwExit = 0;

		int NewHealth = 200;

		WriteProcessMemory(hProcess, (BYTE*)healthAdress, &NewHealth, sizeof(NewHealth), nullptr),
			Sleep(10);

	}
};

