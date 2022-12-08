#pragma once
#include <cstdint>
#include <string>
#include <memory>

enum TokenType
{
    TOKEN_INVALID = 0x0,
    TOKEN_EOF = 0x1,
    TOKEN_STRING = 0x2,
    TOKEN_FLOAT = 0x3,
    TOKEN_INT = 0x4,
    TOKEN_LEFT_CURLY = 0x5,
    TOKEN_RIGHT_CURLY = 0x6,
    TOKEN_LEFT_BRACKET = 0x7,
    TOKEN_RIGHT_BRACKET = 0x8,
    TOKEN_COMMA = 0x9,
    TOKEN_SEMICOLON = 0xA,
    TOKEN_INT8 = 0xB,
    TOKEN_UINT8 = 0xC,
    TOKEN_INT16 = 0xD,
    TOKEN_UINT16 = 0xE,
    TOKEN_FP16_MAN_12 = 0xF,    // 16bit number -> 4bit decimal + 12bit mantissa
    TOKEN_FP16_MAN_9 = 0x10,    // 16bit number -> 7bit decimal + 9bit mantissa
    TOKEN_FP16_MAN_0 = 0x11,    // 16bit number -> 16bit decimal + 0bit mantissa -> Basically int16 read as a float
    TOKEN_FP8 = 0x12,
    TOKEN_WCHAR = 0x13,
    TOKEN_ARRAY = 0x14,
    TOKEN_UNKNOWN = 0x15,
    TOKEN_STRUCT_DEF = 0x16,
    TOKEN_STRUCT_FIRST = 0x17,
    TOKEN_STRUCT_LAST = 0x26,
    TOKEN_CUSTOM_FIRST = 0x27,
};

// May be value from TokenType, a struct index when TOKEN_STRUCT_FIRST <= value <= TOKEN_STRUCT_LAST, or custom token type when value >= TOKEN_CUSTOM_FIRST
typedef size_t token_type_t;

class TokenStreamException final : public std::exception
{
public:
    explicit TokenStreamException(char const* msg)
        : exception(msg)
    {
    }
};

class Token
{
public:
    token_type_t m_type;
    int m_int_value;
    float m_float_value;
    std::string m_string_value;

    Token();
    explicit Token(token_type_t type);
    Token(token_type_t type, int value);
    Token(token_type_t type, float value);
    Token(token_type_t type, std::string value);
};

class ITokenInputStream
{
protected:
    ITokenInputStream() = default;

public:
    virtual ~ITokenInputStream() = default;
    ITokenInputStream(const ITokenInputStream& other) = default;
    ITokenInputStream(ITokenInputStream&& other) noexcept = default;
    ITokenInputStream& operator=(const ITokenInputStream& other) = default;
    ITokenInputStream& operator=(ITokenInputStream&& other) noexcept = default;

    static std::unique_ptr<ITokenInputStream> Create(std::istream& stream);

    virtual Token NextValue() = 0;
    virtual const Token& PeekValue() = 0;
    virtual int NextIntegerValue() = 0;
    virtual std::string NextStringValue() = 0;
    virtual float NextFloatValue() = 0;
    virtual void ExpectToken(token_type_t tokenType) = 0;
};

class ITokenOutputStream
{
protected:
    ITokenOutputStream() = default;

public:
    virtual ~ITokenOutputStream() = default;
    ITokenOutputStream(const ITokenOutputStream& other) = default;
    ITokenOutputStream(ITokenOutputStream&& other) noexcept = default;
    ITokenOutputStream& operator=(const ITokenOutputStream& other) = default;
    ITokenOutputStream& operator=(ITokenOutputStream&& other) noexcept = default;

    static std::unique_ptr<ITokenOutputStream> Create(std::ostream& stream);

    virtual void WriteString(const std::string& value) = 0;
    virtual void WriteFloat(float value) = 0;
    virtual void WriteInteger(int value) = 0;
    virtual void WriteLeftCurly() = 0;
    virtual void WriteRightCurly() = 0;
    virtual void WriteLeftBracket() = 0;
    virtual void WriteRightBracket() = 0;
    virtual void WriteComma() = 0;
    virtual void WriteSemicolon() = 0;
    virtual void WriteInt8(int8_t value) = 0;
    virtual void WriteUInt8(uint8_t value) = 0;
    virtual void WriteInt16(int16_t value) = 0;
    virtual void WriteUInt16(uint16_t value) = 0;
    virtual void WriteFp16Man12(float value) = 0;
    virtual void WriteFp16Man9(float value) = 0;
    virtual void WriteFp16Man0(float value) = 0;
    virtual void WriteFp8(float value) = 0;
    virtual void WriteWChar(wchar_t value) = 0;
    virtual void WriteCustom(token_type_t value) = 0;
};