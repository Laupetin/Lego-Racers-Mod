#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <cstdint>
#include <limits>
#include <sstream>

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
        ss.seekg(0, std::ios::beg);

        const auto token0 = stream->NextValue();
        REQUIRE(token0.m_type == static_cast<token_type_t>('\x60'));

        const auto token1 = stream->NextValue();
        REQUIRE(token1.m_type == TOKEN_EOF);
    }

    TEST_CASE("TokenInputStream: Ensure PeekValue does not consume next token", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << '\x60';
        ss.seekg(0, std::ios::beg);

        const auto token0 = stream->PeekValue();
        REQUIRE(token0.m_type == static_cast<token_type_t>('\x60'));

        const auto token1 = stream->PeekValue();
        REQUIRE(token1.m_type == static_cast<token_type_t>('\x60'));

        const auto token2 = stream->NextValue();
        REQUIRE(token2.m_type == static_cast<token_type_t>('\x60'));

        const auto token3 = stream->NextValue();
        REQUIRE(token3.m_type == TOKEN_EOF);
    }

    TEST_CASE("TokenInputStream: Ensure can read string token", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_STRING) << "Hello World" << '\x00';
        ss.seekg(0, std::ios::beg);

        const auto token0 = stream->NextValue();
        REQUIRE(token0.m_type == static_cast<token_type_t>(TOKEN_STRING));
        REQUIRE(token0.m_string_value == "Hello World");
    }

    TEST_CASE("TokenInputStream: Ensure can read float token", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_FLOAT);
        constexpr float f = 3.14f;
        ss.write(reinterpret_cast<const char*>(&f), sizeof(f));

        ss.seekg(0, std::ios::beg);

        const auto token0 = stream->NextValue();
        REQUIRE(token0.m_type == static_cast<token_type_t>(TOKEN_FLOAT));
        REQUIRE_THAT(token0.m_float_value, WithinAbs(3.14, FLOAT_EPS));
    }

    TEST_CASE("TokenInputStream: Ensure can read int token", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_INT);
        constexpr int32_t i = 1337;
        ss.write(reinterpret_cast<const char*>(&i), sizeof(i));

        ss.seekg(0, std::ios::beg);

        const auto token0 = stream->NextValue();
        REQUIRE(token0.m_type == static_cast<token_type_t>(TOKEN_INT));
        REQUIRE(token0.m_int_value == 1337);
    }

    TEST_CASE("TokenInputStream: Ensure can read int8 token", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_INT8);
        constexpr int8_t i = 42;
        ss.write(reinterpret_cast<const char*>(&i), sizeof(i));

        ss.seekg(0, std::ios::beg);

        const auto token0 = stream->NextValue();
        REQUIRE(token0.m_type == static_cast<token_type_t>(TOKEN_INT));
        REQUIRE(token0.m_int_value == 42);
    }

    TEST_CASE("TokenInputStream: Ensure can read uint8 token", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_UINT8);
        constexpr uint8_t i = 142u;
        ss.write(reinterpret_cast<const char*>(&i), sizeof(i));

        ss.seekg(0, std::ios::beg);

        const auto token0 = stream->NextValue();
        REQUIRE(token0.m_type == static_cast<token_type_t>(TOKEN_INT));
        REQUIRE(token0.m_int_value == 142);
    }

    TEST_CASE("TokenInputStream: Ensure can read int16 token", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_INT16);
        constexpr int16_t i = 21588;
        ss.write(reinterpret_cast<const char*>(&i), sizeof(i));

        ss.seekg(0, std::ios::beg);

        const auto token0 = stream->NextValue();
        REQUIRE(token0.m_type == static_cast<token_type_t>(TOKEN_INT));
        REQUIRE(token0.m_int_value == 21588);
    }

    TEST_CASE("TokenInputStream: Ensure can read uint16 token", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_UINT16);
        constexpr uint16_t i = 54356u;
        ss.write(reinterpret_cast<const char*>(&i), sizeof(i));

        ss.seekg(0, std::ios::beg);

        const auto token0 = stream->NextValue();
        REQUIRE(token0.m_type == static_cast<token_type_t>(TOKEN_INT));
        REQUIRE(token0.m_int_value == 54356);
    }

    TEST_CASE("TokenInputStream: Ensure can read fp16man12 token", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_FP16_MAN_12);
        constexpr uint16_t i = 0x435C;
        ss.write(reinterpret_cast<const char*>(&i), sizeof(i));

        ss.seekg(0, std::ios::beg);

        const auto token0 = stream->NextValue();
        REQUIRE(token0.m_type == static_cast<token_type_t>(TOKEN_FLOAT));
        REQUIRE_THAT(token0.m_float_value, WithinAbs(4.21, 0.000244140625));
    }

    TEST_CASE("TokenInputStream: Ensure can read fp16man9 token", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_FP16_MAN_9);
        constexpr uint16_t i = 0x86;
        ss.write(reinterpret_cast<const char*>(&i), sizeof(i));

        ss.seekg(0, std::ios::beg);

        const auto token0 = stream->NextValue();
        REQUIRE(token0.m_type == static_cast<token_type_t>(TOKEN_FLOAT));
        REQUIRE_THAT(token0.m_float_value, WithinAbs(4.21, 0.03125));
    }

    TEST_CASE("TokenInputStream: Ensure can read fp16man0 token", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_FP16_MAN_0);
        constexpr uint16_t i = 1337;
        ss.write(reinterpret_cast<const char*>(&i), sizeof(i));

        ss.seekg(0, std::ios::beg);

        const auto token0 = stream->NextValue();
        REQUIRE(token0.m_type == static_cast<token_type_t>(TOKEN_FLOAT));
        REQUIRE_THAT(token0.m_float_value, WithinAbs(1337, FLOAT_EPS));
    }

    TEST_CASE("TokenInputStream: Ensure can read fp8 token", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_FP8);
        constexpr int8_t i = 53;
        ss.write(reinterpret_cast<const char*>(&i), sizeof(i));

        ss.seekg(0, std::ios::beg);

        const auto token0 = stream->NextValue();
        REQUIRE(token0.m_type == static_cast<token_type_t>(TOKEN_FLOAT));
        REQUIRE_THAT(token0.m_float_value, WithinAbs(0.421, 0.0078740157480315));
    }

    TEST_CASE("TokenInputStream: Ensure can read wchar token", "[token][input]")
    {
        std::stringstream ss;
        const auto stream = ITokenInputStream::Create(ss);
        ss << static_cast<char>(TOKEN_WCHAR);
        constexpr uint16_t i = 0x8446;
        ss.write(reinterpret_cast<const char*>(&i), sizeof(i));

        ss.seekg(0, std::ios::beg);

        const auto token0 = stream->NextValue();
        REQUIRE(token0.m_type == static_cast<token_type_t>(0x8446));
    }
}
