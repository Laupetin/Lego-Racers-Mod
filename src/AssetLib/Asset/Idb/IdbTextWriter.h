#pragma once

#include "IdbEmitter.h"

#include <memory>
#include <ostream>

namespace idb
{
    class IdbTextWriter
    {
    public:
        IdbTextWriter() = delete;

        static std::unique_ptr<IIdbEmitter> Create(std::ostream& out);
    };
} // namespace idb
