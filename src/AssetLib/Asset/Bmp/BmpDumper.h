#pragma once

#include <cstddef>
#include <string>
#include <ostream>

#include "Asset/IFileTypeProcessor.h"

namespace bmp
{
    class BmpDumper final : public IFileTypeProcessor
    {
    public:
        [[nodiscard]] bool SupportFileExtension(const std::string& extension) const override;
        void ProcessFile(const std::string& filePath, const void* inputData, size_t inputDataSize, std::ostream& output) const override;
    };
}
