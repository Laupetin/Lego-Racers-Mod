#pragma once

#include <istream>

#include "TdbEmitter.h"

namespace tdb
{
    class TdbTextReader
    {
    public:
        TdbTextReader() = delete;

        static void Read(std::istream& input, ITdbEmitter& emitter);
    };
}
