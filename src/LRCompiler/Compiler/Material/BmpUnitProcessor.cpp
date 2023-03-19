#include "BmpUnitProcessor.h"

#include <filesystem>
#include <fstream>

#include "StringUtils.h"

namespace fs = std::filesystem;

class BmpUnitProcessor final : public IUnitProcessor
{
public:
    [[nodiscard]] bool ExamineInputsAndOutputs(const ProjectContext& context, const std::filesystem::path& file, UnitProcessorInputsAndOutputs& io) override
    {
        const auto relativeFilePath = fs::relative(file, context.m_data_path);
        m_intermediate_path = (context.m_obj_path / relativeFilePath).replace_extension(".bmp_bin");

        io.AddInput(file);
        io.AddIntermediate(m_intermediate_path);
        io.AddOutput(file, jam::JamFilePath(relativeFilePath.string()));

        return true;
    }

    [[nodiscard]] bool Compile(const ProjectContext& context, const std::filesystem::path& file) override
    {
        const std::ofstream out(m_intermediate_path, std::ios::out | std::ios::binary);
        if (!out.is_open())
        {
            std::cerr << "Could not open intermediate file " << m_intermediate_path << "!\n";
            return false;
        }

        return true;
    }

private:
    fs::path m_intermediate_path;
};

std::unique_ptr<IUnitProcessor> BmpUnitProcessorFactory::CreateHandler(const ProjectContext& context, const std::filesystem::path& file) const
{
    if (utils::StringEqualsIgnoreCase(file.extension().string(), ".bmp"))
        return std::make_unique<BmpUnitProcessor>();

    return nullptr;
}
