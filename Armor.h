#pragma once
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include "proc.h"
#include "infiniteAmmo.h"


class Armor
{
public:

	static int ArmorM() {

		int ArmorOffset = 0x0017E0A8;

		std::vector<unsigned int> BombOffsets = { 0xF0 };

		DWORD PID = GetProcessId(L"ac_client.exe");

		if (PID == 0) {
			std::cout << "Process Not Found" << std::endl;
			getchar();
			return 0;
		}

		intptr_t moduleBase = GetmoduleAddress(PID, L"ac_client.exe");

		HANDLE hProcess = 0;

		hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, PID);

		intptr_t dynamicPtr = moduleBase + ArmorOffset;
		intptr_t armorAdress = FindDMAAddy(hProcess, dynamicPtr, BombOffsets);

		DWORD dwExit = 0;

		int newArmor = 9999999;

	 WriteProcessMemory(hProcess, (BYTE*)armorAdress, &newArmor, sizeof(newArmor), nullptr),
			Sleep(10);
		
	}

};

