#pragma once

#include "GdbEmitter.h"

#include <istream>

namespace gdb
{
    class GdbBinaryReader
    {
    public:
        GdbBinaryReader() = delete;

        static void Read(std::istream& input, IGdbEmitter& emitter);
    };
} // namespace gdb
