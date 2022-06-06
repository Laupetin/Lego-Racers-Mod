#pragma once
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
    TOKEN_FP16_MAN_12 = 0xF,
    TOKEN_FP16_MAN_9 = 0x10,
    TOKEN_FP16_MAN_0 = 0x11,
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
    virtual void ExpectToken(token_type_t tokenType) = 0;
};