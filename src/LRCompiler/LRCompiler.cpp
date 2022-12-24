#include "LRCompiler.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "LRCompilerArgs.h"
#include "StringUtils.h"
#include "Project/ProjectDefinition.h"

namespace fs = std::filesystem;

class LRCompiler::Impl
{
    static constexpr auto PROJECT_FILE_EXTENSION = ".lrproj";

public:
    Impl()
    = default;

    bool Start(const int argc, const char** argv)
    {
        if (!m_args.ParseArgs(argc, argv))
            return false;

        for (const auto& object : m_args.m_compile_objects)
            CompileObject(object);

        return true;
    }

private:
    void CompileObject(const std::string& object)
    {
        const auto status = fs::status(object);

        if (status.type() == std::filesystem::file_type::directory)
            CompileObjectDirectory(object);
        else if (status.type() == std::filesystem::file_type::regular)
            CompileObjectFile(object);
    }

    void CompileObjectDirectory(const std::string& directoryObject)
    {
        auto foundProjectFile = false;
        for (const auto& file : fs::directory_iterator(directoryObject))
        {
            if (!file.is_regular_file())
                continue;

            if (!utils::StringEqualsIgnoreCase(file.path().extension().string(), PROJECT_FILE_EXTENSION))
                continue;

            CompileObjectFile(file.path().string());
            foundProjectFile = true;
        }

        if (!foundProjectFile)
            std::cerr << "Failed to find lrproj file in: \"" << directoryObject << "\"\n";
    }

    void CompileObjectFile(const std::string& fileObject)
    {
        std::ifstream stream(fileObject, std::ios::in | std::ios::binary);
        if (!stream.is_open())
        {
            std::cerr << "Failed to open project file: \"" << fileObject << "\"\n";
            return;
        }

        const auto definition = ProjectDefinitionReader::ReadDefinition(stream, fileObject);
        if (!definition)
        {
            std::cerr << "Failed to read project file: \"" << fileObject << "\"\n";
            return;
        }

        std::cout << "Compiling object file: \"" << fileObject << "\": target=" << definition->m_target.m_name << "\n";
    }

    LRCompilerArgs m_args;
};

LRCompiler::LRCompiler()
    : m_impl(new Impl())
{
}

LRCompiler::~LRCompiler()
{
    delete m_impl;
    m_impl = nullptr;
}

bool LRCompiler::Start(const int argc, const char** argv) const
{
    return m_impl->Start(argc, argv);
}
