#include "GdbBinaryWriter.h"

#include <sstream>

#include "TokenStream.h"

namespace gdb
{
	class GdbBinaryWriterImpl final : public IGdbEmitter
	{
	public:
        explicit GdbBinaryWriterImpl(std::ostream& stream)
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

		void EmitMaterial(const std::string materialName) override
		{
			m_temp_tokens->WriteString(materialName);
			m_current_count++;
		}

		void EndMaterials() override
		{
			WriteElementsFromTempBuffer();
		}

		void EmitScale(const float scale) override
		{
			m_tokens->WriteCustom(TOKEN_SCALE);
			m_tokens->WriteFloat(scale);
		}

		void StartVertices() override
		{
			// Do nothing
		}

		void EmitVertex(const Vec3 position) override
		{
			if (m_current_count <= 0)
				PrepareElementsInTempBuffer(TOKEN_SECTION_VERTEX_WITH_POSITION);

			m_temp_tokens->WriteFloat(position.x);
			m_temp_tokens->WriteFloat(position.y);
			m_temp_tokens->WriteFloat(position.z);
			m_current_count++;
		}

		void EmitVertex(const Vec3 position, const Vec2 uv) override
		{
			if (m_current_count <= 0)
				PrepareElementsInTempBuffer(TOKEN_SECTION_VERTEX_WITH_POSITION_UV);

			m_temp_tokens->WriteFloat(position.x);
			m_temp_tokens->WriteFloat(position.y);
			m_temp_tokens->WriteFloat(position.z);

			m_temp_tokens->WriteFloat(uv.x);
			m_temp_tokens->WriteFloat(uv.y);

			m_current_count++;
		}

		void EmitVertex(const Vec3 position, const Vec2 uv, const Color4 color) override
		{
			if (m_current_count <= 0)
				PrepareElementsInTempBuffer(TOKEN_SECTION_VERTEX_WITH_POSITION_UV_COLOR);

			m_temp_tokens->WriteFloat(position.x);
			m_temp_tokens->WriteFloat(position.y);
			m_temp_tokens->WriteFloat(position.z);

			m_temp_tokens->WriteFloat(uv.x);
			m_temp_tokens->WriteFloat(uv.y);

			m_temp_tokens->WriteUInt8(color.r);
			m_temp_tokens->WriteUInt8(color.g);
			m_temp_tokens->WriteUInt8(color.b);
			m_temp_tokens->WriteUInt8(color.a);

			m_current_count++;
		}

		void EmitVertex(const Vec3 position, const Vec2 uv, const Vec3 normal) override
		{
			if (m_current_count <= 0)
				PrepareElementsInTempBuffer(TOKEN_SECTION_VERTEX_WITH_POSITION_UV_NORMAL);

			m_temp_tokens->WriteFloat(position.x);
			m_temp_tokens->WriteFloat(position.y);
			m_temp_tokens->WriteFloat(position.z);

			m_temp_tokens->WriteFloat(uv.x);
			m_temp_tokens->WriteFloat(uv.y);

			m_temp_tokens->WriteFloat(normal.x);
			m_temp_tokens->WriteFloat(normal.y);
			m_temp_tokens->WriteFloat(normal.z);

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

		void EmitFace(const uint8_t vertex0, const uint8_t vertex1, const uint8_t vertex2) override
		{
			m_temp_tokens->WriteUInt8(vertex0);
			m_temp_tokens->WriteUInt8(vertex1);
			m_temp_tokens->WriteUInt8(vertex2);

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

		void EmitMetaSelectVertices(const uint8_t shiftForwardCount, const size_t vertexOffset, const uint8_t vertexCount) override
		{
			m_temp_tokens->WriteCustom(TOKEN_META_VERTICES);
			m_temp_tokens->WriteUInt8(shiftForwardCount);
			m_temp_tokens->WriteInteger(static_cast<int>(vertexOffset));
			m_temp_tokens->WriteUInt8(vertexCount);

			m_current_count++;
		}

		void EmitMetaAddFaces(const size_t faceOffset, const uint8_t faceCount) override
		{
			m_temp_tokens->WriteCustom(TOKEN_META_FACES);
			m_temp_tokens->WriteInteger(static_cast<int>(faceOffset));
			m_temp_tokens->WriteUInt8(faceCount);

			m_current_count++;
		}

		void EmitMetaKeyword2F(const int value0) override
		{
			m_temp_tokens->WriteCustom(TOKEN_META_2F);
			m_temp_tokens->WriteInteger(value0);

			m_current_count++;
		}

		void EmitMetaKeyword30() override
		{
			m_temp_tokens->WriteCustom(TOKEN_META_30);

			m_current_count++;
		}

		void EmitMetaKeyword32(const int value0) override
		{
			m_temp_tokens->WriteCustom(TOKEN_META_32);
			m_temp_tokens->WriteInteger(value0);

			m_current_count++;
		}

		void EmitMetaNewObject(const size_t materialIndex) override
		{
			m_temp_tokens->WriteCustom(TOKEN_META_NEW_OBJECT);
			m_temp_tokens->WriteInteger(static_cast<int>(materialIndex));

			m_current_count++;
		}

		void EndMeta() override
		{
			WriteElementsFromTempBuffer();
		}

	private:
		void PrepareElementsInTempBuffer(const token_type_t startTokenType) const
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
