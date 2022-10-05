#include "GdbDumper.h"

#include <cassert>
#include <iostream>
#include <vector>
#include <array>

#include "Gdb.h"
#include "TokenStream.h"
#include "Utils/AbstractTextDumper.h"

namespace gdb
{
	class GdbDumpingException final : public std::exception
	{
	public:
		explicit GdbDumpingException(char const* msg)
			: exception(msg)
		{
		}
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

using namespace gdb;

class GdbTextOutputStream final : public AbstractTokenTextDumper
{
public:
	GdbTextOutputStream(std::istream& in, std::ostream& out)
		: AbstractTokenTextDumper(out),
		m_tokens(ITokenInputStream::Create(in)),
		m_scale_value(0.0f)
	{
	}

	void Write()
	{
		for (auto nextSectionToken = m_tokens->NextValue(); nextSectionToken.m_type != TOKEN_INVALID && nextSectionToken.m_type != TOKEN_EOF; nextSectionToken = m_tokens->NextValue())
		{
			switch (nextSectionToken.m_type)
			{
			case TOKEN_SECTION_MATERIAL:
				HandleMaterialList();
				break;

			case TOKEN_SECTION_VERTEX_WITH_POSITION_UV:
				LoadVerticesWithPositionAndUv();
				break;

			case TOKEN_SECTION_VERTEX_WITH_POSITION_UV_NORMAL:
				LoadVerticesWithPositionAndUvAndNormal();
				break;

			case TOKEN_SECTION_VERTEX_WITH_POSITION_UV_COLOR:
				LoadVerticesWithPositionAndUvAndColor();
				break;

			case TOKEN_SECTION_INDICES:
				LoadIndices();
				break;

			case TOKEN_SECTION_VERTEX_META:
				LoadVertexMeta();
				break;

			case TOKEN_SCALE:
				LoadScale();
				break;

			case TOKEN_SECTION_VERTEX_WITH_POSITION:
				LoadVerticesWithPosition();
				break;

			default:
				throw GdbDumpingException("Unknown keyword for section");
			}
		}
	}

private:
	void HandleMaterialList()
	{
		m_stream << "materials\n";
		Indent();
		m_stream << "{\n";
		IncIndent();

		const auto materialCount = ReadCountInCurlyBraces();
		for (auto materialIndex = 0; materialIndex < materialCount; materialIndex++)
		{
			auto materialName = m_tokens->NextStringValue();
			Indent();
			m_stream << "\"" << materialName << "\"";

			if (materialIndex + 1 < materialCount)
				m_stream << ',';
			m_stream << '\n';

			m_materials.emplace_back(std::move(materialName));
		}

		m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);

		DecIndent();
		Indent();
		m_stream << "}\n\n";
	}

	void LoadVerticesWithPositionAndUv()
	{
		m_stream << "vertices\n";
		Indent();
		m_stream << "{\n";
		IncIndent();

		assert(m_vertices.empty());
		const auto vertexCount = ReadCountInCurlyBraces();

		m_vertices.resize(vertexCount);
		for (auto index = 0; index < vertexCount; index++)
		{
			Vertex& v = m_vertices[index];
			v.m_position.x = m_tokens->NextFloatValue();
			v.m_position.y = m_tokens->NextFloatValue();
			v.m_position.z = m_tokens->NextFloatValue();

			v.m_uv.x = m_tokens->NextFloatValue();
			v.m_uv.y = m_tokens->NextFloatValue();

			if (index > 0)
				m_stream << "\n";

			Indent();
			m_stream << "v " << v.m_position.x << " " << v.m_position.y << " " << v.m_position.z << "\n";

			Indent();
			m_stream << "uv " << v.m_uv.x << " " << v.m_uv.y << "\n";
		}

		m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);

		DecIndent();
		Indent();
		m_stream << "}\n\n";
	}

