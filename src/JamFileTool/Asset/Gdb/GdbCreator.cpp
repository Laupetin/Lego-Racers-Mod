#include "GdbCreator.h"

#include <iostream>

#include "Gdb.h"

using namespace gdb;

bool GdbCreator::SupportFileExtension(const std::string& extension) const
{
    return extension == ".GDB";
}

void GdbCreator::ProcessFile(const std::string& filePath, const void* inputData, const size_t inputDataSize, std::ostream& output) const
{
    std::cout << "Gdb creating \"" << filePath << "\"\n";
}
