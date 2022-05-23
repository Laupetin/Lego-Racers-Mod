#include "PatchCore.h"

#include <iostream>

#include "RacersOffset.h"
#include "Game/LEGORacers2001.h"
#include "patch/Patch.h"

namespace core
{
    Event<> onEngineInitialized;

    DWORD* __cdecl PostLoadEngineLibrary(DWORD* a1)
    {
        const auto result = Patch::DoCall<DWORD*(DWORD*)>(Offset().Racers01(0x4797E0))(a1);

        onEngineInitialized();

#ifdef _DEBUG
        MessageBoxA(NULL, "PostLoadEngine", "DEBUG", 0);
#endif

        return result;
    }

    void SpawnDevConsole()
    {
        if (AllocConsole())
        {
            freopen("CONOUT$", "w", stdout);
            freopen("CONOUT$", "w", stderr);
            freopen("CONIN$", "r", stdin);

            SetConsoleTitleA("LegoRacersMod Console");
        }

        std::cout << "Launching LegoRacersMod\n";
    }
}

using namespace core;

PatchCore::PatchCore()
    : Component("Core")
{
}

bool PatchCore::InstallInternal()
{
    SpawnDevConsole();

    Patch::Call(0x4898D9, Patch::GetP(PostLoadEngineLibrary)); // first function called after GoL loading

    return true;
}
