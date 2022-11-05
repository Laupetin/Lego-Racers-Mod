#pragma once

#include "GdbEmitter.h"
#include "Utils/AbstractTextDumper.h"

namespace gdb
{
	class GdbTextWriter
	{
	public:
		GdbTextWriter() = delete;

		static std::unique_ptr<IGdbEmitter> Create(std::ostream& out);
	};
}