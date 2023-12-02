#include "JamFiles.h"

#include "Core.h"
#include "Detour.h"
#include "Game/Fields.h"
#include "Offset.h"
#include "Patch.h"
#include "RacersOffset.h"

#include <iostream>

namespace jam_files
{
}

using namespace jam_files;

ComponentJamFiles::ComponentJamFiles()
    : Component("JamFiles")
{
}

bool ComponentJamFiles::InstallInternal()
{
    Patch::Field<const char*>(0x4E7198, "mod.jam\nlego.jam");

    static FieldOffset<const char> absolutePathBuffer1(Offset().Racers01(0x4F90F8));
    static FieldOffset<const char> absolutePathBuffer2(Offset().Racers01(0x4F8FDC));
    static FunctionDetourTrampoline<void(const char*, const char*)> absolutePathTrampoline;
    absolutePathTrampoline.Init(Offset().Racers01(0x478380),
                                [](const char* s1, const char* s2)
                                {
                                    const auto& windowSettings = game::gameConfig->windowSettings;

                                    if (windowSettings.environment.unknown5)
                                        std::cout << "Before Absolute Path: " << *windowSettings.environment.unknown5 << "\n";
                                    absolutePathTrampoline(s1, s2);
                                    std::cout << "After Absolute Path: " << s2 << " -> " << absolutePathBuffer2.Ptr() << "\n";
                                });

    core::onEngineInitialized.RegisterCallback(
        []()
        {
            static FieldOffset<const char> absolutePathBuffer2Engine(Offset().Racers01(0x100630E0));
            static FunctionDetourTrampoline<void(const char*, const char*)> absolutePathTrampolineEngine;
            absolutePathTrampolineEngine.Init(Offset().Racers01(0x10042C30),
                                              [](const char* s1, const char* s2)
                                              {
                                                  const auto& windowSettings = game::gameConfig->windowSettings;

                                                  if (windowSettings.environment.unknown5)
                                                      std::cout << "Before Absolute Path (Engine): " << *windowSettings.environment.unknown5 << "\n";
                                                  absolutePathTrampolineEngine(s1, s2);
                                                  std::cout << "After Absolute Path (Engine): " << s2 << " -> " << absolutePathBuffer2Engine.Ptr() << "\n";
                                              });

            return true;
        });

    return true;
}
