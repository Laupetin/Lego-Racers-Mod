#pragma once

#include "Gdb.h"
#include "GdbEmitter.h"

namespace gdb
{
	class GdbStructReader
	{
	public:
		GdbStructReader() = delete;

		static void Read(const Model& model, IGdbEmitter& emitter);
	};
}