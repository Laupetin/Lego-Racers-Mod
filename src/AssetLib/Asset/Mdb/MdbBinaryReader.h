#pragma once

#include "MdbEmitter.h"

#include <istream>

namespace mdb
{
    class MdbBinaryReader
    {
    public:
        MdbBinaryReader() = delete;

        static void Read(std::istream& input, IMdbEmitter& emitter);
    };
} // namespace mdb
