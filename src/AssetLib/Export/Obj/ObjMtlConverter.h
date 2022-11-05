#pragma once

#include <memory>
#include <vector>

#include "Obj.h"
#include "Asset/Mdb/MdbEmitter.h"

namespace obj
{
    class IObjMtlConverter : public mdb::IMdbEmitter
    {
    public:
        virtual std::vector<MtlMaterial> RetrieveConvertedMaterials() = 0;
    };

	class ObjMtlConverter
	{
	public:
		ObjMtlConverter() = delete;

		static std::unique_ptr<IObjMtlConverter> Create();
	};
}