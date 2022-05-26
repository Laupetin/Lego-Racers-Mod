#include "PassthroughCreator.h"

#include <iostream>

bool PassthroughCreator::SupportFileExtension(const std::string& extension) const
{
    return true;
}

void PassthroughCreator::ProcessFile(const std::string& filePath, const void* inputData, const size_t inputDataSize, std::ostream& output) const
{
    std::cout << "Passthrough creating \"" << filePath << "\"\n";
    output.write(static_cast<const char*>(inputData), inputDataSize);
}
