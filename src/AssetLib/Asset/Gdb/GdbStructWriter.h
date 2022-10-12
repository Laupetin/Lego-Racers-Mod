#pragma once

#include <memory>

#include "GdbEmitter.h"

namespace gdb
{
    class GdbStructWriter
    {
	public:
		static std::unique_ptr<IGdbEmitter> Create(Model& model);

	private:
		GdbStructWriter() = delete;
    };
}
