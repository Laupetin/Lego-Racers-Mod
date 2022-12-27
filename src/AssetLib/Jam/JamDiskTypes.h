#pragma once

#include <cstdint>

#include "FileUtils.h"

namespace jam
{
    static constexpr uint32_t JAM_FILE_MAGIC = utils::MakeMagic32('L', 'J', 'A', 'M');

    struct DiskFileEntry
    {
        char fileName[12];
        uint32_t dataOffset;
        uint32_t dataSize;
    };

    static_assert(sizeof(DiskFileEntry) == 0x14);

    struct DiskDirectoryEntry
    {
        char directoryName[12];
        uint32_t dataOffset;
    };

    static_assert(sizeof(DiskDirectoryEntry) == 0x10);
}
