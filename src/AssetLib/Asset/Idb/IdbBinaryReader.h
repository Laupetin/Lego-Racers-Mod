#pragma once

#include "IdbEmitter.h"

#include <istream>

namespace idb
{
    class IdbBinaryReader
    {
    public:
        IdbBinaryReader() = delete;

        static void Read(std::istream& input, IIdbEmitter& emitter);
    };
} // namespace idb
