#pragma once
#include "Obj.h"

#include <unordered_map>

namespace obj
{
    class Deduplicator
    {
    public:
        explicit Deduplicator(const ObjObject& object);

        // This removes duplicated uv coordinates, normals and merges vertices with identical positions. Information that is not used by any face is omitted.
        ObjObject Deduplicate();

    private:
        size_t IndexForVertex(ObjVertex vertex);
        size_t IndexForUv(ObjUv uv);
        size_t IndexForNormal(ObjNormal normal);

        const ObjObject& m_object;
        ObjObject m_deduplicated_object;

        std::unordered_map<ObjVertex, size_t> m_previous_vertices;
        std::unordered_map<ObjUv, size_t> m_previous_uvs;
        std::unordered_map<ObjNormal, size_t> m_previous_normals;
    };
} // namespace obj
