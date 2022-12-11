#include "TokenStream.h"

#include <cassert>
#include <deque>
#include <vector>

#include "Endianness.h"
#include "StreamUtils.h"

Token::Token()
    : m_type(TOKEN_INVALID),
      m_int_value(0),
      m_float_value(0)
{
}

Token::Token(const token_type_t type)
    : m_type(type),
      m_int_value(0),
      m_float_value(0)
{
}

Token::Token(const token_type_t type, const int value)
    : m_type(type),
      m_int_value(value),
      m_float_value(0)
{
}

Token::Token(const token_type_t type, const float value)
    : m_type(type),
      m_int_value(0),
      m_float_value(value)
{
}

Token::Token(const token_type_t type, std::string value)
    : m_type(type),
      m_int_value(0),
      m_float_value(0),
      m_string_value(std::move(value))
{
}

class TokenInputStream final : public ITokenInputStream
{
public:
    explicit TokenInputStream(std::istream& stream)
        : m_reader(stream),
          m_peeked_token(false),
          m_current_struct(0u),
          m_current_struct_index(0u),
          m_current_array_type(TOKEN_INVALID),
          m_current_array_size(0u),
          m_current_array_index(0u)
    {
    }

    const Token& PeekValue() override
    {
        if (!m_peeked_token)
        {
            ReadToken();
            m_peeked_token = true;
        }

        return m_current_token;
    }

    Token NextValue() override
    {
        if (m_peeked_token)
            m_peeked_token = false;
        else
            ReadToken();

        return std::move(m_current_token);
    }

    int NextIntegerValue() override
    {
        const auto token = NextValue();
        if (token.m_type != TOKEN_INT)
            throw TokenStreamException("Expected token integer value");

        return token.m_int_value;
    }

    std::string NextStringValue() override
    {
        auto token = NextValue();
        if (token.m_type != TOKEN_STRING)
            throw TokenStreamException("Expected token string value");

        return std::move(token.m_string_value);
    }

    float NextFloatValue() override
    {
        const auto token = NextValue();
        if (token.m_type != TOKEN_FLOAT)
            throw TokenStreamException("Expected token float value");

        return token.m_float_value;
    }

    void ExpectToken(const token_type_t tokenType) override
    {
        const auto token = NextValue();
        if (token.m_type != tokenType)
            throw TokenStreamException("Unexpected token value");
    }

private:
    token_type_t NextTokenTypeToRead()
    {
        if (!m_token_type_cache.empty())
        {
            const auto nextTokenType = m_token_type_cache.front();
            m_token_type_cache.pop_front();
            return nextTokenType;
        }

        if (m_current_struct > 0)
        {
            assert(m_current_struct - 1 < (TOKEN_STRUCT_LAST - TOKEN_STRUCT_FIRST + 1));
            const auto nextTokenType = m_struct_defs[m_current_struct - 1][m_current_struct_index];

            m_current_struct_index++;
            if (m_current_struct_index >= m_struct_defs[m_current_struct - 1].size())
            {
                m_current_struct = 0;
                m_current_struct_index = 0;
            }

            return nextTokenType;
        }

        if (m_current_array_size > 0)
        {
            assert(m_current_array_index < m_current_array_size);
            const auto nextTokenType = m_current_array_type;

            m_current_array_index++;
            if (m_current_array_index >= m_current_array_size)
            {
                m_current_array_size = 0;
                m_current_array_index = 0;
                m_current_array_type = TOKEN_INVALID;
            }

            return nextTokenType;
        }

        uint8_t readValue;
        if (!m_reader.TryReadUInt8(readValue))
            return TOKEN_EOF;

        return readValue;
    }

    void ReadArrayDef()
    {
        const auto arraySize = m_reader.ReadUInt16();
        m_current_array_size = static_cast<size_t>(arraySize);

        const auto tokenReadValue = m_reader.ReadUInt8();
        if (tokenReadValue == TOKEN_WCHAR)
            m_current_array_type = static_cast<token_type_t>(m_reader.ReadUInt16());
        else
            m_current_array_type = static_cast<token_type_t>(tokenReadValue);

        m_current_array_index = 0u;
    }

    void ReadStructDef()
    {
        const auto structTokenType = m_reader.ReadUInt8();
        if (structTokenType < TOKEN_STRUCT_FIRST || structTokenType > TOKEN_STRUCT_LAST)
            throw TokenStreamException("Invalid struct token type for struct def");

        const auto structIndex = static_cast<size_t>(structTokenType) - TOKEN_STRUCT_FIRST;
        const auto structMemberCount = m_reader.ReadUInt8();
        auto& structDef = m_struct_defs[structIndex];
        if (!structDef.empty())
            throw TokenStreamException("Struct already initialized");

        structDef.reserve(structMemberCount);
        for (auto memberIndex = 0u; memberIndex < structMemberCount; memberIndex++)
        {
            const auto readMemberTokenType = m_reader.ReadUInt8();
            if (readMemberTokenType == TOKEN_WCHAR)
                structDef.push_back(m_reader.ReadUInt16());
            else
                structDef.push_back(readMemberTokenType);
        }
    }

