#include "TdbDumper.h"

#include "TdbBinaryReader.h"
#include "TdbTextWriter.h"

#include <iostream>

using namespace tdb;

bool TdbDumper::SupportFileExtension(const std::string& extension) const
{
    return extension == ".TDB";
}

void TdbDumper::ProcessFile(const std::string& filePath, std::istream& input, std::ostream& output) const
{
    std::cout << "TDB dumping \"" << filePath << "\"\n";

    const auto writer = TdbTextWriter::Create(output);
    TdbBinaryReader::Read(input, *writer);
}
