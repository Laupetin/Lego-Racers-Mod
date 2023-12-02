#pragma once

#include "SrfEmitter.h"

#include <istream>

namespace srf
{
    class SrfBinaryReader
    {
    public:
        SrfBinaryReader() = delete;

        static void Read(std::istream& input, ISrfEmitter& emitter);
    };
} // namespace srf
