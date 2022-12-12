#pragma once
#include <cstdint>

#include "FileUtils.h"

static constexpr uint32_t JAM_FILE_MAGIC = utils::MakeMagic32('L', 'J', 'A', 'M');

struct JamFileDiskFile
{
    char fileName[12];
    uint32_t dataOffset;
    uint32_t dataSize;
};

static_assert(sizeof(JamFileDiskFile) == 0x14);

struct JamFileDiskDirectory
{
    char directoryName[12];
    uint32_t dataOffset;
};

static_assert(sizeof(JamFileDiskDirectory) == 0x10);