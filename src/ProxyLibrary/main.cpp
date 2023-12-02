#include "Components/Core.h"
#include "Components/Debug.h"
#include "Components/JamFiles.h"
#include "Components/Menus.h"
#include "Components/Windowed.h"
#include "Offset.h"
#include "Patch.h"
#include "RacersOffset.h"

#include <Windows.h>
#include <string>

Component* components[]{
    new ComponentCore(),

#ifdef _DEBUG
    new ComponentDebug(),
#endif

    new ComponentMenus(),
    new ComponentWindowed(),
    new ComponentJamFiles(),
};

void DetectGameEnvironment()
{
    TrampolineGlobals::Instance().SetTargetCompiler(TargetCompiler::MSVC);
    Offset::ApplyRacers01();
}

BOOL MainInit(const HMODULE hModule)
{
    DetectGameEnvironment();

    // Install all components
    for (auto* component : components)
    {
        component->Install();
    }

#ifdef _DEBUG
    MessageBoxA(nullptr, "OnStart", "DEBUG", 0);
#endif

    return TRUE;
}

BOOL APIENTRY DllMain(const HMODULE hModule, const DWORD ul_reason_for_call, LPVOID lpReserved)
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
