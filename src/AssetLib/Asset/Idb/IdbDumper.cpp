#include "IdbDumper.h"

#include "IdbBinaryReader.h"
#include "IdbTextWriter.h"

#include <iostream>

using namespace idb;

bool IdbDumper::SupportFileExtension(const std::string& extension) const
{
    return extension == ".IDB";
}

void IdbDumper::ProcessFile(const std::string& filePath, std::istream& input, std::ostream& output) const
{
    std::cout << "IDB dumping \"" << filePath << "\"\n";

    const auto writer = IdbTextWriter::Create(output);
    IdbBinaryReader::Read(input, *writer);
}
