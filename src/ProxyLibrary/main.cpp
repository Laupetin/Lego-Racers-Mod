#include <Windows.h>
#include <string>

#include "Patch.h"

DWORD* __cdecl PostLoadEngineLibrary(DWORD* a1)
{
    auto result = Patch::DoCall<DWORD*(DWORD*)>(0x4797E0)(a1);

    return result;
}

signed int __fastcall GetSaveLoadingErrorCode(void* _THIS,  DWORD* a1, int a2)
{
    auto result = Patch::DoCall<signed int(void*, DWORD*, int)>(0x429670)(_THIS, a1, a2);;

    return 0;
}

BOOL MainInit(const HMODULE hModule)
{
    const auto mod = GetModuleHandle(NULL);
    Patch::Call(0x4898D9, Patch::GetP(PostLoadEngineLibrary)); // first function called after GoL loading

    //Patch::Call(0x42AAAF, Patch::GetP(GetSaveLoadingErrorCode));
    //Patch::Call(0x42A678, Patch::GetP(GetSaveLoadingErrorCode));
    
#ifdef _DEBUG
    // Patch DX Media check to skip the intro videos
    Patch::Nop(0x48ACB6, 2);

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