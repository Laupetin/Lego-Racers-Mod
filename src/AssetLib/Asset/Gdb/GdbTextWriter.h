#pragma once

#include "GdbEmitter.h"

#include <memory>
#include <ostream>

namespace gdb
{
    class GdbTextWriter
    {
    public:
        GdbTextWriter() = delete;

        static std::unique_ptr<IGdbEmitter> Create(std::ostream& out);
    };
} // namespace gdb
