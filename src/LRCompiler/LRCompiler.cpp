#include "LRCompiler.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "LRCompilerArgs.h"
#include "StringUtils.h"
#include "Project/ProjectContext.h"
#include "Project/ProjectDefinition.h"

namespace fs = std::filesystem;

class LRCompiler::Impl
{
public:
    Impl()
    = default;

    bool Start(const int argc, const char** argv)
    {
        if (!m_args.ParseArgs(argc, argv))
            return false;

        for (const auto& project : m_args.m_compile_projects)
            CompileProject(project);

        return true;
    }

private:
    void CompileProject(const std::string& object)
    {
        const auto status = fs::status(object);

        if (status.type() == std::filesystem::file_type::directory)
            CompileProjectDirectoryOrFiles(object);
        else if (status.type() == std::filesystem::file_type::regular)
            CompileProjectFile(object);
    }

    void CompileProjectDirectoryOrFiles(const std::string& directory)
    {
        auto foundProjectFile = false;
        for (const auto& file : fs::directory_iterator(directory))
        {
            if (!file.is_regular_file())
                continue;

            if (!utils::StringEqualsIgnoreCase(file.path().extension().string(), ProjectDefinition::PROJ_EXTENSION))
                continue;

            CompileProjectFile(file.path().string());
            foundProjectFile = true;
        }

        if (!foundProjectFile)
            CompileProjectDirectory(directory);
    }

    void CompileProjectDirectory(const std::string& directoryObject)
    {
        const auto definition = ProjectDefinition::DefaultDefinition(directoryObject);
        m_args.ConfigureProjectDefinition(*definition);

        if (!definition->Validate())
        {
            std::cerr << "Illegal project definition:\n" << *definition << "\n";
            return;
        }

        std::cout << "Compiling project directory: \"" << directoryObject << "\":\n" << *definition << "\n";

        const auto context = ProjectContext::CreateFromDefinition(directoryObject, *definition);
        Compile(*context);
    }

    void CompileProjectFile(const std::string& fileObject)
    {
        const auto directory = fs::path(fileObject).parent_path();
        const auto definition = ProjectDefinition::DefaultDefinition(directory.string());

        std::ifstream stream(fileObject, std::ios::in | std::ios::binary);
        if (!stream.is_open())
        {
            std::cerr << "Failed to open project file: \"" << fileObject << "\"\n";
            return;
        }

        if (!ProjectDefinitionReader::ReadDefinition(*definition, stream, fileObject))
        {
            std::cerr << "Failed to read project file: \"" << fileObject << "\"\n";
            return;
        }

        m_args.ConfigureProjectDefinition(*definition);

        if (!definition->Validate())
        {
            std::cerr << "Illegal project definition:\n" << *definition << "\n";
            return;
        }

        std::cout << "Compiling project file: \"" << fileObject << "\":\n" << *definition << "\n";

        const auto context = ProjectContext::CreateFromDefinition(directory.string(), *definition);
        Compile(*context);
    }

    void Compile(const ProjectContext& context)
    {
        if (!PrepareContext(context))
        {
            std::cerr << "Failed to prepare context.\n";
            return;
        }
    }

    bool PrepareContext(const ProjectContext& context) const
    {
        if (!fs::is_directory(context.m_data_path))
        {
            std::cerr << "Data directory " << context.m_data_path << " does not exist!\n";
            return false;
        }

        if (!fs::is_directory(context.m_dist_path) && !fs::create_directories(context.m_dist_path))
        {
            std::cerr << "Could not create dist directory " << context.m_dist_path << "!\n";
            return false;
        }

        if (!fs::is_directory(context.m_obj_path) && !fs::create_directories(context.m_obj_path))
        {
            std::cerr << "Could not create obj directory " << context.m_obj_path << "!\n";
            return false;
        }

        return true;
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
