#pragma once

#include "MdbEmitter.h"
#include "Utils/AbstractTextDumper.h"

namespace mdb
{
	class MdbTextWriter
	{
	public:
		MdbTextWriter() = delete;

		static std::unique_ptr<IMdbEmitter> Create(std::ostream& out);
	};
}