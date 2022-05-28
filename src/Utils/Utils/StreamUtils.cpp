#include "StreamUtils.h"

#include <sstream>

using namespace utils;

BinaryReaderStream::BinaryReaderStream(std::istream& stream)
    : m_stream(stream)
{
}

void BinaryReaderStream::Read(void* data, const size_t size)
{
    if (m_stream.read(static_cast<char*>(data), size).gcount() != size)
        throw ReadingException("Unexpected EOF");
}

int8_t BinaryReaderStream::ReadInt8()
{
    int8_t value;
    if (m_stream.read(reinterpret_cast<char*>(&value), sizeof(value)).gcount() != sizeof(value))
        throw ReadingException("Unexpected EOF");
    return value;
}

uint8_t BinaryReaderStream::ReadUInt8()
{
    int8_t value;
    if (m_stream.read(reinterpret_cast<char*>(&value), sizeof(value)).gcount() != sizeof(value))
        throw ReadingException("Unexpected EOF");
    return value;
}

int16_t BinaryReaderStream::ReadInt16()
{
    int16_t value;
    if (m_stream.read(reinterpret_cast<char*>(&value), sizeof(value)).gcount() != sizeof(value))
        throw ReadingException("Unexpected EOF");
    return value;
}

uint16_t BinaryReaderStream::ReadUInt16()
{
    uint16_t value;
    if (m_stream.read(reinterpret_cast<char*>(&value), sizeof(value)).gcount() != sizeof(value))
        throw ReadingException("Unexpected EOF");
    return value;
}

int32_t BinaryReaderStream::ReadInt32()
{
    int32_t value;
    if (m_stream.read(reinterpret_cast<char*>(&value), sizeof(value)).gcount() != sizeof(value))
        throw ReadingException("Unexpected EOF");
    return value;
}

uint32_t BinaryReaderStream::ReadUInt32()
{
    uint32_t value;
    if (m_stream.read(reinterpret_cast<char*>(&value), sizeof(value)).gcount() != sizeof(value))
        throw ReadingException("Unexpected EOF");
    return value;
}

int64_t BinaryReaderStream::ReadInt64()
{
    int64_t value;
    if (m_stream.read(reinterpret_cast<char*>(&value), sizeof(value)).gcount() != sizeof(value))
        throw ReadingException("Unexpected EOF");
    return value;
}

uint64_t BinaryReaderStream::ReadUInt64()
{
    uint64_t value;
    if (m_stream.read(reinterpret_cast<char*>(&value), sizeof(value)).gcount() != sizeof(value))
        throw ReadingException("Unexpected EOF");
    return value;
}

std::string BinaryReaderStream::ReadString(const size_t length)
{
    std::string value(length, '\0');
    if (m_stream.read(value.data(), length).gcount() != length)
        throw ReadingException("Unexpected EOF");
    return value;
}

std::string BinaryReaderStream::ReadStringZeroTerminated()
{
    std::ostringstream ss;

    char c;
    while (m_stream.get(c).gcount() > 0)
    {
        if (c == '\0')
            return ss.str();

        ss << c;
    }

    throw ReadingException("Unexpected EOF");
}

size_t BinaryReaderStream::TryRead(void* data, const size_t size)
{
    return static_cast<size_t>(m_stream.read(static_cast<char*>(data), size).gcount());
}

bool BinaryReaderStream::TryReadInt8(int8_t& value)
{
    return m_stream.read(reinterpret_cast<char*>(&value), sizeof(value)).gcount() == sizeof(value);
}

bool BinaryReaderStream::TryReadUInt8(uint8_t& value)
{
    return m_stream.read(reinterpret_cast<char*>(&value), sizeof(value)).gcount() == sizeof(value);
}

bool BinaryReaderStream::TryReadInt16(int16_t& value)
{
    return m_stream.read(reinterpret_cast<char*>(&value), sizeof(value)).gcount() == sizeof(value);
}

bool BinaryReaderStream::TryReadUInt16(uint16_t& value)
{
    return m_stream.read(reinterpret_cast<char*>(&value), sizeof(value)).gcount() == sizeof(value);
}

bool BinaryReaderStream::TryReadInt32(int32_t& value)
{
    return m_stream.read(reinterpret_cast<char*>(&value), sizeof(value)).gcount() == sizeof(value);
}

