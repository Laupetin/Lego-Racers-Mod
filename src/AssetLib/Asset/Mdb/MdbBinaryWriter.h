#pragma once

#include <memory>
#include <ostream>

#include "MdbEmitter.h"

namespace mdb
{
    class MdbBinaryWriter
    {
    public:
        MdbBinaryWriter() = delete;

        static std::unique_ptr<IMdbEmitter> Create(std::ostream& stream);
    };
}
