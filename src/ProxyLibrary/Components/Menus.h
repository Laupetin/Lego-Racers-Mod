#pragma once
#include "Component.h"

class ComponentMenus final : public Component
{
public:
    ComponentMenus();

protected:
    bool InstallInternal() override;
};
