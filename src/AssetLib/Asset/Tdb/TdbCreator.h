#pragma once

#include "Asset/IFileTypeProcessor.h"

#include <iostream>
#include <string>

namespace tdb
{
    class TdbCreator final : public AbstractStreamingFileTypeProcessor
    {
    public:
        [[nodiscard]] bool SupportFileExtension(const std::string& extension) const override;
        void ProcessFile(const std::string& filePath, std::istream& input, std::ostream& output) const override;
    };
} // namespace tdb
