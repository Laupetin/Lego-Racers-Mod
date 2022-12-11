#pragma once

#include <string>
#include <vector>

namespace gdb
{
    enum ModelToken
    {
        TOKEN_SECTION_MATERIAL = 0x27,
        TOKEN_SECTION_VERTEX_WITH_POSITION_UV = 0x28,
        TOKEN_SECTION_VERTEX_WITH_POSITION_UV_NORMAL = 0x29,
        TOKEN_SECTION_VERTEX_WITH_POSITION_UV_COLOR = 0x2A,
        TOKEN_SECTION_INDICES = 0x2D,
        TOKEN_SECTION_VERTEX_META = 0x2E,
        TOKEN_META_NEW_OBJECT = 0x27,
        TOKEN_META_FACES = 0x2D,
        TOKEN_META_2F = 0x2F,
        TOKEN_META_30 = 0x30,
        TOKEN_META_VERTICES = 0x31,
        TOKEN_META_32 = 0x32,    // Set Bone or something
        TOKEN_SCALE = 0x33,
        TOKEN_SECTION_VERTEX_WITH_POSITION = 0x34,
    };

    enum class VertexFormat
    {
        POSITION,
        POSITION_UV,
        POSITION_UV_COLOR,
        POSITION_UV_NORMAL
    };

    struct Vec2
    {
        float x;
        float y;

        Vec2();
        Vec2(float x, float y);

        friend bool operator==(const Vec2& lhs, const Vec2& rhs);
        friend bool operator!=(const Vec2& lhs, const Vec2& rhs);
        friend bool operator<(const Vec2& lhs, const Vec2& rhs);
    };

    struct Vec3
    {
        float x;
        float y;
        float z;

        Vec3();
        Vec3(float x, float y, float z);

        friend bool operator==(const Vec3& lhs, const Vec3& rhs);
        friend bool operator!=(const Vec3& lhs, const Vec3& rhs);
        friend bool operator<(const Vec3& lhs, const Vec3& rhs);
    };

    struct Color4
    {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;

        Color4();
        Color4(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

        friend bool operator==(const Color4& lhs, const Color4& rhs);
        friend bool operator!=(const Color4& lhs, const Color4& rhs);
        friend bool operator<(const Color4& lhs, const Color4& rhs);
    };

    struct ModelFace
    {
        unsigned char m_indices[3];

        ModelFace();
        ModelFace(unsigned char index0, unsigned char index1, unsigned char index2);
    };

    struct Vertex
    {
        Vec3 m_position;
        Vec2 m_uv;
        Vec3 m_normal;
        Color4 m_color;

        Vertex() = default;

        explicit Vertex(Vec3 position);
        Vertex(Vec3 position, Vec2 uv);
        Vertex(Vec3 position, Vec2 uv, Vec3 normal);
        Vertex(Vec3 position, Vec2 uv, Color4 color);

        friend bool operator==(const Vertex& lhs, const Vertex& rhs);
        friend bool operator!=(const Vertex& lhs, const Vertex& rhs);
        friend bool operator<(const Vertex& lhs, const Vertex& rhs);
    };

    struct Meta
    {
        ModelToken m_keyword;
        int m_value0;
        int m_value1;
        int m_value2;

        Meta();
        explicit Meta(ModelToken keyword);
        Meta(ModelToken keyword, int value0);
        Meta(ModelToken keyword, int value0, int value1);
        Meta(ModelToken keyword, int value0, int value1, int value2);
    };

    struct VertexSelector
    {
        size_t m_shift_forward_count;
        size_t m_vertex_offset;
        size_t m_vertex_count;

        VertexSelector();
    };

    struct FaceSelector
    {
        size_t m_face_offset;
        size_t m_face_count;

        FaceSelector();
    };

    struct Model
    {
        std::vector<std::string> m_materials;
        VertexFormat m_vertex_format;
        std::vector<Vertex> m_vertices;
        std::vector<ModelFace> m_faces;
        std::vector<Meta> m_meta;
        float m_scale;

        Model();
    };
}

template <>
struct std::hash<gdb::Vec2>
{
    std::size_t operator()(const gdb::Vec2& vec) const noexcept;
};

template <>
struct std::hash<gdb::Vec3>
{
    std::size_t operator()(const gdb::Vec3& vec) const noexcept;
};

template <>
struct std::hash<gdb::Color4>
{
    std::size_t operator()(const gdb::Color4& clr) const noexcept;
};

template <>
struct std::hash<gdb::Vertex>
{
    std::size_t operator()(const gdb::Vertex& v) const noexcept;
};
