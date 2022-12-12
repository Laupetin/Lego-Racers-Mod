#include "SrfDumper.h"

#include <string>
#include <iostream>
#include <exception>
#include <memory>
#include <sstream>

#include "StreamUtils.h"
#include "StringUtils.h"
#include "Endianness.h"

class SrfDumpingException final : public std::exception
{
public:
    explicit SrfDumpingException(std::string msg)
        : m_msg(std::move(msg))
    {
    }

    [[nodiscard]] char const* what() const noexcept override
    {
        return m_msg.c_str();
    }

private:
    std::string m_msg;
};

bool SrfDumper::SupportFileExtension(const std::string& extension) const
{
    return extension == ".SRF";
}

void SrfDumper::ProcessFile(const std::string& filePath, std::istream& input, std::ostream& output) const
{
    std::cout << "SRF dumping \"" << filePath << "\"\n";

    uint16_t stringCount;
    uint16_t stringDataSize;

    utils::ReadOrThrow(input, &stringCount, sizeof(stringCount));
    stringCount = endianness::FromLittleEndian(stringCount);

    utils::ReadOrThrow(input, &stringDataSize, sizeof(stringDataSize));
    stringDataSize = endianness::FromLittleEndian(stringDataSize);

    const auto stringOffsets = std::make_unique<uint16_t[]>(stringCount);
    const auto stringData = std::make_unique<wchar_t[]>(stringDataSize);

    utils::ReadOrThrow(input, stringOffsets.get(), sizeof(uint16_t) * stringCount);
    utils::ReadOrThrow(input, stringData.get(), sizeof(wchar_t) * stringDataSize);

    for (auto stringIndex = 0u; stringIndex < stringCount; stringIndex++)
    {
        const auto stringOffset = endianness::FromLittleEndian(stringOffsets[stringIndex]);

        if (stringOffset >= stringDataSize)
            throw SrfDumpingException("String offset out of bounds");

        const auto stringMaxLength = stringDataSize - stringOffset;
        const auto pStr = &stringData[stringOffset];
        const auto strLen = wcsnlen(pStr, stringMaxLength);

        const std::wstring wstr(pStr, strLen);
        std::string str = utils::ConvertWStringToString(wstr);

        std::ostringstream ss;
        for (const auto& c : str)
        {
            switch (c)
            {
            case '\r':
                ss << "\\r";
                break;
            case '\n':
                ss << "\\n";
                break;
            case '\\':
                ss << "\\\\";
                break;
            default:
                ss << c;
                break;
            }
        }

        output << ss.str() << "\n";
    }
}
