#include "ProjectDefinition.h"

#include <filesystem>
#include <iostream>
#include <nlohmann/json.hpp>

#include "StringUtils.h"

using namespace nlohmann;
namespace fs = std::filesystem;

class ProjectDefinitionReaderInternal
{
public:
    static std::unique_ptr<ProjectDefinition> ReadDefinition(std::istream& stream, const std::string& filePath)
    {
        try
        {
            const auto root = json::parse(stream);
            auto result = std::make_unique<ProjectDefinition>();

            if (!ParseTargetData(root, *result, filePath))
                return nullptr;

            return result;
        }
        catch (json::parse_error& ex)
        {
            std::cerr << "Failed to parse project file \"" << filePath << "\": " << ex.what() << "\n";
        }

        return nullptr;
    }

    static bool ParseTargetData(const json& root, ProjectDefinition& definition, const std::string& filePath)
    {
        definition.m_target = DefaultTarget(filePath);

        if (!root.contains("target"))
            return true;

        const auto& target = root["target"];
        if (target.empty() || target.is_null())
            return true;

        ReadStringValue(definition.m_target.m_name, target, "targetName");
        utils::MakeStringUpperCase(definition.m_target.m_name);

        return true;
    }

    static ProjectTargetDefinition DefaultTarget(const std::string& filePath)
    {
        ProjectTargetDefinition target;
        target.m_name = fs::path(filePath).filename().replace_extension().string();

        return target;
    }

    static void ReadStringValue(std::string& str, const json& json, const char* propertyName)
    {
        if (!json.contains(propertyName))
            return;

        const auto& property = json[propertyName];
        if (!property.is_string())
            return;

        str = property.get<std::string>();
    }
};

std::unique_ptr<ProjectDefinition> ProjectDefinitionReader::ReadDefinition(std::istream& stream, const std::string& filePath)
{
    return ProjectDefinitionReaderInternal::ReadDefinition(stream, filePath);
}
