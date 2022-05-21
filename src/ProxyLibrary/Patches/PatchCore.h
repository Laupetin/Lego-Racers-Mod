#pragma once
#include "Event.h"

namespace core
{
    extern Event<> onEngineInitialized;

    void DoPatch();
}
