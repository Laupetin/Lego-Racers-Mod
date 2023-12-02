#pragma once

#include "TdbEmitter.h"

#include <memory>
#include <ostream>

namespace tdb
{
    class TdbTextWriter
    {
    public:
        TdbTextWriter() = delete;

        static std::unique_ptr<ITdbEmitter> Create(std::ostream& out);
    };
} // namespace tdb