	void LoadVerticesWithPositionAndUvAndNormal()
	{
		m_stream << "vertices\n";
		Indent();
		m_stream << "{\n";
		IncIndent();

		assert(m_vertices.empty());
		const auto vertexCount = ReadCountInCurlyBraces();

		m_vertices.resize(vertexCount);
		for (auto index = 0; index < vertexCount; index++)
		{
			Vertex& v = m_vertices[index];
			v.m_position.x = m_tokens->NextFloatValue();
			v.m_position.y = m_tokens->NextFloatValue();
			v.m_position.z = m_tokens->NextFloatValue();

			v.m_uv.x = m_tokens->NextFloatValue();
			v.m_uv.y = m_tokens->NextFloatValue();

			v.m_normal.x = m_tokens->NextFloatValue();
			v.m_normal.y = m_tokens->NextFloatValue();
			v.m_normal.z = m_tokens->NextFloatValue();

			if (index > 0)
				m_stream << "\n";

			Indent();
			m_stream << "v " << v.m_position.x << " " << v.m_position.y << " " << v.m_position.z << "\n";

			Indent();
			m_stream << "uv " << v.m_uv.x << " " << v.m_uv.y << "\n";

			Indent();
			m_stream << "vn " << v.m_normal.x << " " << v.m_normal.y << " " << v.m_normal.z << "\n";
		}

		m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);

