#include "ObjImporter.h"

#include "Asset/Gdb/GdbStructReader.h"
#include "Asset/Gdb/GdbTextWriter.h"
#include "Obj.h"
#include "ObjReader.h"
#include "ObjToGdbConverter.h"
#include "ObjWriter.h"

#include <filesystem>
#include <fstream>
#include <iostream>

using namespace obj;

namespace fs = std::filesystem;

namespace obj
{
    std::unique_ptr<gdb::Model> CreateGdbFromObj(const ObjModel& obj, const bool hasColors)
    {
        auto gdb = std::make_unique<gdb::Model>();

        const auto converter = IObjToGdbConverter::Create(*gdb, obj, hasColors);
        converter->Convert();

        return gdb;
    }

    bool WriteGdbFile(const gdb::Model& model, const std::string& directory, const std::string& fileName)
    {
        const fs::path path = (fs::path(directory) / fileName).replace_extension(".GDB");

        std::ofstream outStream(path, std::ios::out | std::ios::binary);
        if (!outStream.is_open())
            return false;

        const auto fileWriter = gdb::GdbTextWriter::Create(outStream);
        gdb::GdbStructReader::Read(model, *fileWriter);

        return true;
    }
} // namespace obj

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

    const auto gdb = CreateGdbFromObj(*model, reader->HasColors());
    if (!gdb)
        return false;

    const auto fileName = fsPath.filename().string();
    if (!WriteGdbFile(*gdb, directory, fileName))
        return false;

    return true;
}
