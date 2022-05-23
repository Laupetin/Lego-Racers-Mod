#pragma once

#include "Component.h"
#include "Event.h"

namespace core
{
    extern Event<> onEngineInitialized;
}

class PatchCore final : public Component
{
public:
    PatchCore();

protected:
    bool InstallInternal() override;
};