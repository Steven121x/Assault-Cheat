#include "stdafx.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include "proc.h"
#include "infiniteAmmo.h"
#include "BombInfinite.h"
#include "Armor.h"
#include "health.h"
#include <future>
//
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#define DIRECTINPUT_VERSION 0x0800
#include "main.h"
#include <PointX/JumpInfinite.h>

bool WindowsShowCheck = true;

int main(int, char**)
{
    RECT desktop;
    GetWindowRect(GetDesktopWindow(), &desktop);
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, (LPCWSTR)AppClass, NULL };
    RegisterClassEx(&wc);
    hwnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_LAYERED, (LPCWSTR)AppClass, (LPCWSTR)AppName, WS_POPUP, (desktop.right / 2) - (WindowWidth / 2), (desktop.bottom / 2) - (WindowHeight / 2), WindowWidth, WindowHeight, 0, 0, wc.hInstance, 0);

    //SetLayeredWindowAttributes(hwnd, 0, 255, LWA_ALPHA);
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, ULW_COLORKEY);

    if (CreateDeviceD3D(hwnd) < 0)
    {
        CleanupDeviceD3D();
        UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    DefaultFont = io.Fonts->AddFontFromFileTTF(skCrypt("C:\\Windows\\Fonts\\seguihis.ttf"), 24.0f, NULL, io.Fonts->GetGlyphRangesCyrillic());
   // ImGui::NovaColor();
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    static bool open = true;
    DWORD dwFlag = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }
        if (!open) ExitProcess(EXIT_SUCCESS);
        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowSize(ImVec2(WindowWidth, WindowHeight), ImGuiCond_Once);
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
        {
            ImGui::Begin(AppName, &open, dwFlag);
            {
                if (GetAsyncKeyState(VK_F3)) {

                    ShowWindow(hwnd, SW_HIDE);
                }
                if (GetAsyncKeyState(VK_F4)) {
                    ShowWindow(hwnd, SW_SHOW);
                }
               
                ImGui::LabelText("-----2023 & 2024-----", "Options");
                ImGui::SetCursorPos(ImVec2(20, 81));
                if (ImGui::Button("Ammo Infinite", ImVec2(125,45))) {
                    infiniteAmmo::InfiniteAmmo();
                }

                ImGui::SetCursorPos(ImVec2(20, 150));
                if (ImGui::Button("Bomb Infinite", ImVec2(125, 45))) {
                    std::async(std::launch::async, BombInfinite::Infinitebomb);
                }

                ImGui::SetCursorPos(ImVec2(20, 220));
                if (ImGui::Button("Armor Infinite", ImVec2(125, 45))) {

                    Armor::ArmorM();
                }

                ImGui::SetCursorPos(ImVec2(20, 291));
                if (ImGui::Button("Health Infinite", ImVec2(125, 45))) {
                    std::async(std::launch::async, health::healthI);
                }   

                ImGui::SetCursorPos(ImVec2(20, 360));
                if (ImGui::Button("Jump Infinite", ImVec2(125, 45))) {
                    std::thread t1(JumpInfinite::jump);
                    t1.detach();
                }
            }
        }
        ImGui::End();

        ImGui::EndFrame();

        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) ResetDevice();
    }

    void ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    CleanupDeviceD3D();
    DestroyWindow(hwnd);
    UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}