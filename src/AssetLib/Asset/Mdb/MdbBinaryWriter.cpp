#include "MdbBinaryWriter.h"

#include <sstream>

#include "TokenStream.h"

namespace mdb
{
	class MdbBinaryWriterImpl final : public IMdbEmitter
	{
	public:
		explicit MdbBinaryWriterImpl(std::ostream& stream)
			: m_stream(stream),
			m_tokens(ITokenOutputStream::Create(m_stream)),
			m_temp_tokens(ITokenOutputStream::Create(m_temp_buffer)),
			m_current_count(0u)
		{
		}

		void StartMaterials() override
		{
			PrepareElementsInTempBuffer(TOKEN_MATERIAL_DB);
		}

		void EndMaterials() override
		{
			WriteElementsFromTempBuffer();
			m_current_count = 0u;
		}

        void StartMaterial(const std::string name) override
		{
			m_current_count++;
			m_temp_tokens->WriteCustom(TOKEN_MATERIAL);
			m_temp_tokens->WriteString(name);
			m_temp_tokens->WriteLeftCurly();
		}

        void EmitColor0(const uint8_t value0, const uint8_t value1, const uint8_t value2, const uint8_t value3) override
		{
			m_temp_tokens->WriteCustom(TOKEN_KEYWORD_COLOR_0);
			m_temp_tokens->WriteUInt8(value0);
			m_temp_tokens->WriteUInt8(value1);
			m_temp_tokens->WriteUInt8(value2);
			m_temp_tokens->WriteUInt8(value3);
		}

        void EmitColor1(const uint8_t value0, const uint8_t value1, const uint8_t value2, const uint8_t value3) override
		{
			m_temp_tokens->WriteCustom(TOKEN_KEYWORD_COLOR_1);
			m_temp_tokens->WriteUInt8(value0);
			m_temp_tokens->WriteUInt8(value1);
			m_temp_tokens->WriteUInt8(value2);
			m_temp_tokens->WriteUInt8(value3);
		}

        void EmitTexture(const std::string textureName) override
		{
			m_temp_tokens->WriteCustom(TOKEN_KEYWORD_TEXTURE);
			m_temp_tokens->WriteString(textureName);
		}

        void EmitOpacity(const uint8_t value) override
		{
			m_temp_tokens->WriteCustom(TOKEN_KEYWORD_OPACITY);
			m_temp_tokens->WriteUInt8(value);
		}

        void EmitKeyword4E(const int value) override
		{
			m_temp_tokens->WriteCustom(TOKEN_KEYWORD_4E);
			m_temp_tokens->WriteInteger(value);
		}

        void EmitKeyword4F(const int value) override
		{
			m_temp_tokens->WriteCustom(TOKEN_KEYWORD_4F);
			m_temp_tokens->WriteInteger(value);
		}

        void EmitKeyword4D(const int value) override
		{
			m_temp_tokens->WriteCustom(TOKEN_KEYWORD_4D);
			m_temp_tokens->WriteInteger(value);
		}

        void EmitKeyword50(const int value) override
		{
			m_temp_tokens->WriteCustom(TOKEN_KEYWORD_50);
			m_temp_tokens->WriteInteger(value);
		}

        void EmitKeyword2A() override
		{
			m_temp_tokens->WriteCustom(TOKEN_KEYWORD_2A);
		}

        void EmitKeyword2B() override
		{
			m_temp_tokens->WriteCustom(TOKEN_KEYWORD_2B);
		}

        void EmitKeyword2D() override
		{
			m_temp_tokens->WriteCustom(TOKEN_KEYWORD_2D);
		}

        void EmitKeyword2E() override
		{
			m_temp_tokens->WriteCustom(TOKEN_KEYWORD_2E);
		}

        void EmitKeyword44() override
		{
			m_temp_tokens->WriteCustom(TOKEN_KEYWORD_44);
		}

        void EmitKeyword45() override
		{
			m_temp_tokens->WriteCustom(TOKEN_KEYWORD_45);
		}

        void EmitKeyword47() override
		{
			m_temp_tokens->WriteCustom(TOKEN_KEYWORD_47);
		}

        void EmitKeyword48() override
		{
			m_temp_tokens->WriteCustom(TOKEN_KEYWORD_48);
		}

        void EmitKeyword49() override
		{
			m_temp_tokens->WriteCustom(TOKEN_KEYWORD_49);
		}

        void EmitKeyword4A() override
		{
			m_temp_tokens->WriteCustom(TOKEN_KEYWORD_4A);
		}

        void EmitKeyword4B() override
		{
			m_temp_tokens->WriteCustom(TOKEN_KEYWORD_4B);
		}

        void EmitKeyword4C() override
		{
			m_temp_tokens->WriteCustom(TOKEN_KEYWORD_4C);
		}

        void EmitKeyword2F(const MaterialToken subToken, const int subTokenValue) override
		{
			m_temp_tokens->WriteCustom(TOKEN_KEYWORD_2F);

			switch (subToken)
			{
			case TOKEN_KEYWORD_2F_SUB_30:
			case TOKEN_KEYWORD_2F_SUB_36:
				m_temp_tokens->WriteCustom(subToken);
				break;

			case TOKEN_KEYWORD_2F_SUB_31:
			case TOKEN_KEYWORD_2F_SUB_32:
			case TOKEN_KEYWORD_2F_SUB_33:
			case TOKEN_KEYWORD_2F_SUB_34:
			case TOKEN_KEYWORD_2F_SUB_35:
			case TOKEN_KEYWORD_2F_SUB_37:
				m_temp_tokens->WriteCustom(subToken);
				m_temp_tokens->WriteInteger(subTokenValue);
				break;

			default:
				break;
			}
		}

        void EmitKeyword38(const MaterialToken subToken0, const MaterialToken subToken1) override
		{
			m_temp_tokens->WriteCustom(TOKEN_KEYWORD_38);
			m_temp_tokens->WriteCustom(subToken0);
			m_temp_tokens->WriteCustom(subToken1);
		}

        void EndMaterial() override
        {
			m_temp_tokens->WriteRightCurly();
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
		}

		std::ostream& m_stream;
		std::unique_ptr<ITokenOutputStream> m_tokens;
		std::ostringstream m_temp_buffer;
		std::unique_ptr<ITokenOutputStream> m_temp_tokens;
		size_t m_current_count;
	};
}

using namespace mdb;

std::unique_ptr<IMdbEmitter> MdbBinaryWriter::Create(std::ostream& stream)
{
	return std::make_unique<MdbBinaryWriterImpl>(stream);
}
