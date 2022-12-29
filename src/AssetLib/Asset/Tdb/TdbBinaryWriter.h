#pragma once

#include <memory>
#include <ostream>

#include "TdbEmitter.h"

namespace tdb
{
    class TdbBinaryWriter
    {
    public:
        TdbBinaryWriter() = delete;

        static std::unique_ptr<ITdbEmitter> Create(std::ostream& stream);
    };
}
