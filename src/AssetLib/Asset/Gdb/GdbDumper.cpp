#include "GdbDumper.h"

#include "GdbBinaryReader.h"
#include "GdbTextWriter.h"

#include <iostream>

using namespace gdb;

bool GdbDumper::SupportFileExtension(const std::string& extension) const
{
    return extension == ".GDB";
}

void GdbDumper::ProcessFile(const std::string& filePath, std::istream& input, std::ostream& output) const
{
    std::cout << "GDB dumping \"" << filePath << "\"\n";

    const auto writer = GdbTextWriter::Create(output);
    GdbBinaryReader::Read(input, *writer);
}
