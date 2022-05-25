#pragma once
#include "Component.h"

class ComponentJamFiles final : public Component
{
public:
    ComponentJamFiles();

protected:
    bool InstallInternal() override;
};