bool BinaryReaderStream::TryReadUInt32(uint32_t& value)
{
    return m_stream.read(reinterpret_cast<char*>(&value), sizeof(value)).gcount() == sizeof(value);
}

bool BinaryReaderStream::TryReadInt64(int64_t& value)
{
    return m_stream.read(reinterpret_cast<char*>(&value), sizeof(value)).gcount() == sizeof(value);
}

bool BinaryReaderStream::TryReadUInt64(uint64_t& value)
{
    return m_stream.read(reinterpret_cast<char*>(&value), sizeof(value)).gcount() == sizeof(value);
}

std::string BinaryReaderStream::TryReadString(const size_t length)
{
    if (length <= 0)
        return std::string();

    std::ostringstream ss;

    char c;
    size_t curLen = 0u;
    while (m_stream.get(c).gcount() > 0)
    {
        if (++curLen >= length)
            return ss.str();

        ss << c;
    }

    return ss.str();
}

void BinaryReaderStream::SkipBytes(const size_t count)
{
    m_stream.seekg(count, std::ios::cur);
}

BinaryReaderBuffer::BinaryReaderBuffer(const void* buffer, const size_t bufferSize)
    : m_buffer(static_cast<const char*>(buffer)),
      m_buffer_size(bufferSize),
      m_current_offset(0u)
{
}

void BinaryReaderBuffer::Read(void* data, const size_t size)
{
    if (m_current_offset + size > m_buffer_size)
        throw ReadingException("Unexpected EOF");
    memcpy(data, &m_buffer[m_current_offset], size);
    m_current_offset += size;
}

int8_t BinaryReaderBuffer::ReadInt8()
{
    if (m_current_offset + sizeof(int8_t) > m_buffer_size)
        throw ReadingException("Unexpected EOF");
    const auto value = *reinterpret_cast<const int8_t*>(&m_buffer[m_current_offset]);
    m_current_offset += sizeof(int8_t);
    return value;
}

uint8_t BinaryReaderBuffer::ReadUInt8()
{
    if (m_current_offset + sizeof(uint8_t) > m_buffer_size)
        throw ReadingException("Unexpected EOF");
    const auto value = *reinterpret_cast<const uint8_t*>(&m_buffer[m_current_offset]);
    m_current_offset += sizeof(uint8_t);
    return value;
}

int16_t BinaryReaderBuffer::ReadInt16()
{
    if (m_current_offset + sizeof(int16_t) > m_buffer_size)
        throw ReadingException("Unexpected EOF");
    const auto value = *reinterpret_cast<const int16_t*>(&m_buffer[m_current_offset]);
    m_current_offset += sizeof(int16_t);
    return value;
}

uint16_t BinaryReaderBuffer::ReadUInt16()
{
    if (m_current_offset + sizeof(uint16_t) > m_buffer_size)
        throw ReadingException("Unexpected EOF");
    const auto value = *reinterpret_cast<const uint16_t*>(&m_buffer[m_current_offset]);
    m_current_offset += sizeof(uint16_t);
    return value;
}

int32_t BinaryReaderBuffer::ReadInt32()
{
    if (m_current_offset + sizeof(int32_t) > m_buffer_size)
        throw ReadingException("Unexpected EOF");
    const auto value = *reinterpret_cast<const int32_t*>(&m_buffer[m_current_offset]);
    m_current_offset += sizeof(int32_t);
    return value;
}

uint32_t BinaryReaderBuffer::ReadUInt32()
{
    if (m_current_offset + sizeof(uint32_t) > m_buffer_size)
        throw ReadingException("Unexpected EOF");
    const auto value = *reinterpret_cast<const uint32_t*>(&m_buffer[m_current_offset]);
    m_current_offset += sizeof(uint32_t);
    return value;
}

int64_t BinaryReaderBuffer::ReadInt64()
{
    if (m_current_offset + sizeof(int64_t) > m_buffer_size)
        throw ReadingException("Unexpected EOF");
    const auto value = *reinterpret_cast<const int64_t*>(&m_buffer[m_current_offset]);
    m_current_offset += sizeof(int64_t);
    return value;
}

uint64_t BinaryReaderBuffer::ReadUInt64()
{
    if (m_current_offset + sizeof(uint64_t) > m_buffer_size)
        throw ReadingException("Unexpected EOF");
    const auto value = *reinterpret_cast<const uint64_t*>(&m_buffer[m_current_offset]);
    m_current_offset += sizeof(uint64_t);
    return value;
}

