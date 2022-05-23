#pragma once
#include "Component.h"

class PatchWindowed final : public Component
{
public:
    PatchWindowed();

protected:
    bool InstallInternal() override;
};
