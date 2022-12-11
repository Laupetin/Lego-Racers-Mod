#include "JamFileCreator.h"

#include <deque>
#include <iostream>
#include <fstream>
#include <exception>
#include <filesystem>
#include <sstream>
#include <memory>

#include "JamFileTypes.h"
#include "Endianness.h"
#include "Asset/IFileTypeProcessor.h"
#include "Asset/Mdb/MdbCreator.h"
#include "StreamUtils.h"
#include "Asset/PassthroughCreator.h"
#include "Asset/Gdb/GdbCreator.h"
#include "Asset/Idb/IdbCreator.h"
#include "Asset/Srf/SrfCreator.h"
#include "Asset/Tdb/TdbCreator.h"

namespace fs = std::filesystem;

class JamFileWritingException final : public std::exception
{
public:
    explicit JamFileWritingException(std::string msg)
        : m_msg(std::move(msg))
    {
    }

    [[nodiscard]] char const* what() const noexcept override
    {
        return m_msg.c_str();
    }

private:
    std::string m_msg;
};

const IFileTypeProcessor* availableFileTypeCreators[]
{
    new gdb::GdbCreator(),
    new IdbCreator(),
    new mdb::MdbCreator(),
    new SrfCreator(),
    new TdbCreator(),

    // Passthrough should be last due to it accepting any file and simply creates its data unmodified
    new PassthroughCreator()
};

class JamFileDirectoryToCreate
{
public:
    explicit JamFileDirectoryToCreate(fs::path path)
        : m_path(std::move(path)),
          m_file_start_index(0u),
          m_file_count(0u),
          m_sub_directory_start_index(0u),
          m_sub_directory_count(0u)
    {
    }

    fs::path m_path;
    size_t m_file_start_index;
    size_t m_file_count;
    size_t m_sub_directory_start_index;
    size_t m_sub_directory_count;
};

class JamFileFileToCreate
{
public:
    JamFileFileToCreate(fs::path path, const size_t offset, const size_t size)
        : m_path(std::move(path)),
          m_offset(offset),
          m_size(size)
    {
    }

    fs::path m_path;
    size_t m_offset;
    size_t m_size;
};

class JamFileCreator
{
public:
    JamFileCreator(std::ostream& stream, fs::path loadFolder)
        : m_stream(stream),
          m_load_folder(std::move(loadFolder)),
          m_current_offset(0u)
    {
    }

    void Create()
    {
        m_current_offset = 0u;
        m_stream.seekp(0, std::ios::beg);
        Write(&JAM_FILE_MAGIC, sizeof(JAM_FILE_MAGIC));

        PrepareFromDirectory(m_load_folder);
        WriteFileData();
        WriteDirectoryTree();
    }

private:
    void Write(const void* data, const size_t size)
    {
        m_stream.write(static_cast<const char*>(data), size);
        m_current_offset += size;
    }

    void PrepareFromDirectory(const size_t dirIndex, uint32_t& fileDataOffset)
    {
        const auto fileStartIndex = m_files.size();
        const auto subDirectoryStartIndex = m_directories.size();

        for (const auto& entry : fs::directory_iterator(m_directories[dirIndex].m_path, std::filesystem::directory_options::skip_permission_denied))
        {
            if (entry.is_directory())
            {
                m_directories.emplace_back(entry.path());
            }
            else if (entry.is_regular_file())
            {
                const auto fileSize = static_cast<size_t>(entry.file_size());
                m_files.emplace_back(entry.path(), fileDataOffset, fileSize);
                fileDataOffset += fileSize;
            }
        }

        auto& dir = m_directories[dirIndex];
        dir.m_file_start_index = fileStartIndex;
        dir.m_file_count = m_files.size() - fileStartIndex;
        dir.m_sub_directory_start_index = subDirectoryStartIndex;
        dir.m_sub_directory_count = m_directories.size() - subDirectoryStartIndex;
    }

    void PrepareFromDirectory(const fs::path& path)
    {
        m_directories.clear();
        m_directories.emplace_back(path);
        uint32_t fileDataOffset = 0u;

        for (auto currentDirectoryIndex = 0u; currentDirectoryIndex < m_directories.size(); currentDirectoryIndex++)
        {
            PrepareFromDirectory(currentDirectoryIndex, fileDataOffset);
        }
    }

