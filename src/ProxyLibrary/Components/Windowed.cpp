#include "Windowed.h"

#include <iostream>
#include <Windows.h>

#include "RacersOffset.h"
#include "Offset.h"
#include "Patch.h"
#include "Game/LEGORacers2001.h"

namespace windowed
{
    static FunctionOffsetStdcall<LRESULT(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)> gameWindowProcFunc(Offset().Racers01(0x48A290));

    HWND __stdcall CreateWindowExHk(const DWORD dwExStyle, const LPCSTR lpClassName, const LPCSTR lpWindowName, [[maybe_unused]] DWORD dwStyle, [[maybe_unused]] int x, [[maybe_unused]] int y,
                                    [[maybe_unused]] int nWidth, [[maybe_unused]] int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance,
                                    LPVOID lpParam)
    {
        return CreateWindowExA(dwExStyle, lpClassName, lpWindowName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, hWndParent, hMenu, hInstance, lpParam);
    }

    LONG __stdcall ChangeDisplaySettingsHk(DEVMODEA* lpDevMode, DWORD dwFlags)
    {
        // Do nothing
        return DISP_CHANGE_SUCCESSFUL;
    }

    bool ShouldDrawCursor(HWND hwnd)
    {
        RECT rect{};
        POINT cursorPos{};
        GetClientRect(hwnd, &rect);

        POINT rectTopLeft{rect.left, rect.top};
        POINT rectBottomRight{rect.right, rect.bottom};
        ClientToScreen(hwnd, &rectTopLeft);
        ClientToScreen(hwnd, &rectBottomRight);

        GetCursorPos(&cursorPos);

        return cursorPos.x >= rectTopLeft.x && cursorPos.x < rectBottomRight.x
            && cursorPos.y >= rectTopLeft.y && cursorPos.y < rectBottomRight.y;
    }

    LRESULT __stdcall WindowProcFunc_Hk(HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam)
    {
        if (msg == WM_SETCURSOR)
        {
            const auto* windowSettings = reinterpret_cast<const WindowSettingsStruct*>(GetWindowLongPtrA(hWnd, 0));
            if (!windowSettings)
                return gameWindowProcFunc(hWnd, msg, wParam, lParam);

            if (ShouldDrawCursor(hWnd))
            {
                SetCursor(windowSettings->invisibleCursor);
                return TRUE;
            }

            return DefWindowProcA(hWnd, msg, wParam, lParam);
        }

        return gameWindowProcFunc(hWnd, msg, wParam, lParam);
    }
}

using namespace windowed;

ComponentWindowed::ComponentWindowed()
    : Component("Windowed")
{
}

bool ComponentWindowed::InstallInternal()
{
    Patch::Call(Offset().Racers01(0x489603), Patch::GetP(CreateWindowExHk), 6);

    // Make the game not change display settings for videos
    Patch::Call(Offset().Racers01(0x48AE60), Patch::GetP(ChangeDisplaySettingsHk), 6);
    Patch::Call(Offset().Racers01(0x48AEB4), Patch::GetP(ChangeDisplaySettingsHk), 6);

    // Make game target 32bit color
    Patch::Field<uint32_t>(Offset().Racers01(0x411786), 32);

    // Nop setting window flag 0x2 -> Does not minimize the game on tabbing out
    Patch::Nop(Offset().Racers01(0x489BA5), 3);

    Patch::Call(Offset().Racers01(0x48A668), Patch::GetP(ShouldDrawCursor));
    Patch::Field<void*>(Offset().Racers01(0x4894F3), Patch::GetP(WindowProcFunc_Hk));

    return true;
}
