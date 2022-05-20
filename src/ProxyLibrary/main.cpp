#include <Windows.h>
#include <string>

#include "patch/Patch.h"
#include "patch/Detour.h"
#include "patch/Offset.h"

FunctionOffsetThiscall<int(void*, DWORD*)> saveLoadingBaseFunc({0x429670});

DWORD* __cdecl PostLoadEngineLibrary(DWORD* a1)
{
    auto result = Patch::DoCall<DWORD*(DWORD*)>(0x4797E0)(a1);

    return result;
}

signed int GetSaveLoadingErrorCode(void* _THIS,  DWORD* a1)
{
    auto result = saveLoadingBaseFunc(_THIS, a1); // Returns 17 if save has been modified (0x11)

    // This crashes if the save has been tampered with, but later 
    return 0;
}

BOOL MainInit(const HMODULE hModule)
{
    OffsetManager::Instance().SetTargetCompiler(TargetCompiler::MSVC);
    OffsetManager::Instance().InitAll(0);

    const auto mod = GetModuleHandle(NULL);
    Patch::Call(0x4898D9, Patch::GetP(PostLoadEngineLibrary)); // first function called after GoL loading

    static CallDetourThiscall<int(void*, DWORD*)> saveLoadingDetour;
    saveLoadingDetour.Init(0x42AAAF, &GetSaveLoadingErrorCode);
    
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