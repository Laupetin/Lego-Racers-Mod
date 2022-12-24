#pragma once

#include <istream>
#include <memory>
#include <string>

class ProjectTargetDefinition
{
public:
    std::string m_name;
};

class ProjectDefinition
{
public:
    ProjectTargetDefinition m_target;
};

class ProjectDefinitionReader
{
public:
    static std::unique_ptr<ProjectDefinition> ReadDefinition(std::istream& stream, const std::string& filePath);
};