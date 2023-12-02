#include "Obj.h"

#include <cmath>
#include <limits>
#include <tuple>

using namespace obj;

namespace obj
{
    ObjVertex::ObjVertex()
        : m_coordinates{},
          m_colors{1.0, 1.0, 1.0}
    {
    }

    ObjVertex::ObjVertex(const float x, const float y, const float z)
        : m_coordinates{x, y, z},
          m_colors{1.0, 1.0, 1.0}
    {
    }

    ObjVertex::ObjVertex(const float x, const float y, const float z, const float r, const float g, const float b)
        : m_coordinates{x, y, z},
          m_colors{r, g, b}
    {
    }

    bool operator==(const ObjVertex& lhs, const ObjVertex& rhs)
    {
        return std::fabs(lhs.m_coordinates[0] - rhs.m_coordinates[0]) < std::numeric_limits<float>::epsilon()
               && std::fabs(lhs.m_coordinates[1] - rhs.m_coordinates[1]) < std::numeric_limits<float>::epsilon()
               && std::fabs(lhs.m_coordinates[2] - rhs.m_coordinates[2]) < std::numeric_limits<float>::epsilon()
               && std::fabs(lhs.m_colors[0] - rhs.m_colors[0]) < std::numeric_limits<float>::epsilon()
               && std::fabs(lhs.m_colors[1] - rhs.m_colors[1]) < std::numeric_limits<float>::epsilon()
               && std::fabs(lhs.m_colors[2] - rhs.m_colors[2]) < std::numeric_limits<float>::epsilon();
    }

    bool operator!=(const ObjVertex& lhs, const ObjVertex& rhs)
    {
        return !(lhs == rhs);
    }

    bool operator<(const ObjVertex& lhs, const ObjVertex& rhs)
    {
        return std::tie(lhs.m_coordinates[0], lhs.m_coordinates[1], lhs.m_coordinates[2], lhs.m_colors[0], lhs.m_colors[1], lhs.m_colors[2])
               < std::tie(rhs.m_coordinates[0], rhs.m_coordinates[1], rhs.m_coordinates[2], rhs.m_colors[0], rhs.m_colors[1], rhs.m_colors[2]);
    }

    ObjNormal::ObjNormal()
        : m_normal{}
    {
    }

    ObjNormal::ObjNormal(const float x, const float y, const float z)
        : m_normal{x, y, z}
    {
    }

    bool operator==(const ObjNormal& lhs, const ObjNormal& rhs)
    {
        return std::fabs(lhs.m_normal[0] - rhs.m_normal[0]) < std::numeric_limits<float>::epsilon()
               && std::fabs(lhs.m_normal[1] - rhs.m_normal[1]) < std::numeric_limits<float>::epsilon()
               && std::fabs(lhs.m_normal[2] - rhs.m_normal[2]) < std::numeric_limits<float>::epsilon();
    }

    bool operator!=(const ObjNormal& lhs, const ObjNormal& rhs)
    {
        return !(lhs == rhs);
    }

    bool operator<(const ObjNormal& lhs, const ObjNormal& rhs)
    {
        return std::tie(lhs.m_normal[0], lhs.m_normal[1], lhs.m_normal[2]) < std::tie(rhs.m_normal[0], rhs.m_normal[1], rhs.m_normal[2]);
    }

    ObjUv::ObjUv()
        : m_uv{}
    {
    }

    ObjUv::ObjUv(const float u, const float v)
        : m_uv{u, v}
    {
    }

    bool operator==(const ObjUv& lhs, const ObjUv& rhs)
    {
        return std::fabs(lhs.m_uv[0] - rhs.m_uv[0]) < std::numeric_limits<float>::epsilon()
               && std::fabs(lhs.m_uv[1] - rhs.m_uv[1]) < std::numeric_limits<float>::epsilon();
    }

    bool operator!=(const ObjUv& lhs, const ObjUv& rhs)
    {
        return !(lhs == rhs);
    }

    bool operator<(const ObjUv& lhs, const ObjUv& rhs)
    {
        return std::tie(lhs.m_uv[0], lhs.m_uv[1]) < std::tie(rhs.m_uv[0], rhs.m_uv[1]);
    }

    MtlMaterial::MtlMaterial() = default;

    MtlMaterial::MtlMaterial(std::string materialName)
        : m_material_name(std::move(materialName))
    {
    }

