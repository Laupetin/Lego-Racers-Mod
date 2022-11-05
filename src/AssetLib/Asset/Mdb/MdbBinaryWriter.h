#pragma once

#include "MdbEmitter.h"
#include "Utils/AbstractTextDumper.h"

namespace mdb
{
    class MdbBinaryWriter
    {
    public:
        MdbBinaryWriter() = delete;

        static std::unique_ptr<IMdbEmitter> Create(std::ostream& stream);
    };
}
