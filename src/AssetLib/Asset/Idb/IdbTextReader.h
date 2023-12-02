#pragma once

#include "IdbEmitter.h"

#include <istream>

namespace idb
{
    class IdbTextReader
    {
    public:
        IdbTextReader() = delete;

        static void Read(std::istream& input, IIdbEmitter& emitter);
    };
} // namespace idb
