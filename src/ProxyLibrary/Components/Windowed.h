#pragma once
#include "Component.h"

class ComponentWindowed final : public Component
{
public:
    ComponentWindowed();

protected:
    bool InstallInternal() override;
};
