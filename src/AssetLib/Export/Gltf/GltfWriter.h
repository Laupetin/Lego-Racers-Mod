#pragma once

#include <ostream>

#include "Export/Obj/Obj.h"

namespace gltf
{
    class GltfWriter
    {
    public:
        GltfWriter() = default;
        virtual ~GltfWriter() = default;
        GltfWriter(const GltfWriter& other) = default;
        GltfWriter(GltfWriter&& other) noexcept = default;
        GltfWriter& operator=(const GltfWriter& other) = default;
        GltfWriter& operator=(GltfWriter&& other) noexcept = default;

        static std::unique_ptr<GltfWriter> Create(const obj::ObjModel& model);

        virtual void ExportColors(bool value) = 0;
        virtual void ExportNormals(bool value) = 0;

        virtual void WriteGltf(std::ostream& out, const std::string& matName) const = 0;
    };
}
