#include <Windows.h>
#include <string>

#include "RacersOffset.h"
#include "patch/Patch.h"
#include "patch/Detour.h"
#include "patch/Offset.h"
#include "Patches/PatchCore.h"
#include "Patches/PatchWindowed.h"

FunctionOffsetThiscall<int(void*, DWORD*)> saveLoadingBaseFunc(Offset().Racers01(0x429670));

signed int GetSaveLoadingErrorCode(void* _THIS, DWORD* a1)
{
    auto result = saveLoadingBaseFunc(_THIS, a1); // Returns 17 if save has been modified (0x11)

    // This crashes if the save has been tampered with, but later 
    return 0;
}

Component* components[]
{
    new PatchCore(),
    new PatchWindowed()
};

BOOL MainInit(const HMODULE hModule)
{
    TrampolineGlobals::Instance().SetTargetCompiler(TargetCompiler::MSVC);
    Offset::ApplyRacers01();

    static CallDetourThiscall<int(void*, DWORD*)> saveLoadingDetour(Offset().Racers01(0x42AAAF), &GetSaveLoadingErrorCode);

#ifdef _DEBUG
    // Patch DX Media check to skip the intro videos
    //Patch::Nop(Offset().Racers01(0x48ACB6), 2);
#endif

    // Install all components
    for (auto* component : components)
    {
        component->Install();
    }

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
