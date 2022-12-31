#include "ObjDeduplicator.h"

#include <cassert>

using namespace obj;

Deduplicator::Deduplicator(const ObjObject& object)
    : m_object(object)
{
}

size_t Deduplicator::IndexForVertex(ObjVertex vertex)
{
    const auto existingVertex = m_previous_vertices.find(vertex);

    if (existingVertex != m_previous_vertices.end())
    {
        return existingVertex->second;
    }

    const auto newIndex = m_deduplicated_object.m_vertices.size();
    m_deduplicated_object.m_vertices.push_back(vertex);
    m_previous_vertices.emplace(vertex, newIndex);

    return newIndex;
}

size_t Deduplicator::IndexForUv(ObjUv uv)
{
    const auto existingUv = m_previous_uvs.find(uv);

    if (existingUv != m_previous_uvs.end())
    {
        return existingUv->second;
    }

    const auto newIndex = m_deduplicated_object.m_uvs.size();
    m_deduplicated_object.m_uvs.push_back(uv);
    m_previous_uvs.emplace(uv, newIndex);

    return newIndex;
}

size_t Deduplicator::IndexForNormal(ObjNormal normal)
{
    const auto existingNormal = m_previous_normals.find(normal);

    if (existingNormal != m_previous_normals.end())
    {
        return existingNormal->second;
    }

    const auto newIndex = m_deduplicated_object.m_normals.size();
    m_deduplicated_object.m_normals.push_back(normal);
    m_previous_normals.emplace(normal, newIndex);

    return newIndex;
}

ObjObject Deduplicator::Deduplicate()
{
    m_deduplicated_object = ObjObject(m_object.m_name, m_object.m_material_index);
    m_deduplicated_object.m_groups = m_object.m_groups;

    for (const auto& face : m_object.m_faces)
    {
        assert(face.m_vertex_index[0] >= 0 && face.m_vertex_index[1] >= 0 && face.m_vertex_index[2] >= 0);

        int indicesForVertices[3]
        {
            static_cast<int>(IndexForVertex(m_object.m_vertices[face.m_vertex_index[0]])),
            static_cast<int>(IndexForVertex(m_object.m_vertices[face.m_vertex_index[1]])),
            static_cast<int>(IndexForVertex(m_object.m_vertices[face.m_vertex_index[2]]))
        };

        if (face.HasUv())
        {
            int indicesForUvs[3]
            {
                static_cast<int>(IndexForUv(m_object.m_uvs[face.m_uv_index[0]])),
                static_cast<int>(IndexForUv(m_object.m_uvs[face.m_uv_index[1]])),
                static_cast<int>(IndexForUv(m_object.m_uvs[face.m_uv_index[2]]))
            };

            if (face.HasNormals())
            {
                int indicesForNormals[3]
                {
                    static_cast<int>(IndexForNormal(m_object.m_normals[face.m_normal_index[0]])),
                    static_cast<int>(IndexForNormal(m_object.m_normals[face.m_normal_index[1]])),
                    static_cast<int>(IndexForNormal(m_object.m_normals[face.m_normal_index[2]]))
                };

                m_deduplicated_object.m_faces.emplace_back(indicesForVertices[0], indicesForUvs[0], indicesForNormals[0],
                                                           indicesForVertices[1], indicesForUvs[1], indicesForNormals[1],
                                                           indicesForVertices[2], indicesForUvs[2], indicesForNormals[2],
                                                           face.m_group);
            }
            else
            {
                m_deduplicated_object.m_faces.emplace_back(indicesForVertices[0], indicesForUvs[0],
                                                           indicesForVertices[1], indicesForUvs[1],
                                                           indicesForVertices[2], indicesForUvs[2],
                                                           face.m_group);
            }
        }
        else
        {
            m_deduplicated_object.m_faces.emplace_back(indicesForVertices[0],
                                                       indicesForVertices[1],
                                                       indicesForVertices[2],
                                                       face.m_group);
        }
    }

    return std::move(m_deduplicated_object);
}
