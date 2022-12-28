#pragma once

#include <memory>
#include <ostream>

#include "SrfEmitter.h"

namespace srf
{
    class SrfBinaryWriter
    {
    public:
        SrfBinaryWriter() = delete;

        static std::unique_ptr<ISrfEmitter> Create(std::ostream& stream);
    };
}
