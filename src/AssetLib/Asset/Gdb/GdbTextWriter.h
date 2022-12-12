#pragma once

#include <ostream>
#include <memory>

#include "GdbEmitter.h"

namespace gdb
{
	class GdbTextWriter
	{
	public:
		GdbTextWriter() = delete;

		static std::unique_ptr<IGdbEmitter> Create(std::ostream& out);
	};
}