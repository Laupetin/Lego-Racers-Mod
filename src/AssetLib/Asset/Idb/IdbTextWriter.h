#pragma once

#include <memory>
#include <ostream>

#include "IdbEmitter.h"

namespace idb
{
    class IdbTextWriter
    {
    public:
        IdbTextWriter() = delete;

        static std::unique_ptr<IIdbEmitter> Create(std::ostream& out);
    };
}
