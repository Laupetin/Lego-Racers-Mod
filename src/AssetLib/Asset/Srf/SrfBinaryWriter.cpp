#include "SrfBinaryWriter.h"

#include <limits>
#include <sstream>
#include <vector>

#include "Endianness.h"
#include "StringUtils.h"
#include "TokenStream.h"

namespace srf
{
    class SrfBinaryWriterException final : public std::exception
    {
    public:
        explicit SrfBinaryWriterException(std::string msg)
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

    class SrfBinaryWriterImpl final : public ISrfEmitter
    {
    public:
        explicit SrfBinaryWriterImpl(std::ostream& stream)
            : m_stream(stream),
              m_data_buffer_offset(0u)
        {
        }

        void StartStrings() override
        {
        }

        void EndStrings() override
        {
            if (m_string_offsets.size() > std::numeric_limits<uint16_t>::max())
                throw SrfBinaryWriterException("Srf has too many strings");

            if (m_data_buffer_offset > std::numeric_limits<uint16_t>::max())
                throw SrfBinaryWriterException("Srf has too much data");

            const auto stringDataBuffer = m_data_builder.str();
            const uint16_t diskStringCount = endianness::ToLittleEndian(static_cast<uint16_t>(m_string_offsets.size()));
            const uint16_t diskDataSize = endianness::ToLittleEndian(static_cast<uint16_t>(stringDataBuffer.size()));

            m_stream.write(reinterpret_cast<const char*>(&diskStringCount), sizeof(diskStringCount));
            m_stream.write(reinterpret_cast<const char*>(&diskDataSize), sizeof(diskDataSize));

            for (const auto& offset : m_string_offsets)
            {
                const uint16_t diskOffset = endianness::ToLittleEndian(static_cast<uint16_t>(offset));
                m_stream.write(reinterpret_cast<const char*>(&diskOffset), sizeof(diskOffset));
            }

            m_stream.write(reinterpret_cast<const char*>(stringDataBuffer.data()), static_cast<size_t>(sizeof(wchar_t) * stringDataBuffer.size()));
        }

        void EmitString(const std::string str) override
        {
            m_string_offsets.emplace_back(m_data_buffer_offset);
            const auto wStr = utils::ConvertStringToWString(str);
            m_data_builder << wStr << L'\0';
            m_data_buffer_offset += wStr.size() + 1;
        }

    private:
        std::ostream& m_stream;
        std::wostringstream m_data_builder;
        size_t m_data_buffer_offset;
        std::vector<size_t> m_string_offsets;
    };
}

using namespace srf;

std::unique_ptr<ISrfEmitter> SrfBinaryWriter::Create(std::ostream& stream)
{
    return std::make_unique<SrfBinaryWriterImpl>(stream);
}
