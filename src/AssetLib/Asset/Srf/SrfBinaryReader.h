#pragma once

#include <istream>

#include "SrfEmitter.h"

namespace srf
{
    class SrfBinaryReader
    {
    public:
        SrfBinaryReader() = delete;

        static void Read(std::istream& input, ISrfEmitter& emitter);
    };
}
