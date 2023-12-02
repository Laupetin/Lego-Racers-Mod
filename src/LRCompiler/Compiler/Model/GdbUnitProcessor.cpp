#include "GdbUnitProcessor.h"

#include "Asset/Gdb/GdbBinaryWriter.h"
#include "Asset/Gdb/GdbTextReader.h"
#include "StringUtils.h"

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

class GdbUnitProcessor final : public IUnitProcessor
{
public:
    [[nodiscard]] bool ExamineInputsAndOutputs(const ProjectContext& context, const std::filesystem::path& file, UnitProcessorInputsAndOutputs& io) override
    {
        const auto relativeFilePath = fs::relative(file, context.m_data_path);
        m_out_path = (context.m_obj_path / relativeFilePath).replace_extension(".gdb_bin");

        io.AddInput(file);
        io.AddOutput(m_out_path, jam::JamFilePath(relativeFilePath.string()));

        return true;
    }

    [[nodiscard]] bool Compile(const ProjectContext& context, const std::filesystem::path& file) override
    {
        std::ifstream in(file, std::ios::in | std::ios::binary);
        if (!in.is_open())
        {
            std::cerr << "Could not open input file " << file << "!\n";
            return false;
        }

        std::ofstream out(m_out_path, std::ios::out | std::ios::binary);
        if (!out.is_open())
        {
            std::cerr << "Could not open output file " << m_out_path << "!\n";
            return false;
        }

        try
        {
            const auto writer = gdb::GdbBinaryWriter::Create(out);
            gdb::GdbTextReader::Read(in, *writer);
        }
        catch (std::exception& e)
        {
            std::cerr << "Compiling GDB failed: " << e.what() << "\n";
            return false;
        }

        return true;
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
