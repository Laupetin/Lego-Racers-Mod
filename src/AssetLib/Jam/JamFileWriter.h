#pragma once

#include <iostream>

#include "JamTypes.h"

namespace jam
{
    class IJamFileWriter
    {
    public:
        static std::unique_ptr<IJamFileWriter> Create(std::ostream& stream);

        IJamFileWriter() = default;
        virtual ~IJamFileWriter() = default;
        IJamFileWriter(const IJamFileWriter& other) = default;
        IJamFileWriter(IJamFileWriter&& other) noexcept = default;
        IJamFileWriter& operator=(const IJamFileWriter& other) = default;
        IJamFileWriter& operator=(IJamFileWriter&& other) noexcept = default;

        virtual void PrepareDirectoryTree(DirectoryTree& tree) = 0;
        virtual void WriteDataForFile(const jam_id_t& file, std::istream& stream) = 0;
        virtual void WriteMetaData() = 0;
    };
}
