#pragma once

#include <istream>

#include "GdbEmitter.h"

namespace gdb
{
	class GdbBinaryReader
	{
	public:
		GdbBinaryReader() = delete;

		static void Read(std::istream& input, IGdbEmitter& emitter);
	};
}