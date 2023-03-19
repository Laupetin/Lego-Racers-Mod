#include "Linker.h"

#include <cassert>
#include <filesystem>
#include <fstream>
#include <vector>

#include "FileUtils.h"
#include "Jam/JamFileWriter.h"
#include "Jam/JamTypes.h"

namespace fs = std::filesystem;

LinkerSettings::LinkerSettings()
    : m_verbose(false),
      m_force_linking(false)
{
}

class FileData
{
public:
    jam::jam_id_t m_id;
    fs::path m_path;

    FileData(const jam::jam_id_t id, fs::path path)
        : m_id(id),
          m_path(std::move(path))
    {
    }
};

class LinkerData final : public jam::IJamFileWriterDataProvider
{
public:
    std::unique_ptr<std::istream> GetDataForFile(const jam::jam_id_t file) override
    {
        assert(file < m_file_data.size());
        if (file >= m_file_data.size())
            return nullptr;

        auto stream = std::make_unique<std::ifstream>(m_file_data[file].m_path, std::ios::in | std::ios::binary);
        if (!stream->is_open())
        {
            std::cerr << "Failed to open file: " << m_file_data[file].m_path << "!\n";
            return nullptr;
        }

        return stream;
    }

    jam::DirectoryTree m_directory_tree;
    std::vector<FileData> m_file_data;
};

class LinkerImpl final : public ILinker
{
public:
    explicit LinkerImpl(LinkerSettings settings)
        : m_settings(std::move(settings))
    {
    }

    static bool WriteJamFile(const ProjectContext& context, LinkerData& linkerData)
    {
        std::ofstream stream(context.m_target_file_path, std::ios::out | std::ios::binary);
        if (!stream.is_open())
        {
            std::cerr << "Failed to open output file: " << context.m_target_file_path << "!\n";
            return false;
        }

        const auto writer = jam::IJamFileWriter::Create(stream);
        assert(writer);

        return writer->Write(linkerData.m_directory_tree, linkerData);
    }

    bool Link(const ProjectContext& context, const CompilerResult& compilerResult) const override
    {
        std::cout << "\n=============== Linking " << context.m_project_name << " ===============\n";
        if (TargetUpToDate(context, compilerResult))
        {
            std::cout << "Not linking: Everything up to date.\n";
            return true;
        }

        const auto linkerData = CreateLinkerData(compilerResult);

        if (!CreateDirectoryForTargetFile(context.m_target_file_path))
            return false;

        if (!WriteJamFile(context, *linkerData))
            return false;

        std::cout << "Linking successful -> \"" << context.m_target_file_path.string() << "\"\n";

        CopyTargetIfRequired(context.m_target_file_path);
        return true;
    }

private:
    bool TargetUpToDate(const ProjectContext& context, const CompilerResult& compilerResult) const
    {
        if (m_settings.m_force_linking || compilerResult.m_any_changes)
            return false;

        std::error_code err;
        const auto fileSize = fs::file_size(context.m_target_file_path, err);
        return !err && fileSize > 0;
    }

    static bool CreateDirectoryForTargetFile(const fs::path& targetFilePath)
    {
        const auto parentPath = fs::absolute(targetFilePath).parent_path();

        if (!fs::is_directory(parentPath) && !fs::create_directories(parentPath))
        {
            std::cerr << "Failed to create output directory: " << parentPath << "!\n";
            return false;
        }

        return true;
    }

    static std::unique_ptr<LinkerData> CreateLinkerData(const CompilerResult& compilerResult)
    {
        auto data = std::make_unique<LinkerData>();

        data->m_file_data.reserve(compilerResult.m_unit_processor_results.size());
        for (const auto& unitProcessorResult : compilerResult.m_unit_processor_results)
        {
            const auto& fileEntry = data->m_directory_tree.AddFile(unitProcessorResult.m_jam_path);
            data->m_file_data.emplace_back(fileEntry.Id(), unitProcessorResult.m_file);
        }

        return data;
    }

    void CopyTargetIfRequired(const fs::path& targetLocation) const
    {
        if (m_settings.m_copy_to.empty())
            return;

        fs::path copyToPath(m_settings.m_copy_to);

        if (!fs::is_directory(copyToPath))
        {
            const auto parentDirectory = fs::absolute(copyToPath).parent_path();

            if (!fs::is_directory(parentDirectory) && !fs::create_directories(parentDirectory))
            {
                std::cerr << "Failed to create directory for file copy: " << parentDirectory << "!\n";
                return;
            }
        }
        else
            copyToPath = copyToPath / targetLocation.filename();

        if (fs::copy_file(targetLocation, copyToPath, std::filesystem::copy_options::overwrite_existing))
            std::cout << "Copied target to \"" << copyToPath.string() << "\"\n";
        else
            std::cerr << "Failed to copy target to \"" << copyToPath.string() << "\"!\n";
    }

    LinkerSettings m_settings;
};

std::unique_ptr<ILinker> ILinker::Default(LinkerSettings settings)
{
    return std::make_unique<LinkerImpl>(std::move(settings));
}
