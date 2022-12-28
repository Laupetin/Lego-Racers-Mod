#include "SrfBinaryReader.h"

#include <sstream>

#include "Endianness.h"
#include "StreamUtils.h"
#include "StringUtils.h"
#include "TokenStream.h"

namespace srf
{
    class SrfBinaryReadingException final : public std::exception
    {
    public:
        explicit SrfBinaryReadingException(std::string msg)
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

    class SrfBinaryReaderImpl
    {
    public:
        SrfBinaryReaderImpl(std::istream& in, ISrfEmitter& emitter)
            : m_stream(in),
              m_emitter(emitter)
        {
        }

        void Read() const
        {
            uint16_t stringCount;
            uint16_t stringDataSize;

            utils::ReadOrThrow(m_stream, &stringCount, sizeof(stringCount));
            stringCount = endianness::FromLittleEndian(stringCount);

            utils::ReadOrThrow(m_stream, &stringDataSize, sizeof(stringDataSize));
            stringDataSize = endianness::FromLittleEndian(stringDataSize);

            const auto stringOffsets = std::make_unique<uint16_t[]>(stringCount);
            const auto stringData = std::make_unique<wchar_t[]>(stringDataSize);

            utils::ReadOrThrow(m_stream, stringOffsets.get(), sizeof(uint16_t) * stringCount);
            utils::ReadOrThrow(m_stream, stringData.get(), sizeof(wchar_t) * stringDataSize);

            m_emitter.StartStrings();
            for (auto stringIndex = 0u; stringIndex < stringCount; stringIndex++)
            {
                const auto stringOffset = endianness::FromLittleEndian(stringOffsets[stringIndex]);

                if (stringOffset >= stringDataSize)
                    throw SrfBinaryReadingException("String offset out of bounds");

                const auto stringMaxLength = stringDataSize - stringOffset;
                const auto pStr = &stringData[stringOffset];
                const auto strLen = wcsnlen(pStr, stringMaxLength);

                const std::wstring wstr(pStr, strLen);
                std::string str = utils::ConvertWStringToString(wstr);
                m_emitter.EmitString(std::move(str));
            }
            m_emitter.EndStrings();
        }

    private:
        std::istream& m_stream;
        ISrfEmitter& m_emitter;
    };
}

using namespace srf;

void SrfBinaryReader::Read(std::istream& input, ISrfEmitter& emitter)
{
    const SrfBinaryReaderImpl impl(input, emitter);
    impl.Read();
}
