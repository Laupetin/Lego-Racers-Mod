#pragma once

#include <memory>
#include <ostream>

#include "TdbEmitter.h"

namespace tdb
{
    class TdbTextWriter
    {
    public:
        TdbTextWriter() = delete;

        static std::unique_ptr<ITdbEmitter> Create(std::ostream& out);
    };
}