		DecIndent();
		Indent();
		m_stream << "}\n\n";
	}

	void LoadVerticesWithPositionAndUvAndColor()
	{
		m_stream << "vertices\n";
		Indent();
		m_stream << "{\n";
		IncIndent();

		assert(m_vertices.empty());
		const auto vertexCount = ReadCountInCurlyBraces();

		m_vertices.resize(vertexCount);
		for (auto index = 0; index < vertexCount; index++)
		{
			Vertex& v = m_vertices[index];
			v.m_position.x = m_tokens->NextFloatValue();
			v.m_position.y = m_tokens->NextFloatValue();
			v.m_position.z = m_tokens->NextFloatValue();

			v.m_uv.x = m_tokens->NextFloatValue();
			v.m_uv.y = m_tokens->NextFloatValue();

			v.m_color.r = m_tokens->NextIntegerValue();
			v.m_color.g = m_tokens->NextIntegerValue();
			v.m_color.b = m_tokens->NextIntegerValue();
			v.m_color.a = m_tokens->NextIntegerValue();

			if (index > 0)
				m_stream << "\n";

			Indent();
			m_stream << "v " << v.m_position.x << " " << v.m_position.y << " " << v.m_position.z << "\n";

			Indent();
			m_stream << "uv " << v.m_uv.x << " " << v.m_uv.y << "\n";

			Indent();
			m_stream << "clr " << static_cast<unsigned>(v.m_color.r) << " " << static_cast<unsigned>(v.m_color.g)
				<< " " << static_cast<unsigned>(v.m_color.b) << " " << static_cast<unsigned>(v.m_color.a) << "\n";
		}

		m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);

		DecIndent();
		Indent();
		m_stream << "}\n\n";
	}

	void LoadVerticesWithPosition()
	{
		m_stream << "vertices\n";
		Indent();
		m_stream << "{\n";
		IncIndent();

		const auto vertexCount = ReadCountInCurlyBraces();

		m_vertices.resize(vertexCount);
		for (auto index = 0; index < vertexCount; index++)
		{
			Vertex& v = m_vertices[index];
			v.m_position.x = m_tokens->NextFloatValue();
			v.m_position.y = m_tokens->NextFloatValue();
			v.m_position.z = m_tokens->NextFloatValue();

			if (index > 0)
				m_stream << "\n";

			Indent();
			m_stream << "v " << v.m_position.x << " " << v.m_position.y << " " << v.m_position.z << "\n";
		}

		m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);

		DecIndent();
		Indent();
		m_stream << "}\n\n";
	}

	void LoadIndices()
	{
		m_stream << "indices\n";
		Indent();
		m_stream << "{\n";
		IncIndent();

		const auto indexCount = ReadCountInCurlyBraces();
		m_faces.resize(indexCount);

		for (auto index = 0; index < indexCount; index++)
		{
			auto& f = m_faces[index];
			f.indices[0] = static_cast<unsigned char>(m_tokens->NextIntegerValue());
			f.indices[1] = static_cast<unsigned char>(m_tokens->NextIntegerValue());
			f.indices[2] = static_cast<unsigned char>(m_tokens->NextIntegerValue());
			f.indices[3] = 0;

			Indent();
			m_stream << "f " << static_cast<unsigned>(f.indices[0]) << " " << static_cast<unsigned>(f.indices[1]) << " " << static_cast<unsigned>(f.indices[2]) << "\n";
		}

		m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);

		DecIndent();
		Indent();
		m_stream << "}\n\n";
	}

	void LoadVertexMeta()
	{
		m_stream << "meta\n";
		Indent();
		m_stream << "{\n";
		IncIndent();

		const auto metaCount = ReadCountInCurlyBraces();

		for (auto index = 0; index < metaCount; index++)
		{
			switch (m_tokens->NextValue().m_type)
			{
			case TOKEN_META_31:
			{
				const auto value0 = m_tokens->NextIntegerValue();
				const auto value1 = m_tokens->NextIntegerValue();
				const auto value2 = m_tokens->NextIntegerValue();

				Indent();
				m_stream << "token31 " << value0 << " " << value1 << " " << value2 << "\n";
			}
			break;
			case TOKEN_META_2D:
			{
				const auto value0 = m_tokens->NextIntegerValue();
				const auto value1 = m_tokens->NextIntegerValue();

				Indent();
				m_stream << "token2D " << value0 << " " << value1 << "\n";
			}
			break;
			case TOKEN_META_2F:
			{
				const auto value0 = m_tokens->NextIntegerValue();

				Indent();
				m_stream << "token2F " << value0 << "\n";
			}
			break;
			case TOKEN_META_30:
			{
				Indent();
				m_stream << "token30 " << "\n";
			}
			break;
			case TOKEN_META_32:
			{
				const auto value0 = m_tokens->NextIntegerValue();

				Indent();
				m_stream << "token32 " << value0 << "\n";
			}
			break;
			case TOKEN_META_27:
			{
				const auto value0 = m_tokens->NextIntegerValue();
				assert(value0 >= 0 && static_cast<unsigned>(value0) < m_materials.size());

				Indent();
				m_stream << "token27 " << value0 << "\n";
			}
			break;
			default:
				throw GdbDumpingException("Unknown keyword for vertex meta");
			}
		}

		m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);

		DecIndent();
		Indent();
		m_stream << "}\n\n";
	}

	void LoadScale()
	{
		m_scale_value = m_tokens->NextFloatValue();

		Indent();
		m_stream << "scale " << m_scale_value << "\n";
	}

	[[nodiscard]] int ReadCountInCurlyBraces() const
	{
		m_tokens->ExpectToken(TOKEN_LEFT_BRACKET);
		const auto materialCount = m_tokens->NextIntegerValue();
		m_tokens->ExpectToken(TOKEN_RIGHT_BRACKET);
		m_tokens->ExpectToken(TOKEN_LEFT_CURLY);
		return materialCount;
	}

	std::unique_ptr<ITokenInputStream> m_tokens;
	std::vector<std::string> m_materials;
	std::vector<ModelFace> m_faces;
	std::vector<Vertex> m_vertices;
	float m_scale_value;
};

bool GdbDumper::SupportFileExtension(const std::string& extension) const
{
	return extension == ".GDB";
}

void GdbDumper::ProcessFile(const std::string& filePath, std::istream& input, std::ostream& output) const
{
	std::cout << "GDB dumping \"" << filePath << "\"\n";

	GdbTextOutputStream out(input, output);
	out.Write();
}
