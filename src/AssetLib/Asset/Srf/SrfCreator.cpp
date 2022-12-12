#include "SrfCreator.h"

#include <limits>
#include <iostream>
#include <sstream>
#include <vector>

#include "Endianness.h"
#include "StringUtils.h"

class SrfCreationException final : public std::exception
{
public:
    explicit SrfCreationException(std::string msg)
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

namespace creation
{
    std::vector<std::string> SplitSrfDataIntoStrings(const void* inputData, const size_t inputDataSize)
    {
        std::vector<std::string> strings;
        bool hasStringData = false;
        std::ostringstream ss;

        auto* text = static_cast<const char*>(inputData);
        for (auto i = 0u; i < inputDataSize; i++)
        {
            const auto& c = text[i];
            switch (c)
            {
            case '\\':
                if (i + 1 < inputDataSize)
                {
                    const auto& c1 = text[i + 1];
                    if (c1 == 'r')
                        ss << "\r";
                    else if (c1 == 'n')
                        ss << "\n";
                    else
                        ss << c1;
                    i++;
                    hasStringData = true;
                }
                else
                    throw SrfCreationException("Last character of Srf cannot be \\");
                break;

            case '\r':
                if (i + 1 < inputDataSize && text[i + 1] == '\n')
                {
                    if (hasStringData)
                    {
                        strings.emplace_back(ss.str());
                        ss.str(std::string());
                        hasStringData = false;
                    }
                }
                else
                {
                    ss << c;
                    hasStringData = true;
                }
                break;

            case '\n':
                if (hasStringData)
                {
                    strings.emplace_back(ss.str());
                    ss.str(std::string());
                    hasStringData = false;
                }
                break;

            default:
                ss << c;
                hasStringData = true;
                break;
            }
        }

        if (hasStringData)
            strings.emplace_back(ss.str());

        return strings;
    }

    void CreateSrfBuffer(const std::vector<std::string>& inStrings, std::vector<size_t>& outStringOffsets, std::wstring& outStringDataBuffer)
    {
        std::wostringstream ss;
        size_t offset = 0u;
        for (const auto& str : inStrings)
        {
            outStringOffsets.emplace_back(offset);
            const auto wStr = utils::ConvertStringToWString(str);
            ss << wStr << L'\0';
            offset += wStr.size() + 1;
        }

        outStringDataBuffer = ss.str();
    }
}

using namespace creation;

bool SrfCreator::SupportFileExtension(const std::string& extension) const
{
    return extension == ".SRF";
}

void SrfCreator::ProcessFile(const std::string& filePath, const void* inputData, const size_t inputDataSize, std::ostream& output) const
{
    std::cout << "Srf creating \"" << filePath << "\"\n";

    const auto strings = SplitSrfDataIntoStrings(inputData, inputDataSize);

    if (strings.size() > std::numeric_limits<uint16_t>::max())
        throw SrfCreationException("Srf has too many strings");

    std::vector<size_t> stringOffsets;
    std::wstring stringDataBuffer;
    CreateSrfBuffer(strings, stringOffsets, stringDataBuffer);

    if (stringDataBuffer.size() > std::numeric_limits<uint16_t>::max())
        throw SrfCreationException("Srf has too much data");

    const uint16_t diskStringCount = endianness::ToLittleEndian(static_cast<uint16_t>(stringOffsets.size()));
    const uint16_t diskDataSize = endianness::ToLittleEndian(static_cast<uint16_t>(stringDataBuffer.size()));

    output.write(reinterpret_cast<const char*>(&diskStringCount), sizeof(diskStringCount));
    output.write(reinterpret_cast<const char*>(&diskDataSize), sizeof(diskDataSize));

    for (const auto& offset : stringOffsets)
    {
        const uint16_t diskOffset = endianness::ToLittleEndian(static_cast<uint16_t>(offset));
        output.write(reinterpret_cast<const char*>(&diskOffset), sizeof(diskOffset));
    }

    output.write(reinterpret_cast<const char*>(stringDataBuffer.data()), static_cast<size_t>(sizeof(wchar_t) * stringDataBuffer.size()));
}
