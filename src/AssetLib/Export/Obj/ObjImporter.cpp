#include "ObjImporter.h"

using namespace obj;

bool ObjImporter::SupportsExtension(const std::string& extensionName) const
{
    return extensionName == ".OBJ";
}

bool ObjImporter::Convert(const std::string& directory, const std::string& filePath)
{
    return false;
}
