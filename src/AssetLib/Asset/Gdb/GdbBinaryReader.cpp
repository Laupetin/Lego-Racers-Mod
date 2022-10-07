#include "GdbBinaryReader.h"

#include "TokenStream.h"

using namespace gdb;

namespace gdb
{
	class GdbBinaryReadingException final : public std::exception
	{
	public:
		explicit GdbBinaryReadingException(char const* msg)
			: exception(msg)
		{
		}
	};

	class GdbBinaryReaderImpl
	{
	public:
		GdbBinaryReaderImpl(std::istream& in, IGdbEmitter& emitter)
			: m_tokens(ITokenInputStream::Create(in)),
			m_emitter(emitter)
		{
		}

		void Read()
		{
			for (auto nextSectionToken = m_tokens->NextValue(); nextSectionToken.m_type != TOKEN_INVALID && nextSectionToken.m_type != TOKEN_EOF; nextSectionToken = m_tokens->NextValue())
			{
				switch (nextSectionToken.m_type)
				{
				case TOKEN_SECTION_MATERIAL:
					ReadMaterialList();
					break;

				case TOKEN_SECTION_VERTEX_WITH_POSITION_UV:
					ReadVerticesWithPositionAndUv();
					break;

				case TOKEN_SECTION_VERTEX_WITH_POSITION_UV_NORMAL:
					ReadVerticesWithPositionAndUvAndNormal();
					break;

				case TOKEN_SECTION_VERTEX_WITH_POSITION_UV_COLOR:
					ReadVerticesWithPositionAndUvAndColor();
					break;

				case TOKEN_SECTION_INDICES:
					ReadFaces();
					break;

				case TOKEN_SECTION_VERTEX_META:
					ReadVertexMeta();
					break;

				case TOKEN_SCALE:
					ReadScale();
					break;

				case TOKEN_SECTION_VERTEX_WITH_POSITION:
					ReadVerticesWithPosition();
					break;

				default:
					throw GdbBinaryReadingException("Unknown keyword for section");
				}
			}
		}

	private:
		void ReadMaterialList()
		{
			m_emitter.StartMaterials();

			const auto materialCount = ReadCountInCurlyBraces();
			for (auto materialIndex = 0; materialIndex < materialCount; materialIndex++)
			{
				auto materialName = m_tokens->NextStringValue();

				m_emitter.EmitMaterial(std::move(materialName));
			}

			m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);

			m_emitter.EndMaterials();
		}

		void ReadVerticesWithPositionAndUv()
		{
			m_emitter.StartVertices();

			const auto vertexCount = ReadCountInCurlyBraces();
			for (auto index = 0; index < vertexCount; index++)
			{
				Vec3 position;
				position.x = m_tokens->NextFloatValue();
				position.y = m_tokens->NextFloatValue();
				position.z = m_tokens->NextFloatValue();

				Vec2 uv;
				uv.x = m_tokens->NextFloatValue();
				uv.y = m_tokens->NextFloatValue();

				m_emitter.EmitVertex(position, uv);
			}

			m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);

			m_emitter.EndVertices();
		}

		void ReadVerticesWithPositionAndUvAndNormal()
		{
			m_emitter.StartVertices();

			const auto vertexCount = ReadCountInCurlyBraces();
			for (auto index = 0; index < vertexCount; index++)
			{
				Vec3 position;
				position.x = m_tokens->NextFloatValue();
				position.y = m_tokens->NextFloatValue();
				position.z = m_tokens->NextFloatValue();

				Vec2 uv;
				uv.x = m_tokens->NextFloatValue();
				uv.y = m_tokens->NextFloatValue();

				Vec3 normal;
				normal.x = m_tokens->NextFloatValue();
				normal.y = m_tokens->NextFloatValue();
				normal.z = m_tokens->NextFloatValue();

				m_emitter.EmitVertex(position, uv, normal);
			}

			m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);

			m_emitter.EndVertices();
		}

		void ReadVerticesWithPositionAndUvAndColor()
		{
			m_emitter.StartVertices();

			const auto vertexCount = ReadCountInCurlyBraces();
			for (auto index = 0; index < vertexCount; index++)
			{
				Vec3 position;
				position.x = m_tokens->NextFloatValue();
				position.y = m_tokens->NextFloatValue();
				position.z = m_tokens->NextFloatValue();

				Vec2 uv;
				uv.x = m_tokens->NextFloatValue();
				uv.y = m_tokens->NextFloatValue();

				Color4 color;
				color.r = m_tokens->NextIntegerValue();
				color.g = m_tokens->NextIntegerValue();
				color.b = m_tokens->NextIntegerValue();
				color.a = m_tokens->NextIntegerValue();

				m_emitter.EmitVertex(position, uv, color);
			}

			m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);

			m_emitter.EndVertices();
		}

		void ReadVerticesWithPosition()
		{
			m_emitter.StartVertices();

			const auto vertexCount = ReadCountInCurlyBraces();
			for (auto index = 0; index < vertexCount; index++)
			{
				Vec3 position;
				position.x = m_tokens->NextFloatValue();
				position.y = m_tokens->NextFloatValue();
				position.z = m_tokens->NextFloatValue();

				m_emitter.EmitVertex(position);
			}

			m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);

			m_emitter.EndVertices();
		}

		void ReadFaces()
		{
			m_emitter.StartFaces();

			const auto faceCount = ReadCountInCurlyBraces();
			for (auto index = 0; index < faceCount; index++)
			{
				const auto vertex0 = static_cast<unsigned char>(m_tokens->NextIntegerValue());
				const auto vertex1 = static_cast<unsigned char>(m_tokens->NextIntegerValue());
				const auto vertex2 = static_cast<unsigned char>(m_tokens->NextIntegerValue());

				m_emitter.EmitFace(vertex0, vertex1, vertex2);
			}

			m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);

			m_emitter.EndFaces();
		}

		void ReadVertexMeta()
		{
			m_emitter.StartMeta();

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

					m_emitter.EmitMetaKeyword31(value0, value1, value2);
				}
				break;
				case TOKEN_META_2D:
				{
					const auto value0 = m_tokens->NextIntegerValue();
					const auto value1 = m_tokens->NextIntegerValue();

					m_emitter.EmitMetaKeyword2D(value0, value1);
				}
				break;
				case TOKEN_META_2F:
				{
					const auto value0 = m_tokens->NextIntegerValue();

					m_emitter.EmitMetaKeyword2F(value0);
				}
				break;
				case TOKEN_META_30:
				{
					m_emitter.EmitMetaKeyword30();
				}
				break;
				case TOKEN_META_32:
				{
					const auto value0 = m_tokens->NextIntegerValue();

					m_emitter.EmitMetaKeyword32(value0);
				}
				break;
				case TOKEN_META_27:
				{
					const auto value0 = m_tokens->NextIntegerValue();

					m_emitter.EmitMetaKeyword27(value0);
				}
				break;
				default:
					throw GdbBinaryReadingException("Unknown keyword for vertex meta");
				}
			}

			m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);

			m_emitter.EndMeta();
		}

		void ReadScale()
		{
			const auto scaleValue = m_tokens->NextFloatValue();
			m_emitter.EmitScale(scaleValue);
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
		IGdbEmitter& m_emitter;
	};
}

void GdbBinaryReader::Read(std::istream& input, IGdbEmitter& emitter)
{
	GdbBinaryReaderImpl impl(input, emitter);
	impl.Read();
}
