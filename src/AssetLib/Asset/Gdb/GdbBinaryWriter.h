#pragma once

#include "GdbEmitter.h"
#include "Utils/AbstractTextDumper.h"

namespace gdb
{
	class GdbBinaryWriter
	{
	public:
		GdbBinaryWriter() = delete;

		static std::unique_ptr<IGdbEmitter> Create(std::ostream& stream);
	};
}