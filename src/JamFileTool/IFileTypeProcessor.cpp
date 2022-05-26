#include "IFileTypeProcessor.h"

#include <sstream>

void AbstractStreamingFileTypeProcessor::ProcessFile(const std::string& filePath, const void* inputData, const size_t inputDataSize, std::ostream& output) const
{
    std::istringstream ss(std::string(static_cast<const char*>(inputData), inputDataSize));
    ProcessFile(filePath, ss, output);
}