    void WriteFileData()
    {
        const auto fileDataStartOffset = sizeof(JAM_FILE_MAGIC)
            + (sizeof(uint32_t) + sizeof(uint32_t)) * m_directories.size()
            + sizeof(JamFileDiskDirectory) * std::max(m_directories.size() - 1, 0u)
            + sizeof(JamFileDiskFile) * m_files.size();

        m_stream.seekp(fileDataStartOffset, std::ios::beg);

        for (auto& file : m_files)
        {
            const auto extension = file.m_path.filename().extension().string();
            auto relativePath = fs::relative(file.m_path, m_load_folder).string();
            std::replace(relativePath.begin(), relativePath.end(), '/', '\\');

            std::ifstream input(file.m_path, std::ios::in | std::ios::binary);
            if (!input.is_open())
                throw JamFileWritingException("Unable to open input file");

            const auto fileData = std::make_unique<char[]>(file.m_size);
            utils::ReadOrThrow(input, fileData.get(), file.m_size);

            const auto fileStartOffset = m_stream.tellp();
            for (const auto* fileCreator : availableFileTypeCreators)
            {
                if (fileCreator->SupportFileExtension(extension))
                {
                    fileCreator->ProcessFile(relativePath, fileData.get(), file.m_size, m_stream);
                    break;
                }
            }
            const auto fileEndOffset = m_stream.tellp();
            file.m_offset = static_cast<size_t>(fileStartOffset);
            file.m_size = static_cast<size_t>(fileEndOffset - fileStartOffset);
        }
    }

    void WriteDirectoryTree()
    {
        constexpr auto directoryTreeStartOffset = sizeof(JAM_FILE_MAGIC);
        m_stream.seekp(directoryTreeStartOffset, std::ios::beg);

        auto currentFileIndex = 0u;
        auto currentDirectoryIndex = 0u;
        for (const auto& dir : m_directories)
        {
            const auto fileCountDisk = endianness::ToLittleEndian(static_cast<uint32_t>(dir.m_file_count));
            Write(&fileCountDisk, sizeof(fileCountDisk));

            const auto fileEndIndex = currentFileIndex + dir.m_file_count;
            while (currentFileIndex < fileEndIndex)
            {
                const auto& file = m_files[currentFileIndex];
                auto fileName = file.m_path.filename().string();
                if (fileName.size() > std::extent_v<decltype(JamFileDiskFile::fileName)>)
                {
                    std::ostringstream ss;
                    ss << "File name too long: \"" << fileName << "\"";
                    throw JamFileWritingException(ss.str());
                }

                for (auto& c : fileName)
                    c = static_cast<char>(toupper(c));

                JamFileDiskFile diskFile{};
                strncpy(diskFile.fileName, fileName.c_str(), std::extent_v<decltype(JamFileDiskFile::fileName)>);
                diskFile.dataOffset = endianness::ToLittleEndian(static_cast<uint32_t>(file.m_offset));
                diskFile.dataSize = endianness::ToLittleEndian(static_cast<uint32_t>(file.m_size));
                Write(&diskFile, sizeof(diskFile));

                currentFileIndex++;
            }

            const auto subDirCountDisk = endianness::ToLittleEndian(static_cast<uint32_t>(dir.m_sub_directory_count));
            Write(&subDirCountDisk, sizeof(subDirCountDisk));

            const auto subDirectoryEndIndex = dir.m_sub_directory_start_index + dir.m_sub_directory_count;
            for (auto subDirectoryIndex = dir.m_sub_directory_start_index; subDirectoryIndex < subDirectoryEndIndex; subDirectoryIndex++)
            {
                const auto& subDir = m_directories[subDirectoryIndex];
                const auto dirName = subDir.m_path.filename().string();
                if (dirName.size() > std::extent_v<decltype(JamFileDiskDirectory::directoryName)>)
                    throw JamFileWritingException("Directory name too long");

                JamFileDiskDirectory diskDir{};
                strncpy(diskDir.directoryName, dirName.c_str(), std::extent_v<decltype(JamFileDiskDirectory::directoryName)>);

                const auto directoryDataBeforeMe = subDirectoryIndex;
                const auto diskDirectoriesBeforeMe = std::max(subDir.m_sub_directory_start_index - 1, 0u);
                const auto diskFilesBeforeMe = subDir.m_file_start_index;

                diskDir.dataOffset = sizeof(JAM_FILE_MAGIC)
                    + directoryDataBeforeMe * (sizeof(uint32_t) + sizeof(uint32_t))
                    + diskDirectoriesBeforeMe * sizeof(JamFileDiskDirectory)
                    + diskFilesBeforeMe * sizeof(JamFileDiskFile);
                Write(&diskDir, sizeof(JamFileDiskDirectory));
            }

            currentDirectoryIndex++;
        }
    }

    std::ostream& m_stream;
    fs::path m_load_folder;
    uint32_t m_current_offset;
    std::vector<JamFileDirectoryToCreate> m_directories;
    std::vector<JamFileFileToCreate> m_files;
};

void creating::CreateJamFile(const std::string& directoryPath)
{
    const fs::path path(directoryPath);
    const auto jamPath = path.parent_path() / path.filename().replace_extension(".JAM");

    std::cout << "Creating JAM file \"" << jamPath.string() << "\"" << " from folder \"" << path.string() << "\"\n";
    std::ofstream stream(jamPath, std::ios::out | std::ios::binary | std::ios::trunc);
    if (!stream.is_open())
    {
        std::cerr << "Failed to open JAM File: \"" << directoryPath << "\"\n";
        return;
    }

    try
    {
        JamFileCreator creator(stream, path);
        creator.Create();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Failed to create JAM file: " << e.what() << "\n";
    }
}
