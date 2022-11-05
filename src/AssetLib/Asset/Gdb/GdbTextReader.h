#pragma once

#include <istream>

#include "GdbEmitter.h"

namespace gdb
{
	class GdbTextReader
	{
	public:
		GdbTextReader() = delete;

		static void Read(std::istream& input, IGdbEmitter& emitter);
	};
}