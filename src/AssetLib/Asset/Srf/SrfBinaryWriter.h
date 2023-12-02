#pragma once

#include "SrfEmitter.h"

#include <memory>
#include <ostream>

namespace srf
{
    class SrfBinaryWriter
    {
    public:
        SrfBinaryWriter() = delete;

        static std::unique_ptr<ISrfEmitter> Create(std::ostream& stream);
    };
} // namespace srf
