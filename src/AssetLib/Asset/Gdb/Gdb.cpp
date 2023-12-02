#include "Gdb.h"

#include <cmath>
#include <limits>
#include <tuple>

using namespace gdb;

Vec2::Vec2()
{
    x = 0.0f;
    y = 0.0f;
}

Vec2::Vec2(const float x, const float y)
    : x(x),
      y(y)
{
}

Vec3::Vec3()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

Vec3::Vec3(const float x, const float y, const float z)
    : x(x),
      y(y),
      z(z)
{
}

Color4::Color4()
{
    r = 0;
    g = 0;
    b = 0;
    a = 0;
}

Color4::Color4(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a)
    : r(r),
      g(g),
      b(b),
      a(a)
{
}

ModelFace::ModelFace()
    : m_indices{}
{
}

ModelFace::ModelFace(const unsigned char index0, const unsigned char index1, const unsigned char index2)
    : m_indices{index0, index1, index2}
{
}

Vertex::Vertex(const Vec3 position)
    : m_position(position)
{
}

Vertex::Vertex(const Vec3 position, const Vec2 uv)
    : m_position(position),
      m_uv(uv)
{
}

Vertex::Vertex(const Vec3 position, const Vec2 uv, const Vec3 normal)
    : m_position(position),
      m_uv(uv),
      m_normal(normal)
{
}

Vertex::Vertex(const Vec3 position, const Vec2 uv, const Color4 color)
    : m_position(position),
      m_uv(uv),
      m_color(color)
{
}

Meta::Meta()
    : m_keyword{},
      m_value0(0),
      m_value1(0),
      m_value2(0)
{
}

Meta::Meta(const ModelToken keyword)
    : m_keyword(keyword),
      m_value0(0),
      m_value1(0),
      m_value2(0)
{
}

Meta::Meta(const ModelToken keyword, const int value0)
    : m_keyword(keyword),
      m_value0(value0),
      m_value1(0),
      m_value2(0)
{
}

Meta::Meta(const ModelToken keyword, const int value0, const int value1)
    : m_keyword(keyword),
      m_value0(value0),
      m_value1(value1),
      m_value2(0)
{
}

Meta::Meta(const ModelToken keyword, const int value0, const int value1, const int value2)
    : m_keyword(keyword),
      m_value0(value0),
      m_value1(value1),
      m_value2(value2)
{
}

VertexSelector::VertexSelector()
    : m_shift_forward_count(0u),
      m_vertex_offset(0u),
      m_vertex_count(0u)
{
}

FaceSelector::FaceSelector()
    : m_face_offset(0u),
      m_face_count(0u)
{
}

Model::Model()
    : m_vertex_format(VertexFormat::POSITION),
      m_scale(1.0f)
{
}

namespace gdb
{
    bool operator==(const Vec2& lhs, const Vec2& rhs)
    {
        return std::fabs(lhs.x - rhs.x) < std::numeric_limits<float>::epsilon() && std::fabs(lhs.y - rhs.y) < std::numeric_limits<float>::epsilon();
    }

    bool operator!=(const Vec2& lhs, const Vec2& rhs)
    {
        return !(lhs == rhs);
    }

    bool operator<(const Vec2& lhs, const Vec2& rhs)
    {
        return std::tie(lhs.x, lhs.y) < std::tie(rhs.x, rhs.y);
    }

    bool operator==(const Vec3& lhs, const Vec3& rhs)
    {
        return std::fabs(lhs.x - rhs.x) < std::numeric_limits<float>::epsilon() && std::fabs(lhs.y - rhs.y) < std::numeric_limits<float>::epsilon()
               && std::fabs(lhs.z - rhs.z) < std::numeric_limits<float>::epsilon();
    }

    bool operator!=(const Vec3& lhs, const Vec3& rhs)
    {
        return !(lhs == rhs);
    }

    bool operator<(const Vec3& lhs, const Vec3& rhs)
    {
        return std::tie(lhs.x, lhs.y, lhs.z) < std::tie(rhs.x, rhs.y, rhs.z);
    }

    bool operator==(const Color4& lhs, const Color4& rhs)
    {
        return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a;
    }

    bool operator!=(const Color4& lhs, const Color4& rhs)
    {
        return !(lhs == rhs);
    }

    bool operator<(const Color4& lhs, const Color4& rhs)
    {
        return std::tie(lhs.r, lhs.g, lhs.b, lhs.a) < std::tie(rhs.r, rhs.g, rhs.b, rhs.a);
    }

    bool operator==(const Vertex& lhs, const Vertex& rhs)
    {
        return lhs.m_position == rhs.m_position && lhs.m_uv == rhs.m_uv && lhs.m_normal == rhs.m_normal && lhs.m_color == rhs.m_color;
    }

    bool operator!=(const Vertex& lhs, const Vertex& rhs)
    {
        return !(lhs == rhs);
    }

    bool operator<(const Vertex& lhs, const Vertex& rhs)
    {
        return std::tie(lhs.m_position, lhs.m_uv, lhs.m_normal, lhs.m_color) < std::tie(rhs.m_position, rhs.m_uv, rhs.m_normal, rhs.m_color);
    }
} // namespace gdb

namespace std
{
    std::size_t hash<Vec2>::operator()(const Vec2& vec) const noexcept
    {
        std::size_t seed = 0x6D60F00B;
        seed ^= (seed << 6) + (seed >> 2) + 0x548CF15E + static_cast<std::size_t>(vec.x);
        seed ^= (seed << 6) + (seed >> 2) + 0x30C071D8 + static_cast<std::size_t>(vec.y);
        return seed;
    }

    std::size_t hash<Vec3>::operator()(const Vec3& vec) const noexcept
    {
        std::size_t seed = 0x12B59C4B;
        seed ^= (seed << 6) + (seed >> 2) + 0x31CB4C05 + static_cast<std::size_t>(vec.x);
        seed ^= (seed << 6) + (seed >> 2) + 0x6B860674 + static_cast<std::size_t>(vec.y);
        seed ^= (seed << 6) + (seed >> 2) + 0x40C101B6 + static_cast<std::size_t>(vec.z);
        return seed;
    }

    std::size_t hash<Color4>::operator()(const Color4& clr) const noexcept
    {
        std::size_t seed = 0x1636BDE6;
        seed ^= (seed << 6) + (seed >> 2) + 0x2E6720C3 + static_cast<std::size_t>(clr.r);
        seed ^= (seed << 6) + (seed >> 2) + 0x34D14241 + static_cast<std::size_t>(clr.g);
        seed ^= (seed << 6) + (seed >> 2) + 0x69FD43A9 + static_cast<std::size_t>(clr.b);
        seed ^= (seed << 6) + (seed >> 2) + 0x72091198 + static_cast<std::size_t>(clr.a);
        return seed;
    }

    std::size_t hash<Vertex>::operator()(const Vertex& v) const noexcept
    {
        std::size_t seed = 0x2533342F;
        seed ^= (seed << 6) + (seed >> 2) + 0x413DEC8E + std::hash<Vec3>()(v.m_position);
        seed ^= (seed << 6) + (seed >> 2) + 0x63FE3F0C + std::hash<Vec2>()(v.m_uv);
        seed ^= (seed << 6) + (seed >> 2) + 0x0081E9EA + std::hash<Vec3>()(v.m_normal);
        seed ^= (seed << 6) + (seed >> 2) + 0x6D2F3E3A + std::hash<Color4>()(v.m_color);
        return seed;
    }
} // namespace std
