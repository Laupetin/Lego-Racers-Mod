#include "Debug.h"

#include <iostream>
#include <Windows.h>

#include "RacersOffset.h"
#include "Detour.h"
#include "Offset.h"
#include "Patch.h"

namespace debug
{
    FunctionOffsetThiscall<int(void*, DWORD*)> saveLoadingBaseFunc(Offset().Racers01(0x429670));

    signed int GetSaveLoadingErrorCode(void* self, DWORD* a1)
    {
        const auto result = saveLoadingBaseFunc(self, a1); // Returns 17 if save has been modified (0x11)

        std::cout << "Save check: Returning " << result << "\n";

        // This crashes if the save has been tampered with, but later 
        return 0;
    }
}

using namespace debug;

ComponentDebug::ComponentDebug()
    : Component("Debug")
{
}

bool ComponentDebug::InstallInternal()
{
    // Patch DX Media check to skip the intro videos
    Patch::Nop(Offset().Racers01(0x48ACB6), 2);

    static CallDetourThiscall<int(void*, DWORD*)> saveLoadingDetour(Offset().Racers01(0x42AAAF), &GetSaveLoadingErrorCode);

    return true;
}
