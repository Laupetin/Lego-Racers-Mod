#include <catch2/catch_test_macros.hpp>
#include "catch2/generators/catch_generators.hpp"

#include <sstream>
#include <type_traits>

#include "Asset/PassthroughCreator.h"

namespace test::asset::passthrough_creator
{
    TEST_CASE("PassthroughCreator: Ensure can match any extension", "[passthough][creator]")
    {
        const PassthroughCreator creator;
        const auto extension = GENERATE(".txt", ".asdf", ".lol", ".gdb");

        INFO("Extension: " << extension);
        REQUIRE(creator.SupportFileExtension(extension) == true);
    }

    TEST_CASE("PassthroughCreator: Ensure just writes input data to output", "[passthough][creator]")
    {
        const PassthroughCreator creator;
        std::ostringstream output;

        constexpr uint8_t input[]
        {
            0x24, 0x00, 0x12, 0x20, 0x0A, 0xFF, 0xDA
        };

        creator.ProcessFile("TESTFILE", input, std::extent_v<decltype(input)>, output);

        const auto inputStr = std::string(reinterpret_cast<const char*>(input), std::extent_v<decltype(input)>);
        const auto outputStr = output.str();
        REQUIRE(inputStr == outputStr);
    }
}