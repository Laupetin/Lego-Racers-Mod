#pragma once

#include "GdbEmitter.h"

#include <istream>

namespace gdb
{
    class GdbTextReader
    {
    public:
        GdbTextReader() = delete;

        static void Read(std::istream& input, IGdbEmitter& emitter);
    };
} // namespace gdb
