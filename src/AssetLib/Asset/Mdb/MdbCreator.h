#pragma once

#include <string>
#include <iostream>

#include "Asset/IFileTypeProcessor.h"

namespace mdb
{
    class MdbCreator final : public AbstractStreamingFileTypeProcessor
    {
    public:
        [[nodiscard]] bool SupportFileExtension(const std::string& extension) const override;
        void ProcessFile(const std::string& filePath, std::istream& input, std::ostream& output) const override;
    };
}
