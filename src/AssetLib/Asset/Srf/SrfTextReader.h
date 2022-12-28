#pragma once

#include <istream>

#include "SrfEmitter.h"

namespace srf
{
    class SrfTextReader
    {
    public:
        SrfTextReader() = delete;

        static void Read(std::istream& input, ISrfEmitter& emitter);
    };
}
