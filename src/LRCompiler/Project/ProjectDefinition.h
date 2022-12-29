#pragma once

#include <iostream>
#include <memory>
#include <ostream>
#include <string>

class ProjectDefinition
{
public:
    static constexpr auto DEFAULT_DATA_FOLDER = "data";
    static constexpr auto DEFAULT_DIST_FOLDER = "dist";
    static constexpr auto DEFAULT_OBJ_FOLDER = "obj";
    static constexpr auto PROJ_EXTENSION = ".lrproj";

    std::string m_project_name;
    std::string m_data_directory;
    std::string m_dist_directory;
    std::string m_obj_directory;
    std::string m_target_name;

    static std::unique_ptr<ProjectDefinition> DefaultDefinition(const std::string& folderPath);
    bool Validate() const;
    friend std::ostream& operator<<(std::ostream& os, const ProjectDefinition& obj);
};

class ProjectDefinitionReader
{
public:
    static bool ReadDefinition(ProjectDefinition& definition, std::istream& stream, const std::string& definitionFilePath);
};
