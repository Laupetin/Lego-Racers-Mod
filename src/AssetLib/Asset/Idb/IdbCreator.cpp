#include "IdbCreator.h"

#include "IdbBinaryWriter.h"
#include "IdbTextReader.h"
#include "TokenStream.h"

#include <iostream>

using namespace idb;

bool IdbCreator::SupportFileExtension(const std::string& extension) const
{
    return extension == ".IDB";
}

void IdbCreator::ProcessFile(const std::string& filePath, std::istream& input, std::ostream& output) const
{
    std::cout << "Idb creating \"" << filePath << "\"\n";

    const auto writer = IdbBinaryWriter::Create(output);
    IdbTextReader::Read(input, *writer);

    std::cout << "Successfully created Idb \"" << filePath << "\"\n";
}
