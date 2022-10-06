#include "GdbCreator.h"

#include <iostream>
#include <sstream>

#include "TokenStream.h"
#include "GdbTextReader.h"
#include "GdbBinaryWriter.h"

using namespace gdb;

bool GdbCreator::SupportFileExtension(const std::string& extension) const
{
    return extension == ".GDB";
}

void GdbCreator::ProcessFile(const std::string& filePath, std::istream& input, std::ostream& output) const
{
    std::cout << "Gdb creating \"" << filePath << "\"\n";

    const auto writer = GdbBinaryWriter::Create(output);
    GdbTextReader::Read(input, *writer);

    std::cout << "Successfully created Gdb \"" << filePath << "\"\n";
}
