#pragma once

#include <memory>

#include "GdbEmitter.h"

namespace gdb
{
    class GdbStructWriter
    {
	public:
		GdbStructWriter() = delete;

		static std::unique_ptr<IGdbEmitter> Create(Model& model);
    };
}
