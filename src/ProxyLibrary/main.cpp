#include <Windows.h>
#include <string>

#include "Patch.h"

DWORD* __cdecl PostLoadEngineLibrary(DWORD* a1)
{
    MessageBoxA(NULL, "PostLoadEngine", "", 0);

    auto result = Patch::DoCall<DWORD*(DWORD*)>(0x4797E0)(a1);

    return result;
}

int __stdcall VideoGetDeviceCaps(HDC hdc, int index)
{
    return GetDeviceCaps(hdc, index);
};

BOOL MainInit(const HMODULE hModule)
{
    const auto mod = GetModuleHandle(NULL);
    Patch::Call(0x4898D9, Patch::GetP(PostLoadEngineLibrary)); // LoadLibraryA Call in Gol .dll seeking function

#ifdef _DEBUG
    Patch::Nop(0x48ACB6, 2); // Patch DX Media check to skip the intro videos
#endif

#ifdef _DEBUG
    MessageBoxA(NULL, "OnStart", "DEBUG", 0);
#endif

    return TRUE;
}

BOOL APIENTRY DllMain(const HMODULE hModule,
                      const DWORD ul_reason_for_call,
                      LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        return MainInit(hModule);

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
    default:
        break;
    }
    return TRUE;
}