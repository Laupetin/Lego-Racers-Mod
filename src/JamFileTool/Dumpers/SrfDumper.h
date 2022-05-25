#pragma once
#include "IFileTypeDumper.h"

class SrfDumper final : public AbstractStreamingFileTypeDumper
{
public:
    [[nodiscard]] bool SupportFileExtension(const std::string& extension) const override;

protected:
    void DumpFile(const std::string& filePath, std::istream& input, std::ostream& output) const override;
};
