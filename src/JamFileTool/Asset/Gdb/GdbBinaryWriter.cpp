#include "GdbBinaryWriter.h"

#include <sstream>

#include "TokenStream.h"

namespace gdb
{
	class GdbBinaryWriterImpl final : public IGdbEmitter
	{
	public:
		GdbBinaryWriterImpl(std::ostream& stream)
			: m_stream(stream),
			  m_tokens(ITokenOutputStream::Create(m_stream)),
			  m_temp_tokens(ITokenOutputStream::Create(m_temp_buffer)),
			  m_current_count(0u)
		{
		}

		void StartMaterials() override
		{
			PrepareElementsInTempBuffer(TOKEN_SECTION_MATERIAL);
		}

		void EmitMaterial(std::string materialName) override
		{
			m_temp_tokens->WriteString(materialName);
			m_current_count++;
		}

		void EndMaterials() override
		{
			WriteElementsFromTempBuffer();
		}

		void EmitScale(float scale) override
		{
			m_tokens->WriteCustom(TOKEN_SCALE);
			m_tokens->WriteFloat(scale);
		}

		void StartVertices() override
		{
			// Do nothing
		}

		void EmitVertex(Vec3 position) override
		{
			if (m_current_count <= 0)
				PrepareElementsInTempBuffer(TOKEN_SECTION_VERTEX_WITH_POSITION);

			m_tokens->WriteFloat(position.x);
			m_tokens->WriteFloat(position.y);
			m_tokens->WriteFloat(position.z);
			m_current_count++;
		}

		void EmitVertex(Vec3 position, Vec2 uv) override
		{
			if (m_current_count <= 0)
				PrepareElementsInTempBuffer(TOKEN_SECTION_VERTEX_WITH_POSITION_UV);

			m_tokens->WriteFloat(position.x);
			m_tokens->WriteFloat(position.y);
			m_tokens->WriteFloat(position.z);

			m_tokens->WriteFloat(uv.x);
			m_tokens->WriteFloat(uv.y);

			m_current_count++;
		}

		void EmitVertex(Vec3 position, Vec2 uv, Color4 color) override
		{
			if (m_current_count <= 0)
				PrepareElementsInTempBuffer(TOKEN_SECTION_VERTEX_WITH_POSITION_UV_COLOR);

			m_tokens->WriteFloat(position.x);
			m_tokens->WriteFloat(position.y);
			m_tokens->WriteFloat(position.z);

			m_tokens->WriteFloat(uv.x);
			m_tokens->WriteFloat(uv.y);

			m_tokens->WriteUInt8(color.r);
			m_tokens->WriteUInt8(color.g);
			m_tokens->WriteUInt8(color.b);
			m_tokens->WriteUInt8(color.a);

			m_current_count++;
		}

		void EmitVertex(Vec3 position, Vec2 uv, Vec3 normal) override
		{
			if (m_current_count <= 0)
				PrepareElementsInTempBuffer(TOKEN_SECTION_VERTEX_WITH_POSITION_UV_NORMAL);

			m_tokens->WriteFloat(position.x);
			m_tokens->WriteFloat(position.y);
			m_tokens->WriteFloat(position.z);

			m_tokens->WriteFloat(uv.x);
			m_tokens->WriteFloat(uv.y);

			m_tokens->WriteFloat(normal.x);
			m_tokens->WriteFloat(normal.y);
			m_tokens->WriteFloat(normal.z);

			m_current_count++;
		}

		void EndVertices() override
		{
			WriteElementsFromTempBuffer();
		}

		void StartFaces() override
		{
			PrepareElementsInTempBuffer(TOKEN_SECTION_INDICES);
		}

		void EmitFace(unsigned vertex0, unsigned vertex1, unsigned vertex2) override
		{
			m_tokens->WriteUInt8(vertex0);
			m_tokens->WriteUInt8(vertex1);
			m_tokens->WriteUInt8(vertex2);

			m_current_count++;
		}

		void EndFaces() override
		{
			WriteElementsFromTempBuffer();
		}

		void StartMeta() override
		{
			PrepareElementsInTempBuffer(TOKEN_SECTION_VERTEX_META);
		}

		void EmitMetaKeyword31(int value0, int value1, int value2) override
		{
			m_tokens->WriteCustom(TOKEN_META_31);
			m_tokens->WriteInteger(value0);
			m_tokens->WriteInteger(value1);
			m_tokens->WriteInteger(value2);

			m_current_count++;
		}

		void EmitMetaKeyword2D(int value0, int value1) override
		{
			m_tokens->WriteCustom(TOKEN_META_2D);
			m_tokens->WriteInteger(value0);
			m_tokens->WriteInteger(value1);

			m_current_count++;
		}

		void EmitMetaKeyword2F(int value0) override
		{
			m_tokens->WriteCustom(TOKEN_META_2F);
			m_tokens->WriteInteger(value0);

			m_current_count++;
		}

		void EmitMetaKeyword30() override
		{
			m_tokens->WriteCustom(TOKEN_META_30);

			m_current_count++;
		}

		void EmitMetaKeyword32(int value0) override
		{
			m_tokens->WriteCustom(TOKEN_META_32);
			m_tokens->WriteInteger(value0);

			m_current_count++;
		}

		void EmitMetaKeyword27(int value0) override
		{
			m_tokens->WriteCustom(TOKEN_META_27);
			m_tokens->WriteInteger(value0);

			m_current_count++;
		}

		void EndMeta() override
		{
			WriteElementsFromTempBuffer();
		}

	private:
		void PrepareElementsInTempBuffer(token_type_t startTokenType)
		{
			m_tokens->WriteCustom(startTokenType);
		}

		void WriteElementsFromTempBuffer()
		{
			m_tokens->WriteLeftBracket();
			m_tokens->WriteInteger(static_cast<int>(m_current_count));
			m_tokens->WriteRightBracket();
			m_tokens->WriteLeftCurly();

			m_stream << m_temp_buffer.str();

			m_tokens->WriteRightCurly();

			m_temp_buffer.str(std::string());
			m_current_count = 0u;
		}

		std::ostream& m_stream;
		std::unique_ptr<ITokenOutputStream> m_tokens;
		std::ostringstream m_temp_buffer;
		std::unique_ptr<ITokenOutputStream> m_temp_tokens;
		size_t m_current_count;
	};
}

using namespace gdb;

std::unique_ptr<IGdbEmitter> GdbBinaryWriter::Create(std::ostream& stream)
{
	return std::make_unique<GdbBinaryWriterImpl>(stream);
}
