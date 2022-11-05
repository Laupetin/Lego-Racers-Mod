#include "MdbCreator.h"

#include <iostream>

#include "TokenStream.h"
#include "MdbTextReader.h"
#include "MdbBinaryWriter.h"

using namespace mdb;

bool MdbCreator::SupportFileExtension(const std::string& extension) const
{
    return extension == ".MDB";
}

void MdbCreator::ProcessFile(const std::string& filePath, std::istream& input, std::ostream& output) const
{
    std::cout << "Mdb creating \"" << filePath << "\"\n";

    const auto writer = MdbBinaryWriter::Create(output);
    MdbTextReader::Read(input, *writer);

    std::cout << "Successfully created Mdb \"" << filePath << "\"\n";
}
