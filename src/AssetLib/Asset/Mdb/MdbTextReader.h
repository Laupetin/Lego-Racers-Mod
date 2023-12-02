#pragma once

#include "MdbEmitter.h"

#include <istream>

namespace mdb
{
    class MdbTextReader
    {
    public:
        MdbTextReader() = delete;

        static void Read(std::istream& input, IMdbEmitter& emitter);
    };
} // namespace mdb
