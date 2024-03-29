#pragma once

#include "Compiler/IUnitProcessor.h"

class ModelUnitProcessorFactory final : public IUnitProcessorFactory
{
public:
    [[nodiscard]] std::unique_ptr<IUnitProcessor> CreateHandler(const ProjectContext& context, const std::filesystem::path& file) const override;
};
