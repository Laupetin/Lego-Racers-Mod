#pragma once

#include "Asset/Mdb/MdbEmitter.h"
#include "Obj.h"

#include <memory>
#include <vector>

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
} // namespace obj
