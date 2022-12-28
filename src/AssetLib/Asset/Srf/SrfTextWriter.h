#pragma once

#include <memory>
#include <ostream>

#include "SrfEmitter.h"

namespace srf
{
    class SrfTextWriter
    {
    public:
        SrfTextWriter() = delete;

        static std::unique_ptr<ISrfEmitter> Create(std::ostream& out);
    };
}
