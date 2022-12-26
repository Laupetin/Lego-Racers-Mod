#include "GdbUnitProcessor.h"

#include <filesystem>

#include "StringUtils.h"

namespace fs = std::filesystem;

class GdbUnitProcessor final : public IUnitProcessor
{
public:
    [[nodiscard]] bool ExamineInputsAndOutputs(const ProjectContext& context, const std::filesystem::path& file, UnitProcessorInputsAndOutputs& io) override
    {
        const auto relativeFilePath = fs::relative(file, context.m_data_path);
        m_out_path = context.m_obj_path / relativeFilePath;

        io.AddInput(file);
        io.AddOutput(m_out_path, JamFilePath(relativeFilePath.string()));

        return true;
    }

    [[nodiscard]] bool Compile(const ProjectContext& context, const std::filesystem::path& file) override
    {
        return false;
    }

private:
    fs::path m_out_path;
};

std::unique_ptr<IUnitProcessor> GdbUnitProcessorFactory::CreateHandler(const ProjectContext& context, const std::filesystem::path& file) const
{
    if (utils::StringEqualsIgnoreCase(file.extension().string(), ".gdb"))
        return std::make_unique<GdbUnitProcessor>();

    return nullptr;
}
