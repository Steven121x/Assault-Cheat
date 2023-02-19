#pragma once
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include "proc.h"
#include "infiniteAmmo.h"

class BombInfinite
{
public:
    static int Infinitebomb() {

        int BombBase = 0x0017E0A8;
        std::vector<unsigned int> BombOffsets = { 0x144 };
        bool ammoActive = false;

        DWORD procId = GetProcessId(L"ac_client.exe");
        if (procId == 0) {
            std::cout << "Process not found" << std::endl;
            getchar();
            return 0;
        }

        uintptr_t moduleBase = GetmoduleAddress(procId, L"ac_client.exe");

        HANDLE hProcess = 0;
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
      
        uintptr_t dynamicPtrBaseAddr = moduleBase + BombBase;
        uintptr_t ammoAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, BombOffsets);


        DWORD dwExit = 0;

        int newBombs = 999;
        WriteProcessMemory(hProcess, (BYTE*)ammoAddr, &newBombs, sizeof(newBombs), nullptr);
        Sleep(10);

    }

};

