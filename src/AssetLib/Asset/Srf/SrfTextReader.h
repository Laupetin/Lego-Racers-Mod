#pragma once

#include "SrfEmitter.h"

#include <istream>

namespace srf
{
    class SrfTextReader
    {
    public:
        SrfTextReader() = delete;

        static void Read(std::istream& input, ISrfEmitter& emitter);
    };
} // namespace srf
