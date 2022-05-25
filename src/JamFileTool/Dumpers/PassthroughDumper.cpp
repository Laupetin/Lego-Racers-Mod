#include "PassthroughDumper.h"

bool PassthroughDumper::SupportFileExtension(const std::string& extension) const
{
    return true;
}

void PassthroughDumper::DumpFile(const void* inputData, const size_t inputDataSize, std::ostream& output) const
{
    output.write(static_cast<const char*>(inputData), inputDataSize);
}
