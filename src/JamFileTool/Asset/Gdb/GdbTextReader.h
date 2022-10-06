#pragma once

#include <istream>

#include "GdbEmitter.h"

namespace gdb
{
	class GdbTextReader
	{
	public:
		static void Read(std::istream& input, IGdbEmitter& emitter);

	private:
		GdbTextReader() = delete;
	};
}