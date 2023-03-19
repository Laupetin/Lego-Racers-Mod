#pragma once

#include <memory>
#include <ostream>

#include "IdbEmitter.h"

namespace idb
{
    class IdbBinaryWriter
    {
    public:
        IdbBinaryWriter() = delete;

        static std::unique_ptr<IIdbEmitter> Create(std::ostream& stream);
    };
}
