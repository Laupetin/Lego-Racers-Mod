#include "ProjectDefinition.h"

#include <filesystem>
#include <iostream>
#include <nlohmann/json.hpp>

#include "FileUtils.h"
#include "StringUtils.h"

using namespace nlohmann;
namespace fs = std::filesystem;

std::unique_ptr<ProjectDefinition> ProjectDefinition::DefaultDefinition(const std::string& folderPath)
{
    auto definition = std::make_unique<ProjectDefinition>();

    definition->m_data_directory = DEFAULT_DATA_FOLDER;
    definition->m_dist_directory = DEFAULT_DIST_FOLDER;
    definition->m_obj_directory = DEFAULT_OBJ_FOLDER;

    definition->m_target_name = fs::absolute(fs::path(folderPath)).filename().string();
    utils::MakeStringUpperCase(definition->m_target_name);

    return definition;
}

bool ProjectDefinition::Validate() const
{
    if (m_data_directory.find_first_of(utils::ILLEGAL_PATH_CHARS) != std::string::npos)
        return false;

    if (m_dist_directory.find_first_of(utils::ILLEGAL_PATH_CHARS) != std::string::npos)
        return false;

    if (m_obj_directory.find_first_of(utils::ILLEGAL_PATH_CHARS) != std::string::npos)
        return false;

    if (m_target_name.find_first_of(utils::ILLEGAL_FILENAME_CHARS) != std::string::npos)
        return false;

    return true;
}

std::ostream& operator<<(std::ostream& os, const ProjectDefinition& obj)
{
    os << "  Data Directory: \"" << obj.m_data_directory << "\"\n"
        << "  Dist Directory: \"" << obj.m_dist_directory << "\"\n"
        << "  Obj Directory: \"" << obj.m_obj_directory << "\"\n"
        << "  Target Name: \"" << obj.m_target_name << "\"\n";

    return os;
}

class ProjectDefinitionReaderInternal
{
public:
    static bool ReadDefinition(ProjectDefinition& definition, std::istream& stream, const std::string& definitionFilePath)
    {
        SetDefaultTargetNameWhenApplicable(definition, definitionFilePath);

        try
        {
            const auto root = json::parse(stream);

            ReadStringValue(definition.m_data_directory, root, "dataDirectory");
            ReadStringValue(definition.m_dist_directory, root, "distDirectory");
            ReadStringValue(definition.m_obj_directory, root, "objDirectory");
            ReadStringValue(definition.m_target_name, root, "targetName");
        }
        catch (json::parse_error& ex)
        {
            std::cerr << "Failed to parse project file \"" << definitionFilePath << "\": " << ex.what() << "\n";
            return false;
        }

        return true;
    }

private:
    static void SetDefaultTargetNameWhenApplicable(ProjectDefinition& definition, const std::string& definitionFilePath)
    {
        fs::path path(definitionFilePath);

        if (!utils::StringEqualsIgnoreCase(path.extension().string(), ProjectDefinition::PROJ_EXTENSION))
            return;

        path = path.replace_extension();

        definition.m_target_name = path.filename().string();
        utils::MakeStringUpperCase(definition.m_target_name);
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

bool ProjectDefinitionReader::ReadDefinition(ProjectDefinition& definition, std::istream& stream, const std::string& definitionFilePath)
{
    return ProjectDefinitionReaderInternal::ReadDefinition(definition, stream, definitionFilePath);
}
