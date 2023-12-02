#pragma once

#include "MdbEmitter.h"

#include <memory>
#include <ostream>

namespace mdb
{
    class MdbTextWriter
    {
    public:
        MdbTextWriter() = delete;

        static std::unique_ptr<IMdbEmitter> Create(std::ostream& out);
    };
} // namespace mdb
