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
    //auto result = Patch::DoCall<signed int(void*, DWORD*, int)>(0x429670)(_THIS, a1, a2);
    //saveLoadingBaseFunc(_THIS, a1, a2);

    return 0;
}

BOOL MainInit(const HMODULE hModule)
{
    OffsetManager::Instance().InitAll(0);
    OffsetManager::Instance().SetTargetCompiler(TargetCompiler::MSVC);

    const auto mod = GetModuleHandle(NULL);
    Patch::Call(0x4898D9, Patch::GetP(PostLoadEngineLibrary)); // first function called after GoL loading

    static CallDetourThiscall<int(void*, DWORD*)> saveLoadingDetour;
    saveLoadingDetour.Init(0x42AAAF, &GetSaveLoadingErrorCode);

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