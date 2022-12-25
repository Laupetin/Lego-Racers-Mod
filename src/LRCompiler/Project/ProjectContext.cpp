#include "ProjectContext.h"

namespace fs = std::filesystem;

fs::path CreateProjectContextPath(const fs::path& baseDirectoryPath, const fs::path& specifiedDirectory)
{
    if (specifiedDirectory.is_absolute())
        return specifiedDirectory;

    return fs::absolute(baseDirectoryPath / specifiedDirectory);
}

std::unique_ptr<ProjectContext> ProjectContext::CreateFromDefinition(const std::string& baseDirectory, const ProjectDefinition& definition)
{
    const auto baseDirectoryPath = fs::path(baseDirectory);
    auto context = std::make_unique<ProjectContext>();

    context->m_data_path = CreateProjectContextPath(baseDirectoryPath, definition.m_data_directory);
    context->m_dist_path = CreateProjectContextPath(baseDirectoryPath, definition.m_dist_directory);
    context->m_target_file_path = context->m_dist_path / (definition.m_target_name + ".JAM");
    context->m_obj_path = CreateProjectContextPath(baseDirectoryPath, definition.m_obj_directory);

    return context;
}
