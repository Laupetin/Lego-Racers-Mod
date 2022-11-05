#pragma once

#include <istream>

#include "MdbEmitter.h"

namespace mdb
{
    class MdbBinaryReader
    {
	public:
		MdbBinaryReader() = delete;

		static void Read(std::istream& input, IMdbEmitter& emitter);
    };
}