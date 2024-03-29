#include "MdbDumper.h"

#include "MdbBinaryReader.h"
#include "MdbTextWriter.h"

#include <iostream>

using namespace mdb;

bool MdbDumper::SupportFileExtension(const std::string& extension) const
{
    return extension == ".MDB";
}

void MdbDumper::ProcessFile(const std::string& filePath, std::istream& input, std::ostream& output) const
{
    std::cout << "MDB dumping \"" << filePath << "\"\n";

    const auto writer = MdbTextWriter::Create(output);
    MdbBinaryReader::Read(input, *writer);
}
