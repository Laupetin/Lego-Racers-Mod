#include "IFileTypeDumper.h"

#include <sstream>

void AbstractStreamingFileTypeDumper::DumpFile(const void* inputData, const size_t inputDataSize, std::ostream& output) const
{
    std::istringstream ss(std::string(static_cast<const char*>(inputData), inputDataSize));
    DumpFile(ss, output);
}
