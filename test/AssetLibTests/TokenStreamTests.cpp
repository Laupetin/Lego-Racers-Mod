#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <cstdint>
#include <limits>
#include <sstream>
#include <type_traits>

#include "TokenStream.h"

using namespace Catch::Matchers;

namespace test::token_stream
{
    constexpr auto FLOAT_EPS = static_cast<double>(std::numeric_limits<float>::epsilon());

    TEST_CASE("TokenInputStream: Ensure NextValue reads next token", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << '\x60';

        auto token = stream->NextValue();
        REQUIRE(token.m_type == static_cast<token_type_t>('\x60'));

        token = stream->NextValue();
        REQUIRE(token.m_type == TOKEN_EOF);
    }

    TEST_CASE("TokenInputStream: Ensure PeekValue does not consume next token", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << '\x60';

        auto token = stream->PeekValue();
        REQUIRE(token.m_type == static_cast<token_type_t>('\x60'));

        token = stream->PeekValue();
        REQUIRE(token.m_type == static_cast<token_type_t>('\x60'));

        token = stream->NextValue();
        REQUIRE(token.m_type == static_cast<token_type_t>('\x60'));

        token = stream->NextValue();
        REQUIRE(token.m_type == TOKEN_EOF);
    }

    TEST_CASE("TokenInputStream: Ensure can read string token", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_STRING) << "Hello World" << '\x00';

