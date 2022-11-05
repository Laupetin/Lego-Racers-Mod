#pragma once

#include <string>
#include <vector>

namespace obj
{
    class ObjVertex
    {
    public:
        ObjVertex();
        ObjVertex(float x, float y, float z);

        friend bool operator==(const ObjVertex& lhs, const ObjVertex& rhs);
        friend bool operator!=(const ObjVertex& lhs, const ObjVertex& rhs);
        friend bool operator<(const ObjVertex& lhs, const ObjVertex& rhs);

        float m_coordinates[3];
    };

    class ObjNormal
    {
    public:
        ObjNormal();
        ObjNormal(float x, float y, float z);

        friend bool operator==(const ObjNormal& lhs, const ObjNormal& rhs);
        friend bool operator!=(const ObjNormal& lhs, const ObjNormal& rhs);
        friend bool operator<(const ObjNormal& lhs, const ObjNormal& rhs);

        float m_normal[3];
    };

    class ObjUv
    {
    public:
        ObjUv();
        ObjUv(float u, float v);

        friend bool operator==(const ObjUv& lhs, const ObjUv& rhs);
        friend bool operator!=(const ObjUv& lhs, const ObjUv& rhs);
        friend bool operator<(const ObjUv& lhs, const ObjUv& rhs);

        float m_uv[2];
    };

    class ObjFace
    {
    public:
        ObjFace();
        ObjFace(int vertex0, int vertex1, int vertex2);
        ObjFace(int vertex0, int uv0, int vertex1, int uv1, int vertex2, int uv2);
        ObjFace(int vertex0, int uv0, int normal0, int vertex1, int uv1, int normal1, int vertex2, int uv2, int normal2);

        [[nodiscard]] bool HasUv() const;
        [[nodiscard]] bool HasNormals() const;

        int m_vertex_index[3];
        int m_uv_index[3];
        int m_normal_index[3];
    };

    class MtlMaterial
    {
    public:
        MtlMaterial();
        explicit MtlMaterial(std::string materialName);
        MtlMaterial(std::string materialName, std::string colorMapName);

        std::string m_material_name;
        std::string m_color_map_name;
    };

    class ObjObject
    {
    public:
        std::string m_name;
        int m_material_index = -1;
        std::vector<ObjVertex> m_vertices;
        std::vector<ObjNormal> m_normals;
        std::vector<ObjUv> m_uvs;
        std::vector<ObjFace> m_faces;
    };

    class ObjModel
    {
    public:
        std::vector<ObjObject> m_objects;
        std::vector<MtlMaterial> m_materials;
    };
}

namespace std
{
    template <>
    struct hash<obj::ObjVertex>
    {
        std::size_t operator()(const obj::ObjVertex& v) const noexcept;
    };

    template <>
    struct hash<obj::ObjNormal>
    {
        std::size_t operator()(const obj::ObjNormal& n) const noexcept;
    };

    template <>
    struct hash<obj::ObjUv>
    {
        std::size_t operator()(const obj::ObjUv& uv) const noexcept;
    };
}
