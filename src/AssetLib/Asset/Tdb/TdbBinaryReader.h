#pragma once

#include <istream>

#include "TdbEmitter.h"

namespace tdb
{
    class TdbBinaryReader
    {
    public:
        TdbBinaryReader() = delete;

        static void Read(std::istream& input, ITdbEmitter& emitter);
    };
}
