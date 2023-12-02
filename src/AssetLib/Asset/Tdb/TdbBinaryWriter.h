#pragma once

#include "TdbEmitter.h"

#include <memory>
#include <ostream>

namespace tdb
{
    class TdbBinaryWriter
    {
    public:
        TdbBinaryWriter() = delete;

        static std::unique_ptr<ITdbEmitter> Create(std::ostream& stream);
    };
} // namespace tdb
