#pragma once

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
        TOKEN_META_27 = 0x27,
        TOKEN_META_2D = 0x2D,
        TOKEN_META_2F = 0x2F,
        TOKEN_META_30 = 0x30,
        TOKEN_META_31 = 0x31,
        TOKEN_META_32 = 0x32,
        TOKEN_SCALE = 0x33,
        TOKEN_SECTION_VERTEX_WITH_POSITION = 0x34,
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
		unsigned char indices[4];

		ModelFace()
			: indices{}
		{
		}
	};

	struct Vertex
	{
		Vec3 m_position;
		Vec2 m_uv;
		Vec3 m_normal;
		Color4 m_color;
	};
}