#pragma once

#include "TdbEmitter.h"

#include <istream>

namespace tdb
{
    class TdbTextReader
    {
    public:
        TdbTextReader() = delete;

        static void Read(std::istream& input, ITdbEmitter& emitter);
    };
} // namespace tdb
