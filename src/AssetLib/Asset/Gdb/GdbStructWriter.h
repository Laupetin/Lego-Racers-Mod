#pragma once

#include "GdbEmitter.h"

#include <memory>

namespace gdb
{
    class GdbStructWriter
    {
    public:
        GdbStructWriter() = delete;

        static std::unique_ptr<IGdbEmitter> Create(Model& model);
    };
} // namespace gdb
