#include "TdbUnitProcessor.h"

#include <filesystem>
#include <fstream>

#include "StringUtils.h"
#include "Asset/Tdb/TdbTextReader.h"
#include "Asset/Tdb/TdbBinaryWriter.h"

namespace fs = std::filesystem;

class TdbUnitProcessor final : public IUnitProcessor
{
public:
    [[nodiscard]] bool ExamineInputsAndOutputs(const ProjectContext& context, const std::filesystem::path& file, UnitProcessorInputsAndOutputs& io) override
    {
        const auto relativeFilePath = fs::relative(file, context.m_data_path);
        m_out_path = (context.m_obj_path / relativeFilePath).replace_extension(".tdb_bin");

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
            const auto writer = tdb::TdbBinaryWriter::Create(out);
            tdb::TdbTextReader::Read(in, *writer);
        }
        catch (std::exception& e)
        {
            std::cerr << "Compiling TDB failed: " << e.what() << "\n";
            return false;
        }

        return true;
    }

private:
    fs::path m_out_path;
};

std::unique_ptr<IUnitProcessor> TdbUnitProcessorFactory::CreateHandler(const ProjectContext& context, const std::filesystem::path& file) const
{
    if (utils::StringEqualsIgnoreCase(file.extension().string(), ".tdb"))
        return std::make_unique<TdbUnitProcessor>();

    return nullptr;
}
