#include "ObjExporter.h"

#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

using namespace obj;

bool ObjExporter::SupportsExtension(const std::string& extensionName) const
{
    return extensionName == ".GDB";
}

bool ObjExporter::Convert(const std::string& directory, const std::string& filePath)
{
    const fs::path fsPath(filePath);
    if (!fs::is_regular_file(fsPath))
    {
        std::cerr << "Not a valid file: \"" << fsPath << "\"\n";
        return false;
    }

    fs::path outPath = fs::path(directory) / fsPath.filename();
    outPath.replace_extension(".OBJ");
    std::ofstream out(outPath, std::ios::out | std::ios::binary);
    if (!out.is_open())
    {
        std::cerr << "Failed to open output file: \"" << outPath << "\"\n";
        return false;
    }

    return true;
}
