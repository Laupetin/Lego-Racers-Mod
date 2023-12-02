#pragma once

#include "GdbEmitter.h"
#include "Utils/AbstractTextDumper.h"

#include <memory>
#include <ostream>

namespace gdb
{
    class GdbBinaryWriter
    {
    public:
        GdbBinaryWriter() = delete;

        static std::unique_ptr<IGdbEmitter> Create(std::ostream& stream);
    };
} // namespace gdb
