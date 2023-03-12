#include "JamFileWriter.h"

#include <cstdint>
#include <cstring>
#include <deque>

#include "Endianness.h"
#include "StreamUtils.h"
#include "Jam/JamDiskTypes.h"

using namespace jam;

namespace jam
{
    class DirectoryToCreate
    {
    public:
        explicit DirectoryToCreate(const jam_id_t id, const std::string& name)
            : m_id(id),
              m_name(name),
              m_file_start_index(0u),
              m_file_count(0u),
              m_sub_directory_start_index(0u),
              m_sub_directory_count(0u)
        {
        }

        jam_id_t m_id;
        const std::string& m_name;
        size_t m_file_start_index;
        size_t m_file_count;
        size_t m_sub_directory_start_index;
        size_t m_sub_directory_count;
    };

    class FileToCreate
    {
    public:
        FileToCreate(const jam_id_t id, const std::string& name, const int64_t offset, const int64_t size)
            : m_id(id),
              m_name(name),
              m_offset(offset),
              m_size(size)
        {
        }

        jam_id_t m_id;
        const std::string& m_name;
        int64_t m_offset;
        int64_t m_size;
    };
}

class JamFileWriterImpl final : public IJamFileWriter
{
public:
    static constexpr auto READ_BUFFER_SIZE = 0x4000;

    explicit JamFileWriterImpl(std::ostream& stream)
        : m_stream(stream),
          m_read_buffer(std::make_unique<char[]>(READ_BUFFER_SIZE))
    {
    }

    bool Write(const DirectoryTree& tree, IJamFileWriterDataProvider& provider) override
    {
        m_stream.seekp(0, std::ios::beg);
        WriteData(&JAM_FILE_MAGIC, sizeof(JAM_FILE_MAGIC));

        PrepareFromDirectoryTree(tree);
        if (!WriteFileData(provider))
            return false;
        WriteDirectoryTree();

        return true;
    }

private:
    void PrepareFromDirectoryTree(const DirectoryTree& tree)
    {
        std::deque<DirectoryEntry*> scanQueue;

        const auto& rootDir = tree.RootDirectory();
        if (!rootDir)
        {
            static const std::string DEFAULT_DIR = std::string();
            m_directories.emplace_back(jam_id_t(), DEFAULT_DIR);
            return;
        }

        scanQueue.emplace_back(rootDir.get());

        m_directories.reserve(tree.DirectoryCount());
        m_files.reserve(tree.FileCount());

        while (!scanQueue.empty())
        {
            const auto* dir = scanQueue.front();
            scanQueue.pop_front();

            for (const auto& subDirectory : dir->SubDirectories())
                scanQueue.push_back(subDirectory.get());

            auto& dirToCreate = m_directories.emplace_back(dir->Id(), dir->Name());
            dirToCreate.m_file_count = dir->Files().size();
            dirToCreate.m_file_start_index = m_files.size();
            dirToCreate.m_sub_directory_count = dir->SubDirectories().size();
            dirToCreate.m_sub_directory_start_index = m_directories.size() + scanQueue.size() - dirToCreate.m_sub_directory_count;

            for (const auto& file : dir->Files())
                m_files.emplace_back(file->Id(), file->Name(), 0, 0);
        }
    }

    void WriteData(const void* data, const size_t size) const
    {
        m_stream.write(static_cast<const char*>(data), size);
    }

    bool WriteFileData(IJamFileWriterDataProvider& provider)
    {
        const auto fileDataStartOffset = sizeof(JAM_FILE_MAGIC)
            + (sizeof(uint32_t) + sizeof(uint32_t)) * m_directories.size()
            + sizeof(DiskDirectoryEntry) * std::max(m_directories.size() - 1, 0u)
            + sizeof(DiskFileEntry) * m_files.size();

        m_stream.seekp(fileDataStartOffset, std::ios::beg);

        for (auto& fileToCreate : m_files)
        {
            const auto fileStartOffset = m_stream.tellp();

            if (!WriteDataForFile(provider, fileToCreate.m_id))
                return false;

            const auto fileEndOffset = m_stream.tellp();
            fileToCreate.m_offset = static_cast<size_t>(fileStartOffset);
            fileToCreate.m_size = static_cast<size_t>(fileEndOffset - fileStartOffset);
        }

        return true;
    }

    bool WriteDataForFile(IJamFileWriterDataProvider& provider, const jam_id_t id) const
    {
        const auto data = provider.GetDataForFile(id);
        if (!data)
            return false;

        while (!data->eof())
        {
            data->read(m_read_buffer.get(), READ_BUFFER_SIZE);
            const auto readSize = data->gcount();
            m_stream.write(m_read_buffer.get(), readSize);

            if (readSize < READ_BUFFER_SIZE)
                break;
        }

        return true;
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
            WriteData(&fileCountDisk, sizeof(fileCountDisk));

            const auto fileEndIndex = currentFileIndex + dir.m_file_count;
            while (currentFileIndex < fileEndIndex)
            {
                const auto& file = m_files[currentFileIndex];

                DiskFileEntry diskFile{};
                strncpy(diskFile.fileName, file.m_name.c_str(), std::extent_v<decltype(DiskFileEntry::fileName)>);
                diskFile.dataOffset = endianness::ToLittleEndian(static_cast<uint32_t>(file.m_offset));
                diskFile.dataSize = endianness::ToLittleEndian(static_cast<uint32_t>(file.m_size));
                WriteData(&diskFile, sizeof(diskFile));

                currentFileIndex++;
            }

            const auto subDirCountDisk = endianness::ToLittleEndian(static_cast<uint32_t>(dir.m_sub_directory_count));
            WriteData(&subDirCountDisk, sizeof(subDirCountDisk));

            const auto subDirectoryEndIndex = dir.m_sub_directory_start_index + dir.m_sub_directory_count;
            for (auto subDirectoryIndex = dir.m_sub_directory_start_index; subDirectoryIndex < subDirectoryEndIndex; subDirectoryIndex++)
            {
                const auto& subDir = m_directories[subDirectoryIndex];

                DiskDirectoryEntry diskDir{};
                strncpy(diskDir.directoryName, subDir.m_name.c_str(), std::extent_v<decltype(DiskDirectoryEntry::directoryName)>);

                const auto directoryDataBeforeMe = subDirectoryIndex;
                const auto diskDirectoriesBeforeMe = std::max(subDir.m_sub_directory_start_index - 1, 0u);
                const auto diskFilesBeforeMe = subDir.m_file_start_index;

                diskDir.dataOffset = sizeof(JAM_FILE_MAGIC)
                    + directoryDataBeforeMe * (sizeof(uint32_t) + sizeof(uint32_t))
                    + diskDirectoriesBeforeMe * sizeof(DiskDirectoryEntry)
                    + diskFilesBeforeMe * sizeof(DiskFileEntry);
                WriteData(&diskDir, sizeof(DiskDirectoryEntry));
            }

            currentDirectoryIndex++;
        }
    }

    std::ostream& m_stream;
    std::unique_ptr<char[]> m_read_buffer;
    std::vector<DirectoryToCreate> m_directories;
    std::vector<FileToCreate> m_files;
};

std::unique_ptr<IJamFileWriter> IJamFileWriter::Create(std::ostream& stream)
{
    return std::make_unique<JamFileWriterImpl>(stream);
}
