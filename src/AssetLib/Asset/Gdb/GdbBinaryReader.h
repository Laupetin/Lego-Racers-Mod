#pragma once

#include <istream>

#include "GdbEmitter.h"

namespace gdb
{
	class GdbBinaryReader
	{
	public:
		static void Read(std::istream& input, IGdbEmitter& emitter);

	private:
		GdbBinaryReader() = delete;
	};
}