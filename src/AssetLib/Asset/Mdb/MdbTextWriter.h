#pragma once

#include <memory>
#include <ostream>

#include "MdbEmitter.h"

namespace mdb
{
    class MdbTextWriter
    {
    public:
        MdbTextWriter() = delete;

        static std::unique_ptr<IMdbEmitter> Create(std::ostream& out);
    };
}
