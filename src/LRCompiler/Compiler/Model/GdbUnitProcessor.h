#pragma once

#include "Compiler/IUnitProcessor.h"

class GdbUnitProcessor final : public IUnitProcessor
{
public:
    [[nodiscard]] bool Handles(const ProjectContext& context, const std::filesystem::path& file) const override;
    [[nodiscard]] bool ExamineInputsAndOutputs(const ProjectContext& context, UnitProcessorUserData& userData, const std::filesystem::path& file,
                                               UnitProcessorInputsAndOutputs& io) const override;
    [[nodiscard]] bool Compile(const ProjectContext& context, UnitProcessorUserData& userData, const std::filesystem::path& file,
                               std::vector<UnitProcessorResult>& results) const override;
};
