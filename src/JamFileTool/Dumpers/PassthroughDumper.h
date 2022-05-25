#pragma once
#include "IFileTypeDumper.h"

class PassthroughDumper final : public IFileTypeDumper
{
public:
    [[nodiscard]] bool SupportFileExtension(const std::string& extension) const override;
    void DumpFile(const std::string& filePath, const void* inputData, size_t inputDataSize, std::ostream& output) const override;
};
