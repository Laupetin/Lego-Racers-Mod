#pragma once

#include "TdbEmitter.h"

#include <istream>

namespace tdb
{
    class TdbBinaryReader
    {
    public:
        TdbBinaryReader() = delete;

        static void Read(std::istream& input, ITdbEmitter& emitter);
    };
} // namespace tdb
