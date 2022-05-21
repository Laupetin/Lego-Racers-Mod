#include "PatchWindowed.h"

#include <Windows.h>

#include "RacersOffset.h"
#include "patch/Patch.h"

namespace windowed
{
    HWND __stdcall CreateWindowExHk(const DWORD dwExStyle, const LPCSTR lpClassName, const LPCSTR lpWindowName, [[maybe_unused]] DWORD dwStyle, [[maybe_unused]] int x, [[maybe_unused]] int y,
                                    [[maybe_unused]] int nWidth, [[maybe_unused]] int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance,
                                    LPVOID lpParam)
    {
        return CreateWindowExA(dwExStyle, lpClassName, lpWindowName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, hWndParent, hMenu, hInstance, lpParam);
    }

    void DoPatch()
    {
        Patch::Call(Offset().Racers01(0x489603), Patch::GetP(CreateWindowExHk), 6);
    }
}
