#pragma once

#include <cstdint>
#include <exception>
#include <istream>

namespace utils
{
    class ReadingException final : public std::exception
    {
    public:
        explicit ReadingException(std::string msg)
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

    inline void ReadOrThrow(std::istream& stream, void* buffer, const size_t readSize)
    {
        if (stream.read(static_cast<char*>(buffer), readSize).gcount() != readSize)
            throw ReadingException("Unexpected EOF");
    }

    class IBinaryReader
    {
    protected:
        IBinaryReader() = default;

    public:
        virtual ~IBinaryReader() = default;
        IBinaryReader(const IBinaryReader& other) = default;
        IBinaryReader(IBinaryReader&& other) noexcept = default;
        IBinaryReader& operator=(const IBinaryReader& other) = default;
        IBinaryReader& operator=(IBinaryReader&& other) noexcept = default;

        virtual void Read(void* data, size_t size) = 0;
        virtual int8_t ReadInt8() = 0;
        virtual uint8_t ReadUInt8() = 0;
        virtual int16_t ReadInt16() = 0;
        virtual uint16_t ReadUInt16() = 0;
        virtual int32_t ReadInt32() = 0;
        virtual uint32_t ReadUInt32() = 0;
        virtual int64_t ReadInt64() = 0;
        virtual uint64_t ReadUInt64() = 0;
        virtual float ReadFp32() = 0;
        virtual double ReadFp64() = 0;
        virtual std::string ReadString(size_t length) = 0;
        virtual std::string ReadStringZeroTerminated() = 0;

        virtual size_t TryRead(void* data, size_t size) = 0;
        virtual bool TryReadInt8(int8_t& value) = 0;
        virtual bool TryReadUInt8(uint8_t& value) = 0;
        virtual bool TryReadInt16(int16_t& value) = 0;
        virtual bool TryReadUInt16(uint16_t& value) = 0;
        virtual bool TryReadInt32(int32_t& value) = 0;
        virtual bool TryReadUInt32(uint32_t& value) = 0;
        virtual bool TryReadInt64(int64_t& value) = 0;
        virtual bool TryReadUInt64(uint64_t& value) = 0;
        virtual bool TryReadFp32(float& value) = 0;
        virtual bool TryReadFp64(double& value) = 0;
        virtual std::string TryReadString(size_t length) = 0;

        virtual void SkipBytes(size_t count) = 0;
    };

    class BinaryReaderStream final : public IBinaryReader
    {
    public:
        explicit BinaryReaderStream(std::istream& stream);

        void Read(void* data, size_t size) override;
        int8_t ReadInt8() override;
        uint8_t ReadUInt8() override;
        int16_t ReadInt16() override;
        uint16_t ReadUInt16() override;
        int32_t ReadInt32() override;
        uint32_t ReadUInt32() override;
        int64_t ReadInt64() override;
        uint64_t ReadUInt64() override;
        float ReadFp32() override;
        double ReadFp64() override;
        std::string ReadString(size_t length) override;
        std::string ReadStringZeroTerminated() override;

        size_t TryRead(void* data, size_t size) override;
        bool TryReadInt8(int8_t& value) override;
        bool TryReadUInt8(uint8_t& value) override;
        bool TryReadInt16(int16_t& value) override;
        bool TryReadUInt16(uint16_t& value) override;
        bool TryReadInt32(int32_t& value) override;
        bool TryReadUInt32(uint32_t& value) override;
        bool TryReadInt64(int64_t& value) override;
        bool TryReadUInt64(uint64_t& value) override;
        bool TryReadFp32(float& value) override;
        bool TryReadFp64(double& value) override;
        std::string TryReadString(size_t length) override;

        void SkipBytes(size_t count) override;

    private:
        std::istream& m_stream;
    };

    class BinaryReaderBuffer final : public IBinaryReader
    {
    public:
        BinaryReaderBuffer(const void* buffer, size_t bufferSize);

        void Read(void* data, size_t size) override;
        int8_t ReadInt8() override;
        uint8_t ReadUInt8() override;
        int16_t ReadInt16() override;
        uint16_t ReadUInt16() override;
        int32_t ReadInt32() override;
        uint32_t ReadUInt32() override;
        int64_t ReadInt64() override;
        uint64_t ReadUInt64() override;
        float ReadFp32() override;
        double ReadFp64() override;
        std::string ReadString(size_t length) override;
        std::string ReadStringZeroTerminated() override;

        size_t TryRead(void* data, size_t size) override;
        bool TryReadInt8(int8_t& value) override;
        bool TryReadUInt8(uint8_t& value) override;
        bool TryReadInt16(int16_t& value) override;
        bool TryReadUInt16(uint16_t& value) override;
        bool TryReadInt32(int32_t& value) override;
        bool TryReadUInt32(uint32_t& value) override;
        bool TryReadInt64(int64_t& value) override;
        bool TryReadUInt64(uint64_t& value) override;
        bool TryReadFp32(float& value) override;
        bool TryReadFp64(double& value) override;
        std::string TryReadString(size_t length) override;

        void SkipBytes(size_t count) override;

        [[nodiscard]] const void* Buffer() const;
        [[nodiscard]] size_t BufferSize() const;
        [[nodiscard]] size_t Pos() const;

    private:
        const char* m_buffer;
        size_t m_buffer_size;
        size_t m_current_offset;
    };
} // namespace utils
