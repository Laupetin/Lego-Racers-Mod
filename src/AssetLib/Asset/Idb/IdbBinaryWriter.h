#pragma once

#include "IdbEmitter.h"

#include <memory>
#include <ostream>

namespace idb
{
    class IdbBinaryWriter
    {
    public:
        IdbBinaryWriter() = delete;

        static std::unique_ptr<IIdbEmitter> Create(std::ostream& stream);
    };
} // namespace idb
