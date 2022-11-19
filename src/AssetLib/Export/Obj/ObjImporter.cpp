#include "ObjImporter.h"

#include <fstream>
#include <iostream>
#include <filesystem>

#include "Obj.h"
#include "ObjReader.h"
#include "Asset/Gdb/Gdb.h"

using namespace obj;

namespace fs = std::filesystem;

namespace obj
{
    std::unique_ptr<gdb::Model> CreateGdbFromObj(const ObjModel& obj)
    {
        return nullptr;
    }

    bool WriteGdbFile(const gdb::Model& model, const std::string& directory, const std::string& fileName)
    {
        return false;
    }
}

bool ObjImporter::SupportsExtension(const std::string& extensionName) const
{
    return extensionName == ".OBJ";
}

bool ObjImporter::Convert(const std::string& directory, const std::string& filePath)
{
    const fs::path fsPath = fs::path(directory) / filePath;
    if (!fs::is_regular_file(fsPath))
    {
        std::cerr << "Not a valid file: \"" << fsPath.string() << "\"\n";
        return false;
    }

    std::ifstream in(fsPath, std::ios::in | std::ios::binary);
    if (!in.is_open())
    {
        std::cerr << "Failed to open obj: \"" << fsPath.string() << "\"\n";
        return false;
    }

    const auto reader = ObjReader::Create(in);
    const auto model = reader->ReadModel();
    if (!model)
    {
        std::cerr << "Error while reading obj: \"" << fsPath.string() << "\"\n";
        return false;
    }

    const auto gdb = CreateGdbFromObj(*model);
    if (!gdb)
        return false;

    const auto fileName = fsPath.filename().string();
    if (!WriteGdbFile(*gdb, directory, fileName))
        return false;

    return true;
}
