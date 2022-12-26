#include "GdbUnitProcessor.h"

#include <filesystem>

#include "StringUtils.h"

namespace fs = std::filesystem;

bool GdbUnitProcessor::Handles(const ProjectContext& context, const std::filesystem::path& file) const
{
    return utils::StringEqualsIgnoreCase(file.extension().string(), ".gdb");
}

bool GdbUnitProcessor::ExamineInputsAndOutputs(const ProjectContext& context, UnitProcessorUserData& userData, const std::filesystem::path& file,
                                               UnitProcessorInputsAndOutputs& io) const
{
    const auto relativeFilePath = fs::relative(file, context.m_data_path);

    io.AddInput(file);
    io.AddOutput(context.m_obj_path / relativeFilePath, JamFilePath(relativeFilePath.string()));

    return true;
}

bool GdbUnitProcessor::Compile(const ProjectContext& context, UnitProcessorUserData& userData, const std::filesystem::path& file, std::vector<UnitProcessorResult>& results) const
{
    return false;
}
