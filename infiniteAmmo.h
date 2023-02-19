#pragma once
class infiniteAmmo
{
public:
    static int InfiniteAmmo() {

        int ammoOffset = 0x17E0A8;
        std::vector<unsigned int> ammoOffsets = { 0x140 };
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

        uintptr_t dynamicPtrBaseAddr = moduleBase + ammoOffset;
        uintptr_t ammoAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, ammoOffsets);


        DWORD dwExit = 0;

        int newAmmo = 99999;
        WriteProcessMemory(hProcess, (BYTE*)ammoAddr, &newAmmo, sizeof(newAmmo), nullptr);
        Sleep(10);

    }
};

