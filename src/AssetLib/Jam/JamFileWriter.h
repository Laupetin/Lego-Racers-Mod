#pragma once

#include "JamTypes.h"

#include <iostream>

namespace jam
{
    class IJamFileWriterDataProvider
    {
    public:
        IJamFileWriterDataProvider() = default;
        virtual ~IJamFileWriterDataProvider() = default;
        IJamFileWriterDataProvider(const IJamFileWriterDataProvider& other) = default;
        IJamFileWriterDataProvider(IJamFileWriterDataProvider&& other) noexcept = default;
        IJamFileWriterDataProvider& operator=(const IJamFileWriterDataProvider& other) = default;
        IJamFileWriterDataProvider& operator=(IJamFileWriterDataProvider&& other) noexcept = default;

        virtual std::unique_ptr<std::istream> GetDataForFile(jam_id_t file) = 0;
    };

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

        virtual bool Write(const DirectoryTree& tree, IJamFileWriterDataProvider& provider) = 0;
    };
} // namespace jam
