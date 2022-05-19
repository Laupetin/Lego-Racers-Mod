#include <Windows.h>
#include <string>

#include "Patch.h"

void PostLoadEngineLibrary(void* arg)
{
    Patch::DoCall<void(void*)>(0x450D80)(arg);

    MessageBoxA(NULL, "PostLoadEngine", "", 0);
}

BOOL MainInit(const HMODULE hModule)
{
    const auto mod = GetModuleHandle(NULL);

    Patch::Call(0x4169FA, Patch::GetP(PostLoadEngineLibrary));

#ifdef _DEBUG

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