        auto token = stream->NextValue();
        REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_STRING));
        REQUIRE(token.m_string_value == "Hello World");

        token = stream->NextValue();
        REQUIRE(token.m_type == TOKEN_EOF);
    }

    TEST_CASE("TokenInputStream: Ensure can read float token", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_FLOAT);
        constexpr float f = 3.14f;
        ss.write(reinterpret_cast<const char*>(&f), sizeof(f));

        auto token = stream->NextValue();
        REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_FLOAT));
        REQUIRE_THAT(token.m_float_value, WithinAbs(static_cast<double>(3.14f), FLOAT_EPS));

        token = stream->NextValue();
        REQUIRE(token.m_type == TOKEN_EOF);
    }

    TEST_CASE("TokenInputStream: Ensure can read int token", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_INT);
        constexpr int32_t i = 1337;
        ss.write(reinterpret_cast<const char*>(&i), sizeof(i));

        auto token = stream->NextValue();
        REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_INT));
        REQUIRE(token.m_int_value == 1337);

        token = stream->NextValue();
        REQUIRE(token.m_type == TOKEN_EOF);
    }

    TEST_CASE("TokenInputStream: Ensure can read int8 token", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_INT8);
        constexpr int8_t i = 42;
        ss.write(reinterpret_cast<const char*>(&i), sizeof(i));

        auto token = stream->NextValue();
        REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_INT));
        REQUIRE(token.m_int_value == 42);

        token = stream->NextValue();
        REQUIRE(token.m_type == TOKEN_EOF);
    }

    TEST_CASE("TokenInputStream: Ensure can read uint8 token", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_UINT8);
        constexpr uint8_t i = 142u;
        ss.write(reinterpret_cast<const char*>(&i), sizeof(i));

        auto token = stream->NextValue();
        REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_INT));
        REQUIRE(token.m_int_value == 142);

        token = stream->NextValue();
        REQUIRE(token.m_type == TOKEN_EOF);
    }

    TEST_CASE("TokenInputStream: Ensure can read int16 token", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_INT16);
        constexpr int16_t i = 21588;
        ss.write(reinterpret_cast<const char*>(&i), sizeof(i));

        auto token = stream->NextValue();
        REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_INT));
        REQUIRE(token.m_int_value == 21588);

        token = stream->NextValue();
        REQUIRE(token.m_type == TOKEN_EOF);
    }

    TEST_CASE("TokenInputStream: Ensure can read uint16 token", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_UINT16);
        constexpr uint16_t i = 54356u;
        ss.write(reinterpret_cast<const char*>(&i), sizeof(i));

        auto token = stream->NextValue();
        REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_INT));
        REQUIRE(token.m_int_value == 54356);

        token = stream->NextValue();
        REQUIRE(token.m_type == TOKEN_EOF);
    }

    TEST_CASE("TokenInputStream: Ensure can read fp16man12 token", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_FP16_MAN_12);
        constexpr uint16_t i = 0x435C;
        ss.write(reinterpret_cast<const char*>(&i), sizeof(i));

        auto token = stream->NextValue();
        REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_FLOAT));
        REQUIRE_THAT(token.m_float_value, WithinAbs(4.21, 0.000244140625));

        token = stream->NextValue();
        REQUIRE(token.m_type == TOKEN_EOF);
    }

    TEST_CASE("TokenInputStream: Ensure can read fp16man9 token", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_FP16_MAN_9);
        constexpr uint16_t i = 0x86;
        ss.write(reinterpret_cast<const char*>(&i), sizeof(i));

        auto token = stream->NextValue();
        REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_FLOAT));
        REQUIRE_THAT(token.m_float_value, WithinAbs(4.21, 0.03125));

        token = stream->NextValue();
        REQUIRE(token.m_type == TOKEN_EOF);
    }

    TEST_CASE("TokenInputStream: Ensure can read fp16man0 token", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_FP16_MAN_0);
        constexpr uint16_t i = 1337;
        ss.write(reinterpret_cast<const char*>(&i), sizeof(i));

        auto token = stream->NextValue();
        REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_FLOAT));
        REQUIRE_THAT(token.m_float_value, WithinAbs(1337, FLOAT_EPS));

        token = stream->NextValue();
        REQUIRE(token.m_type == TOKEN_EOF);
    }

    TEST_CASE("TokenInputStream: Ensure can read fp8 token", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_FP8);
        constexpr int8_t i = 53;
        ss.write(reinterpret_cast<const char*>(&i), sizeof(i));

        auto token = stream->NextValue();
        REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_FLOAT));
        REQUIRE_THAT(token.m_float_value, WithinAbs(0.421, 0.0078740157480315));

        token = stream->NextValue();
        REQUIRE(token.m_type == TOKEN_EOF);
    }

    TEST_CASE("TokenInputStream: Ensure can read wchar token", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_WCHAR);
        constexpr uint16_t i = 0x8446;
        ss.write(reinterpret_cast<const char*>(&i), sizeof(i));

        auto token = stream->NextValue();
        REQUIRE(token.m_type == static_cast<token_type_t>(0x8446));

        token = stream->NextValue();
        REQUIRE(token.m_type == TOKEN_EOF);
    }

    TEST_CASE("TokenInputStream: Ensure can read simple tokens", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);

        const auto tokenType = GENERATE(TOKEN_COMMA, TOKEN_LEFT_CURLY, TOKEN_RIGHT_CURLY, TOKEN_LEFT_BRACKET, TOKEN_RIGHT_BRACKET, TOKEN_COMMA, TOKEN_SEMICOLON, TOKEN_CUSTOM_FIRST, 99);
        ss << static_cast<char>(tokenType);

        INFO("Simple token recognized: " << tokenType);

        auto token = stream->NextValue();
        REQUIRE(token.m_type == static_cast<token_type_t>(tokenType));

        token = stream->NextValue();
        REQUIRE(token.m_type == TOKEN_EOF);
    }

    TEST_CASE("TokenInputStream: Ensure can read array of simple tokens", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);

        ss << static_cast<char>(TOKEN_ARRAY);

        constexpr uint16_t arraySize = 3u;
        ss.write(reinterpret_cast<const char*>(&arraySize), sizeof(arraySize));

        ss << static_cast<char>(TOKEN_COMMA);

        auto token = stream->NextValue();
        REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_COMMA));

        token = stream->NextValue();
        REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_COMMA));

        token = stream->NextValue();
        REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_COMMA));

        token = stream->NextValue();
        REQUIRE(token.m_type == TOKEN_EOF);
    }

    TEST_CASE("TokenInputStream: Ensure can read array of wchar tokens", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);

        ss << static_cast<char>(TOKEN_ARRAY);

        constexpr uint16_t arraySize = 4u;
        ss.write(reinterpret_cast<const char*>(&arraySize), sizeof(arraySize));

        ss << static_cast<char>(TOKEN_WCHAR);

        constexpr uint16_t i = 0x8446;
        ss.write(reinterpret_cast<const char*>(&i), sizeof(i));

        auto token = stream->NextValue();
        REQUIRE(token.m_type == static_cast<token_type_t>(0x8446));

        token = stream->NextValue();
        REQUIRE(token.m_type == static_cast<token_type_t>(0x8446));

        token = stream->NextValue();
        REQUIRE(token.m_type == static_cast<token_type_t>(0x8446));

        token = stream->NextValue();
        REQUIRE(token.m_type == static_cast<token_type_t>(0x8446));

        token = stream->NextValue();
        REQUIRE(token.m_type == TOKEN_EOF);
    }

    TEST_CASE("TokenInputStream: Ensure can read array of token with following data", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);

        ss << static_cast<char>(TOKEN_ARRAY);

        constexpr uint16_t arraySize = 3u;
        ss.write(reinterpret_cast<const char*>(&arraySize), sizeof(arraySize));

        ss << static_cast<char>(TOKEN_INT);

        constexpr int32_t i0 = 1337;
        ss.write(reinterpret_cast<const char*>(&i0), sizeof(i0));

        constexpr int32_t i1 = 457;
        ss.write(reinterpret_cast<const char*>(&i1), sizeof(i1));

        constexpr int32_t i2 = 13361338;
        ss.write(reinterpret_cast<const char*>(&i2), sizeof(i2));

        auto token = stream->NextValue();
        REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_INT));
        REQUIRE(token.m_int_value == 1337);

        token = stream->NextValue();
        REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_INT));
        REQUIRE(token.m_int_value == 457);

        token = stream->NextValue();
        REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_INT));
        REQUIRE(token.m_int_value == 13361338);

        token = stream->NextValue();
        REQUIRE(token.m_type == TOKEN_EOF);
    }

    TEST_CASE("TokenInputStream: Ensure can read unknown", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);

        ss << static_cast<char>(TOKEN_UNKNOWN);

        constexpr int32_t i0 = 1337;
        ss.write(reinterpret_cast<const char*>(&i0), sizeof(i0));

        auto token = stream->NextValue();
        REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_LEFT_BRACKET));

        token = stream->NextValue();
        REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_INT));
        REQUIRE(token.m_int_value == 1337);

        token = stream->NextValue();
        REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_RIGHT_BRACKET));

        token = stream->NextValue();
        REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_RIGHT_BRACKET));

        token = stream->NextValue();
        REQUIRE(token.m_type == TOKEN_EOF);
    }

    TEST_CASE("TokenInputStream: Ensure can read struct", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);

        const auto structTokenIndex = GENERATE(TOKEN_STRUCT_FIRST, (TOKEN_STRUCT_FIRST + 4), TOKEN_STRUCT_LAST);
        ss << static_cast<char>(TOKEN_STRUCT_DEF) << static_cast<char>(structTokenIndex);
        INFO("Struct with index: " << structTokenIndex);

        constexpr uint8_t memberCount = 4;
        ss.write(reinterpret_cast<const char*>(&memberCount), sizeof(memberCount));

        ss << static_cast<char>(TOKEN_COMMA) << static_cast<char>(TOKEN_INT) << static_cast<char>(TOKEN_WCHAR);

        constexpr uint16_t i = 0x8446;
        ss.write(reinterpret_cast<const char*>(&i), sizeof(i));

        ss << static_cast<char>(TOKEN_INT8);

        SECTION("...once")
        {
            ss << static_cast<char>(structTokenIndex);

            constexpr int32_t value0 = 13361338;
            ss.write(reinterpret_cast<const char*>(&value0), sizeof(value0));

            constexpr int8_t value1 = 42;
            ss.write(reinterpret_cast<const char*>(&value1), sizeof(value1));

            auto token = stream->NextValue();
            REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_COMMA));

            token = stream->NextValue();
            REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_INT));
            REQUIRE(token.m_int_value == 13361338);

            token = stream->NextValue();
            REQUIRE(token.m_type == static_cast<token_type_t>(0x8446));

            token = stream->NextValue();
            REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_INT));
            REQUIRE(token.m_int_value == 42);

            token = stream->NextValue();
            REQUIRE(token.m_type == TOKEN_EOF);
        }

        SECTION("...twice")
        {
            ss << static_cast<char>(structTokenIndex);

            constexpr int32_t value0 = 13361338;
            ss.write(reinterpret_cast<const char*>(&value0), sizeof(value0));

            constexpr int8_t value1 = 42;
            ss.write(reinterpret_cast<const char*>(&value1), sizeof(value1));

            ss << static_cast<char>(structTokenIndex);

            constexpr int32_t value2 = 55554444;
            ss.write(reinterpret_cast<const char*>(&value2), sizeof(value2));

            constexpr int8_t value3 = -3;
            ss.write(reinterpret_cast<const char*>(&value3), sizeof(value3));

            // First struct

            auto token = stream->NextValue();
            REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_COMMA));

            token = stream->NextValue();
            REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_INT));
            REQUIRE(token.m_int_value == 13361338);

            token = stream->NextValue();
            REQUIRE(token.m_type == static_cast<token_type_t>(0x8446));

            token = stream->NextValue();
            REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_INT));
            REQUIRE(token.m_int_value == 42);

            // Second struct

            token = stream->NextValue();
            REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_COMMA));

            token = stream->NextValue();
            REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_INT));
            REQUIRE(token.m_int_value == 55554444);

            token = stream->NextValue();
            REQUIRE(token.m_type == static_cast<token_type_t>(0x8446));

            token = stream->NextValue();
            REQUIRE(token.m_type == static_cast<token_type_t>(TOKEN_INT));
            REQUIRE(token.m_int_value == -3);

            token = stream->NextValue();
            REQUIRE(token.m_type == TOKEN_EOF);
        }
    }

    TEST_CASE("TokenInputStream: Ensure cannot specify struct index out of bounds", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);

        const auto structTokenIndex = GENERATE(-125, 0, TOKEN_STRUCT_FIRST - 1, TOKEN_STRUCT_LAST + 1, 127);
        ss << static_cast<char>(TOKEN_STRUCT_DEF) << static_cast<char>(structTokenIndex);

        constexpr uint8_t memberCount = 2;
        ss.write(reinterpret_cast<const char*>(&memberCount), sizeof(memberCount));

        ss << static_cast<char>(TOKEN_COMMA) << static_cast<char>(TOKEN_SEMICOLON);
        ss << static_cast<char>(structTokenIndex);

        INFO("Struct with index: " << structTokenIndex);
        REQUIRE_THROWS_AS(stream->NextValue(), TokenStreamException);
    }

    TEST_CASE("TokenInputStream: Ensure cannot specify struct more than once", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);

        // First definition
        ss << static_cast<char>(TOKEN_STRUCT_DEF) << static_cast<char>(TOKEN_STRUCT_FIRST);

        constexpr uint8_t memberCount0 = 2;
        ss.write(reinterpret_cast<const char*>(&memberCount0), sizeof(memberCount0));

        ss << static_cast<char>(TOKEN_COMMA) << static_cast<char>(TOKEN_SEMICOLON);

        // Second definition
        ss << static_cast<char>(TOKEN_STRUCT_DEF) << static_cast<char>(TOKEN_STRUCT_FIRST);

        constexpr uint8_t memberCount1 = 3;
        ss.write(reinterpret_cast<const char*>(&memberCount1), sizeof(memberCount1));

        ss << static_cast<char>(TOKEN_LEFT_BRACKET) << static_cast<char>(TOKEN_SEMICOLON) << static_cast<char>(TOKEN_RIGHT_BRACKET);

        // Write struct
        ss << static_cast<char>(TOKEN_STRUCT_FIRST);

        REQUIRE_THROWS_AS(stream->NextValue(), TokenStreamException);
    }

    TEST_CASE("TokenInputStream: Ensure can use NextIntegerValue when token is integer", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_INT);
        constexpr int32_t i = 1337;
        ss.write(reinterpret_cast<const char*>(&i), sizeof(i));

        const auto value = stream->NextIntegerValue();
        REQUIRE(value == 1337);

        const auto token = stream->NextValue();
        REQUIRE(token.m_type == TOKEN_EOF);
    }

    TEST_CASE("TokenInputStream: Ensure NextIntegerValue throws when token is not integer", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_SEMICOLON);

        REQUIRE_THROWS_AS(stream->NextIntegerValue(), TokenStreamException);
    }

    TEST_CASE("TokenInputStream: Ensure can use NextStringValue when next token is string", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_STRING) << "Hello World" << '\x00';

        const auto value = stream->NextStringValue();
        REQUIRE(value == "Hello World");

        const auto token = stream->NextValue();
        REQUIRE(token.m_type == TOKEN_EOF);
    }

    TEST_CASE("TokenInputStream: Ensure NextStringValue throws when token is not string", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_SEMICOLON);

        REQUIRE_THROWS_AS(stream->NextStringValue(), TokenStreamException);
    }

    TEST_CASE("TokenInputStream: Ensure can use NextFloatValue when token is float", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_FLOAT);
        constexpr float f = 4.20f;
        ss.write(reinterpret_cast<const char*>(&f), sizeof(f));

        const auto value = stream->NextFloatValue();
        REQUIRE_THAT(value, WithinAbs(static_cast<double>(4.20f), FLOAT_EPS));

        const auto token = stream->NextValue();
        REQUIRE(token.m_type == TOKEN_EOF);
    }

    TEST_CASE("TokenInputStream: Ensure NextFloatValue throws when token is not float", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_SEMICOLON);

        REQUIRE_THROWS_AS(stream->NextFloatValue(), TokenStreamException);
    }

    TEST_CASE("TokenInputStream: Ensure ExpectToken succeeds when type matches", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_SEMICOLON);

        REQUIRE_NOTHROW(stream->ExpectToken(TOKEN_SEMICOLON));
    }

    TEST_CASE("TokenInputStream: Ensure ExpectToken throws when type does not match", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_SEMICOLON);

        REQUIRE_THROWS_AS(stream->ExpectToken(TOKEN_COMMA), TokenStreamException);
    }

    TEST_CASE("TokenOutputStream: Ensure WriteString outputs correct data", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenOutputStream::Create(ss);

        stream->WriteString("Hello World");

        const auto output = ss.str();

        constexpr uint8_t expectedOutput[]
        {
            static_cast<uint8_t>(TOKEN_STRING),
            'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd',
            '\x00'
        };

        REQUIRE(output.size() == std::extent_v<decltype(expectedOutput)>);
        REQUIRE(output == std::string(reinterpret_cast<const char*>(expectedOutput), std::extent_v<decltype(expectedOutput)>));
    }

    TEST_CASE("TokenOutputStream: Ensure WriteFloat outputs correct data", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenOutputStream::Create(ss);

        stream->WriteFloat(1337.0f);

        const auto output = ss.str();

        constexpr uint8_t expectedOutput[]
        {
            static_cast<uint8_t>(TOKEN_FLOAT),

            // 0x44a72000 -> 1337.0f
            0x00, 0x20, 0xa7, 0x44
        };

        REQUIRE(output.size() == std::extent_v<decltype(expectedOutput)>);
        REQUIRE(output == std::string(reinterpret_cast<const char*>(expectedOutput), std::extent_v<decltype(expectedOutput)>));
    }

    TEST_CASE("TokenOutputStream: Ensure WriteInteger outputs correct data", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenOutputStream::Create(ss);

        stream->WriteInteger(13361338);

        const auto output = ss.str();

        constexpr uint8_t expectedOutput[]
        {
            static_cast<uint8_t>(TOKEN_INT),
            0xBA, 0xE0, 0xCB, 0x00
        };

        REQUIRE(output.size() == std::extent_v<decltype(expectedOutput)>);
        REQUIRE(output == std::string(reinterpret_cast<const char*>(expectedOutput), std::extent_v<decltype(expectedOutput)>));
    }

    TEST_CASE("TokenOutputStream: Ensure simple token methods output correct data", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenOutputStream::Create(ss);

        token_type_t token = TOKEN_UNKNOWN;

        SECTION("Token: left curly")
        {
            stream->WriteLeftCurly();
            token = TOKEN_LEFT_CURLY;
        }

        SECTION("Token: right curly")
        {
            stream->WriteRightCurly();
            token = TOKEN_RIGHT_CURLY;
        }

        SECTION("Token: left bracket")
        {
            stream->WriteLeftBracket();
            token = TOKEN_LEFT_BRACKET;
        }

        SECTION("Token: right bracket")
        {
            stream->WriteRightBracket();
            token = TOKEN_RIGHT_BRACKET;
        }

        SECTION("Token: comma")
        {
            stream->WriteComma();
            token = TOKEN_COMMA;
        }

        SECTION("Token: semicolon")
        {
            stream->WriteSemicolon();
            token = TOKEN_SEMICOLON;
        }

        const auto output = ss.str();

        const uint8_t expectedOutput[]
        {
            static_cast<uint8_t>(token)
        };

        REQUIRE(output.size() == std::extent_v<decltype(expectedOutput)>);
        REQUIRE(output == std::string(reinterpret_cast<const char*>(expectedOutput), std::extent_v<decltype(expectedOutput)>));
    }

    TEST_CASE("TokenOutputStream: Ensure WriteInt8 outputs correct data", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenOutputStream::Create(ss);

        stream->WriteInt8(42);

        const auto output = ss.str();

        constexpr uint8_t expectedOutput[]
        {
            static_cast<uint8_t>(TOKEN_INT8),
            0x2A
        };

        REQUIRE(output.size() == std::extent_v<decltype(expectedOutput)>);
        REQUIRE(output == std::string(reinterpret_cast<const char*>(expectedOutput), std::extent_v<decltype(expectedOutput)>));
    }

    TEST_CASE("TokenOutputStream: Ensure WriteUInt8 outputs correct data", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenOutputStream::Create(ss);

        stream->WriteUInt8(174);

        const auto output = ss.str();

        constexpr uint8_t expectedOutput[]
        {
            static_cast<uint8_t>(TOKEN_UINT8),
            0xAE
        };

        REQUIRE(output.size() == std::extent_v<decltype(expectedOutput)>);
        REQUIRE(output == std::string(reinterpret_cast<const char*>(expectedOutput), std::extent_v<decltype(expectedOutput)>));
    }

    TEST_CASE("TokenOutputStream: Ensure WriteInt16 outputs correct data", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenOutputStream::Create(ss);

        stream->WriteInt16(24750);

        const auto output = ss.str();

        constexpr uint8_t expectedOutput[]
        {
            static_cast<uint8_t>(TOKEN_INT16),
            0xAE, 0x60
        };

        REQUIRE(output.size() == std::extent_v<decltype(expectedOutput)>);
        REQUIRE(output == std::string(reinterpret_cast<const char*>(expectedOutput), std::extent_v<decltype(expectedOutput)>));
    }

    TEST_CASE("TokenOutputStream: Ensure WriteUInt16 outputs correct data", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenOutputStream::Create(ss);

        stream->WriteUInt16(42134);

        const auto output = ss.str();

        constexpr uint8_t expectedOutput[]
        {
            static_cast<uint8_t>(TOKEN_UINT16),
            0x96, 0xA4
        };

        REQUIRE(output.size() == std::extent_v<decltype(expectedOutput)>);
        REQUIRE(output == std::string(reinterpret_cast<const char*>(expectedOutput), std::extent_v<decltype(expectedOutput)>));
    }

    TEST_CASE("TokenOutputStream: Ensure WriteFp16Man12 outputs correct data", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenOutputStream::Create(ss);

        stream->WriteFp16Man12(3.03125f);

        const auto output = ss.str();

        constexpr uint8_t expectedOutput[]
        {
            static_cast<uint8_t>(TOKEN_FP16_MAN_12),
            0x80, 0x30
        };

        REQUIRE(output.size() == std::extent_v<decltype(expectedOutput)>);
        REQUIRE(output == std::string(reinterpret_cast<const char*>(expectedOutput), std::extent_v<decltype(expectedOutput)>));
    }

    TEST_CASE("TokenOutputStream: Ensure WriteFp16Man9 outputs correct data", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenOutputStream::Create(ss);

        stream->WriteFp16Man9(42.96875f);

        const auto output = ss.str();

        constexpr uint8_t expectedOutput[]
        {
            static_cast<uint8_t>(TOKEN_FP16_MAN_9),
            0x5F, 0x05
        };

        REQUIRE(output.size() == std::extent_v<decltype(expectedOutput)>);
        REQUIRE(output == std::string(reinterpret_cast<const char*>(expectedOutput), std::extent_v<decltype(expectedOutput)>));
    }

    TEST_CASE("TokenOutputStream: Ensure WriteFp16Man0 outputs correct data", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenOutputStream::Create(ss);

        stream->WriteFp16Man0(25931.0f);

        const auto output = ss.str();

        constexpr uint8_t expectedOutput[]
        {
            static_cast<uint8_t>(TOKEN_FP16_MAN_0),
            0x4B, 0x65
        };

        REQUIRE(output.size() == std::extent_v<decltype(expectedOutput)>);
        REQUIRE(output == std::string(reinterpret_cast<const char*>(expectedOutput), std::extent_v<decltype(expectedOutput)>));
    }

    TEST_CASE("TokenOutputStream: Ensure WriteFp8 outputs correct data", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenOutputStream::Create(ss);

        stream->WriteFp8(0.42f);

        const auto output = ss.str();

        constexpr uint8_t expectedOutput[]
        {
            static_cast<uint8_t>(TOKEN_FP8),
            0x35
        };

        REQUIRE(output.size() == std::extent_v<decltype(expectedOutput)>);
        REQUIRE(output == std::string(reinterpret_cast<const char*>(expectedOutput), std::extent_v<decltype(expectedOutput)>));
    }

    TEST_CASE("TokenOutputStream: Ensure WriteWChar outputs correct data", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenOutputStream::Create(ss);

        stream->WriteWChar(22077);

        const auto output = ss.str();

        constexpr uint8_t expectedOutput[]
        {
            static_cast<uint8_t>(TOKEN_WCHAR),
            0x3D, 0x56
        };

        REQUIRE(output.size() == std::extent_v<decltype(expectedOutput)>);
        REQUIRE(output == std::string(reinterpret_cast<const char*>(expectedOutput), std::extent_v<decltype(expectedOutput)>));
    }

    TEST_CASE("TokenOutputStream: Ensure WriteCustom outputs correct data", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenOutputStream::Create(ss);

        stream->WriteCustom(42);

        const auto output = ss.str();

        constexpr uint8_t expectedOutput[]
        {
            0x2A
        };

        REQUIRE(output.size() == std::extent_v<decltype(expectedOutput)>);
        REQUIRE(output == std::string(reinterpret_cast<const char*>(expectedOutput), std::extent_v<decltype(expectedOutput)>));
    }
}