    void ReadToken()
    {
        bool shouldContinue;
        do
        {
            const auto nextTokenType = NextTokenTypeToRead();
            shouldContinue = false;

            switch (nextTokenType)
            {
            case TOKEN_STRING:
                {
                    auto str = m_reader.ReadStringZeroTerminated();
                    m_current_token = Token(TOKEN_STRING, std::move(str));
                    break;
                }

            case TOKEN_FLOAT:
                {
                    const auto val = m_reader.ReadFp32();
                    m_current_token = Token(TOKEN_FLOAT, val);
                    break;
                }

            case TOKEN_INT:
                {
                    const auto val = m_reader.ReadInt32();
                    m_current_token = Token(TOKEN_INT, static_cast<int>(val));
                    break;
                }

            case TOKEN_INT8:
                {
                    const auto val = m_reader.ReadInt8();
                    m_current_token = Token(TOKEN_INT, static_cast<int>(val));
                    break;
                }

            case TOKEN_UINT8:
                {
                    const auto val = m_reader.ReadUInt8();
                    m_current_token = Token(TOKEN_INT, static_cast<int>(val));
                    break;
                }

            case TOKEN_INT16:
                {
                    const auto val = m_reader.ReadInt16();
                    m_current_token = Token(TOKEN_INT, static_cast<int>(val));
                    break;
                }

            case TOKEN_UINT16:
                {
                    const auto val = m_reader.ReadUInt16();
                    m_current_token = Token(TOKEN_INT, static_cast<int>(val));
                    break;
                }

            case TOKEN_FP16_MAN_12:
                {
                    const auto val = m_reader.ReadInt16();
                    m_current_token = Token(TOKEN_FLOAT, static_cast<float>(val) / 4096.0f);
                    break;
                }

            case TOKEN_FP16_MAN_9:
                {
                    const auto val = m_reader.ReadInt16();
                    m_current_token = Token(TOKEN_FLOAT, static_cast<float>(val) / 32.0f);
                    break;
                }

            case TOKEN_FP16_MAN_0:
                {
                    const auto val = m_reader.ReadInt16();
                    m_current_token = Token(TOKEN_FLOAT, static_cast<float>(val));
                    break;
                }

            case TOKEN_FP8:
                {
                    const auto val = m_reader.ReadInt8();
                    m_current_token = Token(TOKEN_FLOAT, static_cast<float>(val) / 127.0f);
                    break;
                }

            case TOKEN_WCHAR:
                {
                    const auto val = m_reader.ReadUInt16();
                    m_current_token = Token(static_cast<token_type_t>(val));
                    break;
                }

            case TOKEN_ARRAY:
                ReadArrayDef();
                shouldContinue = true;
                break;

            case TOKEN_UNKNOWN:
                m_token_type_cache.emplace_back(TOKEN_LEFT_BRACKET);
                m_token_type_cache.emplace_back(TOKEN_INT);
                m_token_type_cache.emplace_back(TOKEN_RIGHT_BRACKET);
                m_token_type_cache.emplace_back(TOKEN_RIGHT_BRACKET);
                shouldContinue = true;
                break;

            case TOKEN_STRUCT_DEF:
                ReadStructDef();
                shouldContinue = true;
                break;

            case TOKEN_INVALID:
            case TOKEN_EOF:
            case TOKEN_LEFT_CURLY:
            case TOKEN_RIGHT_CURLY:
            case TOKEN_LEFT_BRACKET:
            case TOKEN_RIGHT_BRACKET:
            case TOKEN_COMMA:
            case TOKEN_SEMICOLON:
            default:
                if (nextTokenType >= TOKEN_STRUCT_FIRST && nextTokenType <= TOKEN_STRUCT_LAST)
                {
                    const auto structIndex = static_cast<size_t>(nextTokenType - TOKEN_STRUCT_FIRST);
                    m_current_struct = structIndex + 1;
                    m_current_struct_index = 0u;
                    shouldContinue = true;
                }
                else
                    m_current_token = Token(nextTokenType);
                break;
            }
        }
        while (shouldContinue);
    }

