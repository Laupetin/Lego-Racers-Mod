#include "Windowed.h"

#include <Windows.h>

#include "RacersOffset.h"
#include "Patch/Patch.h"

namespace windowed
{
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

    return true;
}
