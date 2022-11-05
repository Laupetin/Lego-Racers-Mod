#pragma once

#include <istream>

#include "MdbEmitter.h"

namespace mdb
{
	class MdbTextReader
	{
	public:
		MdbTextReader() = delete;

		static void Read(std::istream& input, IMdbEmitter& emitter);
	};
}