    utils::BinaryReaderStream m_reader;
    bool m_peeked_token;
    Token m_current_token;
    std::deque<token_type_t> m_token_type_cache;
    size_t m_current_struct;
    size_t m_current_struct_index;
    token_type_t m_current_array_type;
    size_t m_current_array_size;
    size_t m_current_array_index;
    std::vector<token_type_t> m_struct_defs[TOKEN_STRUCT_LAST - TOKEN_STRUCT_FIRST + 1];
};

std::unique_ptr<ITokenInputStream> ITokenInputStream::Create(std::istream& stream)
{
    return std::make_unique<TokenInputStream>(stream);
}

class TokenOutputStream final : public ITokenOutputStream
{
public:
    explicit TokenOutputStream(std::ostream& stream)
        : m_stream(stream)
    {
    }

    void WriteString(const std::string& value) override
    {
        m_stream.put(TOKEN_STRING);
        m_stream.write(value.c_str(), value.size());
        m_stream.put('\0');
    }

    void WriteFloat(const float value) override
    {
        m_stream.put(TOKEN_FLOAT);
        m_stream.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }

    void WriteInteger(const int value) override
    {
        const auto leValue = endianness::ToLittleEndian(value);
        m_stream.put(TOKEN_INT);
        m_stream.write(reinterpret_cast<const char*>(&leValue), sizeof(leValue));
    }

    void WriteLeftCurly() override
    {
        m_stream.put(TOKEN_LEFT_CURLY);
    }

    void WriteRightCurly() override
    {
        m_stream.put(TOKEN_RIGHT_CURLY);
    }

    void WriteLeftBracket() override
    {
        m_stream.put(TOKEN_LEFT_BRACKET);
    }

    void WriteRightBracket() override
    {
        m_stream.put(TOKEN_RIGHT_BRACKET);
    }

    void WriteComma() override
    {
        m_stream.put(TOKEN_COMMA);
    }

    void WriteSemicolon() override
    {
        m_stream.put(TOKEN_SEMICOLON);
    }

    void WriteInt8(const int8_t value) override
    {
        m_stream.put(TOKEN_INT8);
        m_stream.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }

    void WriteUInt8(const uint8_t value) override
    {
        m_stream.put(TOKEN_UINT8);
        m_stream.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }

    void WriteInt16(const int16_t value) override
    {
        const auto leValue = endianness::ToLittleEndian(value);
        m_stream.put(TOKEN_INT16);
        m_stream.write(reinterpret_cast<const char*>(&leValue), sizeof(leValue));
    }

    void WriteUInt16(const uint16_t value) override
    {
        const auto leValue = endianness::ToLittleEndian(value);
        m_stream.put(TOKEN_UINT16);
        m_stream.write(reinterpret_cast<const char*>(&leValue), sizeof(leValue));
    }

    void WriteFp16Man12(const float value) override
    {
        const auto leValue = endianness::ToLittleEndian(static_cast<int16_t>(value * 4096.0f));
        m_stream.put(TOKEN_FP16_MAN_12);
        m_stream.write(reinterpret_cast<const char*>(&leValue), sizeof(leValue));
    }

    void WriteFp16Man9(const float value) override
    {
        const auto leValue = endianness::ToLittleEndian(static_cast<int16_t>(value * 32.0f));
        m_stream.put(TOKEN_FP16_MAN_9);
        m_stream.write(reinterpret_cast<const char*>(&leValue), sizeof(leValue));
    }

    void WriteFp16Man0(const float value) override
    {
        const auto leValue = endianness::ToLittleEndian(static_cast<int16_t>(value));
        m_stream.put(TOKEN_FP16_MAN_0);
        m_stream.write(reinterpret_cast<const char*>(&leValue), sizeof(leValue));
    }

    void WriteFp8(const float value) override
    {
        const auto byteValue = static_cast<int8_t>(value * 127.0f);
        m_stream.put(TOKEN_FP8);
        m_stream.write(reinterpret_cast<const char*>(&byteValue), sizeof(byteValue));
    }

    void WriteWChar(const wchar_t value) override
    {
        const auto leValue = endianness::ToLittleEndian(static_cast<uint16_t>(value));
        m_stream.put(TOKEN_WCHAR);
        m_stream.write(reinterpret_cast<const char*>(&leValue), sizeof(leValue));
    }

    void WriteCustom(const token_type_t value) override
    {
        const auto tokenValue = static_cast<uint8_t>(value);
        m_stream.write(reinterpret_cast<const char*>(&tokenValue), sizeof(tokenValue));
    }

private:
    std::ostream& m_stream;
};

std::unique_ptr<ITokenOutputStream> ITokenOutputStream::Create(std::ostream& stream)
{
    return std::make_unique<TokenOutputStream>(stream);
}
