#pragma once

#include "LEGORacers2001.h"
#include "RacersOffset.h"
#include "patch/Offset.h"

namespace game
{
    static inline FieldOffset<GameConfig> gameConfig(Offset().Racers01(0x4EF440));
}