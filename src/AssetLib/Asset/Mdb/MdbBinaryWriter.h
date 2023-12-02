#pragma once

#include "MdbEmitter.h"

#include <memory>
#include <ostream>

namespace mdb
{
    class MdbBinaryWriter
    {
    public:
        MdbBinaryWriter() = delete;

        static std::unique_ptr<IMdbEmitter> Create(std::ostream& stream);
    };
} // namespace mdb
