#pragma once

#include "ProjectDefinition.h"

#include <filesystem>
#include <memory>

class ProjectContext
{
public:
    static std::unique_ptr<ProjectContext> CreateFromDefinition(const std::string& baseDirectory, const ProjectDefinition& definition);

    std::string m_project_name;
    std::filesystem::path m_data_path;
    std::filesystem::path m_dist_path;
    std::filesystem::path m_target_file_path;
    std::filesystem::path m_obj_path;
};
