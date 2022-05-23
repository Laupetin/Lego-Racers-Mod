#pragma once

#include "Component.h"
#include "Event.h"

namespace core
{
    extern Event<> onEngineInitialized;
}

class ComponentCore final : public Component
{
public:
    ComponentCore();

protected:
    bool InstallInternal() override;
};