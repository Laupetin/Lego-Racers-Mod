#pragma once
#include "Component.h"

class ComponentDebug final : public Component
{
public:
    ComponentDebug();

protected:
    bool InstallInternal() override;
};
