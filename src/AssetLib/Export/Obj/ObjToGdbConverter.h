#pragma once

#include "Asset/Gdb/Gdb.h"
#include "Obj.h"

#include <memory>

namespace obj
{
    class IObjToGdbConverter
    {
    public:
        IObjToGdbConverter() = default;
        virtual ~IObjToGdbConverter() = default;
        IObjToGdbConverter(const IObjToGdbConverter& other) = default;
        IObjToGdbConverter(IObjToGdbConverter&& other) noexcept = default;
        IObjToGdbConverter& operator=(const IObjToGdbConverter& other) = default;
        IObjToGdbConverter& operator=(IObjToGdbConverter&& other) noexcept = default;

        static std::unique_ptr<IObjToGdbConverter> Create(gdb::Model& gdb, const ObjModel& obj, bool hasColors);

        virtual void SetBoneIndexForGroup(std::string groupName, int boneIndex) = 0;
        virtual void Convert() = 0;
    };
} // namespace obj