    MtlMaterial::MtlMaterial(std::string materialName, std::string colorMapName)
        : m_material_name(std::move(materialName)),
          m_color_map_name(std::move(colorMapName))
    {
    }

    ObjFace::ObjFace()
        : m_vertex_index{-1, -1, -1},
          m_uv_index{-1, -1, -1},
          m_normal_index{-1, -1, -1},
          m_group(-1)
    {
    }

    ObjFace::ObjFace(const int vertex0, const int vertex1, const int vertex2, const int group)
        : m_vertex_index{vertex0, vertex1, vertex2},
          m_uv_index{-1, -1, -1},
          m_normal_index{-1, -1, -1},
          m_group(group)
    {
    }

    ObjFace::ObjFace(const int vertex0, const int uv0, const int vertex1, const int uv1, const int vertex2, const int uv2, const int group)
        : m_vertex_index{vertex0, vertex1, vertex2},
          m_uv_index{uv0, uv1, uv2},
          m_normal_index{-1, -1, -1},
          m_group(group)
    {
    }

    ObjFace::ObjFace(const int vertex0,
                     const int uv0,
                     const int normal0,
                     const int vertex1,
                     const int uv1,
                     const int normal1,
                     const int vertex2,
                     const int uv2,
                     const int normal2,
                     const int group)
        : m_vertex_index{vertex0, vertex1, vertex2},
          m_uv_index{uv0, uv1, uv2},
          m_normal_index{normal0, normal1, normal2},
          m_group(group)
    {
    }

    bool ObjFace::HasUv() const
    {
        return m_uv_index[0] >= 0 && m_uv_index[1] >= 0 && m_uv_index[2] >= 0;
    }

    bool ObjFace::HasNormals() const
    {
        return m_normal_index[0] >= 0 && m_normal_index[1] >= 0 && m_normal_index[2] >= 0;
    }

    bool ObjFace::HasGroup() const
    {
        return m_group >= 0;
    }

    ObjObject::ObjObject()
        : m_material_index(-1)
    {
    }

    ObjObject::ObjObject(std::string name, const int materialIndex)
        : m_name(std::move(name)),
          m_material_index(materialIndex)
    {
    }
} // namespace obj

std::size_t std::hash<ObjVertex>::operator()(const ObjVertex& v) const noexcept

{
    std::size_t seed = 0x58CACB27;
    seed ^= (seed << 6) + (seed >> 2) + 0x6C7D59B7 + static_cast<std::size_t>(v.m_coordinates[0]);
    seed ^= (seed << 6) + (seed >> 2) + 0x31B8AAE9 + static_cast<std::size_t>(v.m_coordinates[1]);
    seed ^= (seed << 6) + (seed >> 2) + 0x35FC0176 + static_cast<std::size_t>(v.m_coordinates[2]);
    seed ^= (seed << 6) + (seed >> 2) + 0x169940DF + static_cast<std::size_t>(v.m_colors[0]);
    seed ^= (seed << 6) + (seed >> 2) + 0x2025FC20 + static_cast<std::size_t>(v.m_colors[1]);
    seed ^= (seed << 6) + (seed >> 2) + 0x0CFCD4A8 + static_cast<std::size_t>(v.m_colors[2]);
    return seed;
}

std::size_t std::hash<ObjNormal>::operator()(const ObjNormal& n) const noexcept

{
    std::size_t seed = 0x05568BBF;
    seed ^= (seed << 6) + (seed >> 2) + 0x0E4D7D9A + static_cast<std::size_t>(n.m_normal[0]);
    seed ^= (seed << 6) + (seed >> 2) + 0x14785A83 + static_cast<std::size_t>(n.m_normal[1]);
    seed ^= (seed << 6) + (seed >> 2) + 0x43B671FE + static_cast<std::size_t>(n.m_normal[2]);
    return seed;
}

std::size_t std::hash<ObjUv>::operator()(const ObjUv& uv) const noexcept

{
    std::size_t seed = 0x382922E4;
    seed ^= (seed << 6) + (seed >> 2) + 0x3E45615C + static_cast<std::size_t>(uv.m_uv[0]);
    seed ^= (seed << 6) + (seed >> 2) + 0x7481DA41 + static_cast<std::size_t>(uv.m_uv[1]);
    return seed;
}
