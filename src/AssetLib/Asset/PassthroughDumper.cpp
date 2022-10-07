#include "PassthroughDumper.h"

#include <iostream>

bool PassthroughDumper::SupportFileExtension(const std::string& extension) const
{
    return true;
}

void PassthroughDumper::ProcessFile(const std::string& filePath, const void* inputData, const size_t inputDataSize, std::ostream& output) const
{
    std::cout << "Passthrough dumping \"" << filePath << "\"\n";
    output.write(static_cast<const char*>(inputData), inputDataSize);
}
