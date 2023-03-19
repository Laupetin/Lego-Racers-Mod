#pragma once

#include <istream>

#include "IdbEmitter.h"

namespace idb
{
    class IdbBinaryReader
    {
    public:
        IdbBinaryReader() = delete;

        static void Read(std::istream& input, IIdbEmitter& emitter);
    };
}
