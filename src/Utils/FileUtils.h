#pragma once

#include <cstdint>

namespace utils
{
    static constexpr auto ILLEGAL_PATH_CHARS = R"(<>:"|?*)";
    static constexpr auto ILLEGAL_FILENAME_CHARS = R"(<>:"/\|?*)";

    static constexpr uint16_t MakeMagic16(const char ch0, const char ch1)
    {
        return static_cast<uint16_t>(static_cast<uint16_t>(ch0) | static_cast<uint16_t>(ch1) << 8);
    }

    static constexpr uint32_t MakeMagic32(const char ch0, const char ch1, const char ch2, const char ch3)
    {
        return static_cast<uint32_t>(ch0) | static_cast<uint32_t>(ch1) << 8 | static_cast<uint32_t>(ch2) << 16 | static_cast<uint32_t>(ch3) << 24;
    }
}; // namespace utils
