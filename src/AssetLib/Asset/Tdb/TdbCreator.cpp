#include "TdbCreator.h"

#include <iostream>

#include "TokenStream.h"
#include "TdbTextReader.h"
#include "TdbBinaryWriter.h"

using namespace tdb;

bool TdbCreator::SupportFileExtension(const std::string& extension) const
{
    return extension == ".TDB";
}

void TdbCreator::ProcessFile(const std::string& filePath, std::istream& input, std::ostream& output) const
{
    std::cout << "Tdb creating \"" << filePath << "\"\n";

    const auto writer = TdbBinaryWriter::Create(output);
    TdbTextReader::Read(input, *writer);

    std::cout << "Successfully created Tdb \"" << filePath << "\"\n";
}
