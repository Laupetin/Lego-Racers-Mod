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
        TOKEN_META_ADD_VERTICES = 0x31,
        TOKEN_META_32 = 0x32,
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

        Vec2()
        {
            x = 0.0f;
            y = 0.0f;
        }
    };

    struct Vec3
    {
        float x;
        float y;
        float z;

        Vec3()
        {
            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
        }
    };

    struct Color4
    {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;

        Color4()
        {
            r = 0;
            g = 0;
            b = 0;
            a = 0;
        }
    };

    struct ModelFace
    {
        unsigned char m_indices[3];

        ModelFace()
            : m_indices{}
        {
        }

        ModelFace(const unsigned char index0, const unsigned char index1, const unsigned char index2)
            : m_indices{index0, index1, index2}
        {
        }
    };

    struct Vertex
    {
        Vec3 m_position;
        Vec2 m_uv;
        Vec3 m_normal;
        Color4 m_color;

        Vertex() = default;

        explicit Vertex(const Vec3 position)
            : m_position(position)
        {
        }

        Vertex(const Vec3 position, const Vec2 uv)
            : m_position(position),
              m_uv(uv)
        {
        }

        Vertex(const Vec3 position, const Vec2 uv, const Vec3 normal)
            : m_position(position),
              m_uv(uv),
              m_normal(normal)
        {
        }

        Vertex(const Vec3 position, const Vec2 uv, const Color4 color)
            : m_position(position),
              m_uv(uv),
              m_color(color)
        {
        }
    };

    struct Meta
    {
        ModelToken m_keyword;
        int m_value0;
        int m_value1;
        int m_value2;

        Meta()
            : m_keyword{},
              m_value0(0),
              m_value1(0),
              m_value2(0)
        {
        }

        explicit Meta(const ModelToken keyword)
            : m_keyword(keyword),
              m_value0(0),
              m_value1(0),
              m_value2(0)
        {
        }

        Meta(const ModelToken keyword, const int value0)
            : m_keyword(keyword),
              m_value0(value0),
              m_value1(0),
              m_value2(0)
        {
        }

        Meta(const ModelToken keyword, const int value0, const int value1)
            : m_keyword(keyword),
              m_value0(value0),
              m_value1(value1),
              m_value2(0)
        {
        }

        Meta(const ModelToken keyword, const int value0, const int value1, const int value2)
            : m_keyword(keyword),
              m_value0(value0),
              m_value1(value1),
              m_value2(value2)
        {
        }
    };

    struct Model
    {
        std::vector<std::string> m_materials;
        VertexFormat m_vertex_format;
        std::vector<Vertex> m_vertices;
        std::vector<ModelFace> m_faces;
        std::vector<Meta> m_meta;
        float m_scale;

        Model()
            : m_vertex_format(VertexFormat::POSITION),
              m_scale(1.0f)
        {
        }
    };
}
