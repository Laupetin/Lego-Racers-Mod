#pragma once
#include "Asset/IFileTypeProcessor.h"

class IdbDumper final : public AbstractStreamingFileTypeProcessor
{
public:
    [[nodiscard]] bool SupportFileExtension(const std::string& extension) const override;

protected:
    void ProcessFile(const std::string& filePath, std::istream& input, std::ostream& output) const override;
};
