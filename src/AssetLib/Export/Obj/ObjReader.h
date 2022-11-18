#pragma once

#include <istream>
#include <memory>

#include "Obj.h"

namespace obj
{
    class ObjReader
    {
    public:
        ObjReader() = default;
        virtual ~ObjReader() = default;
        ObjReader(const ObjReader& other) = default;
        ObjReader(ObjReader&& other) noexcept = default;
        ObjReader& operator=(const ObjReader& other) = default;
        ObjReader& operator=(ObjReader&& other) noexcept = default;

        static std::unique_ptr<ObjReader> Create(std::istream& in);

        virtual std::unique_ptr<ObjModel> ReadModel() = 0;
    };
}