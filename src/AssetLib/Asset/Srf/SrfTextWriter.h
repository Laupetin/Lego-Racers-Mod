#pragma once

#include "SrfEmitter.h"

#include <memory>
#include <ostream>

namespace srf
{
    class SrfTextWriter
    {
    public:
        SrfTextWriter() = delete;

        static std::unique_ptr<ISrfEmitter> Create(std::ostream& out);
    };
} // namespace srf
