#pragma once

#include <istream>

#include "IdbEmitter.h"

namespace idb
{
    class IdbTextReader
    {
    public:
        IdbTextReader() = delete;

        static void Read(std::istream& input, IIdbEmitter& emitter);
    };
}
