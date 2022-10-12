#pragma once

#include "Gdb.h"
#include "GdbEmitter.h"

namespace gdb
{
	class GdbStructReader
	{
	public:
		static void Read(const Model& model, IGdbEmitter& emitter);

	private:
		GdbStructReader() = delete;
	};
}