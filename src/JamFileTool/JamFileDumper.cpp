#include "JamFileDumper.h"

#include <iostream>
#include <fstream>
#include <exception>
#include <filesystem>
#include <sstream>
#include <memory>

#include "JamFileTypes.h"
#include "Endianness.h"
#include "IFileTypeDumper.h"
#include "Dumpers/PassthroughDumper.h"

using namespace dumping;
namespace fs = std::filesystem;

class JamFileReadingException final : public std::exception
{
public:
    explicit JamFileReadingException(const char* msg)
        : m_msg(msg)
    {
    }

    [[nodiscard]] char const* what() const override
    {
        return m_msg;
    }

private:
    const char* m_msg;
};

const IFileTypeDumper* availableFileTypeDumpers[]
{
    // Passthrough should be last due to it accepting any file and simply dumps its data unmodified
    new PassthroughDumper()
};

class JamFileDumper
{
public:
    JamFileDumper(std::istream& stream, fs::path dumpFolder)
        : m_stream(stream),
          m_dump_folder(std::move(dumpFolder))
    {
    }

    void Dump()
    {
        uint32_t magicBuffer;
        m_stream.seekg(0, std::ios::beg);

        Read(&magicBuffer, sizeof(magicBuffer));
        if (magicBuffer != JAM_FILE_MAGIC)
            throw JamFileReadingException("Not a JAM file");

        JamFileDiskDirectory rootDirectory{};
        memset(rootDirectory.directoryName, 0, std::extent_v<decltype(rootDirectory.directoryName)>);
        rootDirectory.dataOffset = 4u;

        DumpDirectory("", rootDirectory);
    }

private:
    void Read(void* dst, const size_t size) const
    {
        const auto readCount = m_stream.read(static_cast<char*>(dst), size).gcount();
        if (readCount != size)
            throw JamFileReadingException("Unexpected EOF");
    }

    static std::string GetDiskDirectoryPath(const std::string& currentPath, const JamFileDiskDirectory& diskDirectory)
    {
        std::ostringstream ss;
        ss << currentPath;
        if (!currentPath.empty())
            ss << "/";

        const std::string diskDirectoryName(diskDirectory.directoryName, strnlen(diskDirectory.directoryName, std::extent_v<decltype(diskDirectory.directoryName)>));
        ss << diskDirectoryName;
        return ss.str();
    }

    static std::string GetDiskFilePath(const std::string& currentPath, const std::string& fileName)
    {
        std::ostringstream filePathStream;
        filePathStream << currentPath << "\\" << fileName;
        auto filePath = filePathStream.str();
        std::replace(filePath.begin(), filePath.end(), '/', '\\');
        return filePath;
    }

    [[nodiscard]] std::vector<JamFileDiskFile> ReadDirectoryFiles() const
    {
        std::vector<JamFileDiskFile> files;
        uint32_t fileCount;
        Read(&fileCount, sizeof(fileCount));
        fileCount = endianness::FromLittleEndian(fileCount);

        if (fileCount > 100000)
            throw JamFileReadingException("Too many files");

        for (auto i = 0u; i < fileCount; i++)
        {
            JamFileDiskFile file{};
            Read(&file, sizeof(file));
            files.emplace_back(file);
        }

        return files;
    }

    [[nodiscard]] std::vector<JamFileDiskDirectory> ReadDirectorySubDirectories() const
    {
        std::vector<JamFileDiskDirectory> subDirectories;
        uint32_t subDirectoryCount;
        Read(&subDirectoryCount, sizeof(subDirectoryCount));
        subDirectoryCount = endianness::FromLittleEndian(subDirectoryCount);

        if (subDirectoryCount > 100000)
            throw JamFileReadingException("Too many subdirectories");

        for (auto i = 0u; i < subDirectoryCount; i++)
        {
            JamFileDiskDirectory subDirectory{};
            Read(&subDirectory, sizeof(subDirectory));
            subDirectories.emplace_back(subDirectory);
        }

        return subDirectories;
    }

    void DumpFile(const std::string& currentPath, const fs::path& dumpPath, const JamFileDiskFile& file) const
    {
        if (file.dataSize <= 0)
            return;

        const std::string fileName(file.fileName, strnlen(file.fileName, std::extent_v<decltype(file.fileName)>));
        const auto dumpFilePath = dumpPath / fileName;

        auto fileExtension = fs::path(fileName).extension().string();
        for (auto& c : fileExtension)
            c = static_cast<char>(toupper(c));

        const auto filePath = GetDiskFilePath(currentPath, fileName);

        std::ofstream streamOut(dumpFilePath, std::ios::out | std::ios::binary);
        if (!streamOut.is_open())
            throw JamFileReadingException("Could not open file for output");

        const auto fileDataBuffer = std::make_unique<char[]>(file.dataSize);
        m_stream.seekg(file.dataOffset, std::ios::beg);
        m_stream.read(fileDataBuffer.get(), file.dataSize);

        for (const auto* fileDumper : availableFileTypeDumpers)
        {
            if (fileDumper->SupportFileExtension(fileExtension))
            {
                fileDumper->DumpFile(filePath, fileDataBuffer.get(), file.dataSize, streamOut);
                break;
            }
        }
    }

    void DumpDirectory(const std::string& currentPath, const JamFileDiskDirectory& diskDirectory)
    {
        const auto diskDirectoryPath = GetDiskDirectoryPath(currentPath, diskDirectory);
        const auto dumpPath = m_dump_folder / diskDirectoryPath;
        fs::create_directories(dumpPath);

        m_stream.seekg(diskDirectory.dataOffset, std::ios::beg);

        const auto files = ReadDirectoryFiles();
        const auto subDirectories = ReadDirectorySubDirectories();

        for (const auto& file : files)
            DumpFile(diskDirectoryPath, dumpPath, file);

        for (const auto& subDirectory : subDirectories)
        {
            if (subDirectory.dataOffset < diskDirectory.dataOffset + sizeof(JamFileDiskDirectory))
                throw JamFileReadingException("SubDirectory does not follow current directory");

            DumpDirectory(diskDirectoryPath, subDirectory);
        }
    }

    std::istream& m_stream;
    fs::path m_dump_folder;
};

void dumping::DumpJamFile(const std::string& filePath)
{
    std::ifstream stream(filePath, std::ios::in | std::ios::binary);
    if (!stream.is_open())
    {
        std::cerr << "Failed to open JAM File: \"" << filePath << "\"\n";
        return;
    }

    const fs::path path(filePath);
    const auto dumpFolder = path.parent_path() / path.filename().replace_extension();
    fs::create_directories(dumpFolder);

    std::cout << "Dumping JAM file \"" << filePath << "\"" << " to folder \"" << dumpFolder << "\"\n";

    try
    {
        JamFileDumper dumper(stream, dumpFolder);
        dumper.Dump();
    }
    catch (const JamFileReadingException& e)
    {
        std::cerr << "Failed to dump JAM file: " << e.what() << "\n";
    }
}
