#include "ProjectContextCreator.h"

#include <filesystem>
#include <fstream>

#include "StringUtils.h"

namespace fs = std::filesystem;

ProjectContextCreator::ProjectContextCreator(const LRCompilerArgs& args)
    : m_args(args)
{
}

std::vector<std::unique_ptr<ProjectContext>> ProjectContextCreator::CreateContexts(const std::string& projectPath) const
{
    const auto status = fs::status(projectPath);

    if (status.type() == std::filesystem::file_type::directory)
        return CreateContextsForDirectoryOrFiles(projectPath);

    if (status.type() == std::filesystem::file_type::regular)
    {
        std::vector<std::unique_ptr<ProjectContext>> result;
        result.emplace_back(CreateContextForFile(projectPath));
        return result;
    }

    std::cerr << "Could not find project: \"" << projectPath << "\"\n";
    return {};
}

std::vector<std::unique_ptr<ProjectContext>> ProjectContextCreator::CreateContextsForDirectoryOrFiles(const std::string& projectDirectory) const
{
    auto hasProjectFile = false;
    std::vector<std::unique_ptr<ProjectContext>> result;
    for (const auto& file : fs::directory_iterator(projectDirectory))
    {
        if (!file.is_regular_file())
            continue;

        if (!utils::StringEqualsIgnoreCase(file.path().extension().string(), ProjectDefinition::PROJ_EXTENSION))
            continue;

        if (auto fileContext = CreateContextForFile(file.path().string()))
            result.emplace_back(std::move(fileContext));

        hasProjectFile = true;
    }

    if (!hasProjectFile)
    {
        if (auto directoryContext = CreateContextForDirectory(projectDirectory))
        {
            result.emplace_back(std::move(directoryContext));
            return result;
        }
    }

    return result;
}

std::unique_ptr<ProjectContext> ProjectContextCreator::CreateContextForDirectory(const std::string& projectDirectory) const
{
    const auto definition = ProjectDefinition::DefaultDefinition(projectDirectory);
    m_args.ConfigureProjectDefinition(*definition);

    if (!definition->Validate())
    {
        std::cerr << "Illegal project definition:\n" << *definition << "\n";
        return nullptr;
    }

    std::cout << "Opened project directory: \"" << projectDirectory << "\":\n" << *definition << "\n";

    return ProjectContext::CreateFromDefinition(projectDirectory, *definition);
}

std::unique_ptr<ProjectContext> ProjectContextCreator::CreateContextForFile(const std::string& projectFile) const
{
    const auto directory = fs::path(projectFile).parent_path();
    const auto definition = ProjectDefinition::DefaultDefinition(directory.string());
    SetDefaultsFromFileName(*definition, projectFile);

    std::ifstream stream(projectFile, std::ios::in | std::ios::binary);
    if (!stream.is_open())
    {
        std::cerr << "Failed to open project file: \"" << projectFile << "\"\n";
        return nullptr;
    }

    if (!ProjectDefinitionReader::ReadDefinition(*definition, stream, projectFile))
    {
        std::cerr << "Failed to read project file: \"" << projectFile << "\"\n";
        return nullptr;
    }

    m_args.ConfigureProjectDefinition(*definition);

    if (!definition->Validate())
    {
        std::cerr << "Illegal project definition:\n" << *definition << "\n";
        return nullptr;
    }

    std::cout << "Opened project file: \"" << projectFile << "\":\n" << *definition << "\n";

    return ProjectContext::CreateFromDefinition(directory.string(), *definition);
}

void ProjectContextCreator::SetDefaultsFromFileName(ProjectDefinition& definition, const std::string& projectFile)
{
    definition.m_project_name = fs::path(projectFile).filename().replace_extension().string();
    definition.m_target_name = definition.m_project_name;
    utils::MakeStringUpperCase(definition.m_target_name);
}