std::string BinaryReaderBuffer::ReadString(const size_t length)
{
    if (m_current_offset + length > m_buffer_size)
        throw ReadingException("Unexpected EOF");
    auto value = std::string(&m_buffer[m_current_offset], length);
    m_current_offset += length;
    return value;
}

std::string BinaryReaderBuffer::ReadStringZeroTerminated()
{
    const size_t stringStart = m_current_offset;
    while (m_current_offset < m_buffer_size)
    {
        if (m_buffer[m_current_offset++] == '\0')
            return std::string(&m_buffer[stringStart], m_current_offset - stringStart);
    }
    throw ReadingException("Unexpected EOF");
}

size_t BinaryReaderBuffer::TryRead(void* data, const size_t size)
{
    const auto readSize = std::min(m_buffer_size - m_current_offset, size);

    if (readSize > 0)
        memcpy(data, &m_buffer[m_current_offset], readSize);
    m_current_offset += readSize;
    return readSize;
}

bool BinaryReaderBuffer::TryReadInt8(int8_t& value)
{
    if (m_current_offset + sizeof(int8_t) >= m_buffer_size)
        return false;
    value = *reinterpret_cast<const int8_t*>(&m_buffer[m_current_offset]);
    m_current_offset += sizeof(int8_t);
    return true;
}

bool BinaryReaderBuffer::TryReadUInt8(uint8_t& value)
{
    if (m_current_offset + sizeof(uint8_t) >= m_buffer_size)
        return false;
    value = *reinterpret_cast<const uint8_t*>(&m_buffer[m_current_offset]);
    m_current_offset += sizeof(uint8_t);
    return true;
}

bool BinaryReaderBuffer::TryReadInt16(int16_t& value)
{
    if (m_current_offset + sizeof(int16_t) >= m_buffer_size)
        return false;
    value = *reinterpret_cast<const int16_t*>(&m_buffer[m_current_offset]);
    m_current_offset += sizeof(int16_t);
    return true;
}

bool BinaryReaderBuffer::TryReadUInt16(uint16_t& value)
{
    if (m_current_offset + sizeof(uint16_t) >= m_buffer_size)
        return false;
    value = *reinterpret_cast<const uint16_t*>(&m_buffer[m_current_offset]);
    m_current_offset += sizeof(uint16_t);
    return true;
}

bool BinaryReaderBuffer::TryReadInt32(int32_t& value)
{
    if (m_current_offset + sizeof(int32_t) >= m_buffer_size)
        return false;
    value = *reinterpret_cast<const int32_t*>(&m_buffer[m_current_offset]);
    m_current_offset += sizeof(int32_t);
    return true;
}

bool BinaryReaderBuffer::TryReadUInt32(uint32_t& value)
{
    if (m_current_offset + sizeof(uint32_t) >= m_buffer_size)
        return false;
    value = *reinterpret_cast<const uint32_t*>(&m_buffer[m_current_offset]);
    m_current_offset += sizeof(uint32_t);
    return true;
}

bool BinaryReaderBuffer::TryReadInt64(int64_t& value)
{
    if (m_current_offset + sizeof(int64_t) >= m_buffer_size)
        return false;
    value = *reinterpret_cast<const int64_t*>(&m_buffer[m_current_offset]);
    m_current_offset += sizeof(int64_t);
    return true;
}

bool BinaryReaderBuffer::TryReadUInt64(uint64_t& value)
{
    if (m_current_offset + sizeof(uint64_t) >= m_buffer_size)
        return false;
    value = *reinterpret_cast<const uint64_t*>(&m_buffer[m_current_offset]);
    m_current_offset += sizeof(uint64_t);
    return true;
}

std::string BinaryReaderBuffer::TryReadString(const size_t length)
{
    const auto readLength = std::min(m_buffer_size - m_current_offset, length);

    if (length <= 0)
        return std::string();

    auto value = std::string(&m_buffer[m_current_offset], readLength);
    m_current_offset += readLength;
    return value;
}

void BinaryReaderBuffer::SkipBytes(const size_t count)
{
    m_current_offset += std::min(count, m_buffer_size - m_current_offset);
}

const void* BinaryReaderBuffer::Buffer() const
{
    return m_buffer;
}

size_t BinaryReaderBuffer::BufferSize() const
{
    return m_buffer_size;
}

size_t BinaryReaderBuffer::Pos() const
{
    return m_current_offset;
}
