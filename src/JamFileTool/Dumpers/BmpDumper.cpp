#include "BmpDumper.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <Windows.h>

#include "Utils/Alignment.h"
#include "Utils/FileUtils.h"
#include "Utils/StreamUtils.h"

class BmpDumpingException final : public std::exception
{
public:
    explicit BmpDumpingException(char const* msg)
        : exception(msg)
    {
    }
};

constexpr auto BMP_PALETTE_MAX_SIZE = 256;
constexpr auto BMP_DECOMPRESS_BUFFER_SIZE = 1500;
constexpr auto CUSTOM_BMP_MASK_BITS_PER_PIXEL = 0x3C;
constexpr auto CUSTOM_BMP_FLAG_NO_PALETTE = 0x80;

struct RacersCustomBmpHeader
{
    uint8_t bitsPerPixel;
    uint8_t paletteSize;
    uint16_t width;
    uint16_t height;
};

static_assert(sizeof(RacersCustomBmpHeader) == 6);

struct RacersCustomBmpPaletteRgba
{
    uint8_t b;
    uint8_t g;
    uint8_t r;
    uint8_t a;
};

static_assert(sizeof(RacersCustomBmpPaletteRgba) == 4);

struct RacersCustomBmpPaletteRgb
{
    uint8_t b;
    uint8_t g;
    uint8_t r;
};

static_assert(sizeof(RacersCustomBmpPaletteRgb) == 3);

namespace creation
{
}

class CustomBmpDumper
{
public:
    CustomBmpDumper(const char* in, const size_t inSize, std::ostream& out)
        : m_reader(in, inSize),
          m_out(out),
          m_palette{},
          m_decompress_buffer{},
          m_decompress_pos(0u),
          m_decompress_size(0u),
          m_palette_size(0u),
          m_bits_per_pixel(0u),
          m_width(0u),
          m_height(0u),
          m_out_stride_in_bytes(0u),
          m_out_image_size_in_byte(0u)
    {
    }

    void Initialize()
    {
        RacersCustomBmpHeader inHeader{};
        m_reader.Read(&inHeader, sizeof(inHeader));

        m_bits_per_pixel = inHeader.bitsPerPixel & CUSTOM_BMP_MASK_BITS_PER_PIXEL;
        if (m_bits_per_pixel != 4 && m_bits_per_pixel != 8 && m_bits_per_pixel != 24 && m_bits_per_pixel != 32)
            throw BmpDumpingException("Bitmap has invalid bitsPerPixel");

        m_width = inHeader.width;
        m_height = inHeader.height;

        m_out_stride_in_bytes = utils::Align(m_width * m_bits_per_pixel, 32u) / 8u;
        m_out_image_size_in_byte = m_out_stride_in_bytes * m_height;

        const auto hasPalette = m_bits_per_pixel <= 8 && (inHeader.bitsPerPixel & CUSTOM_BMP_FLAG_NO_PALETTE) == 0;
        m_palette_size = hasPalette ? inHeader.paletteSize + 1 : 0;
        ReadPalette();
    }

    void Write()
    {
        const auto outDataOffset = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * m_palette_size;
        const auto imageByteSize = m_out_image_size_in_byte;
        const BITMAPFILEHEADER outFileHeader{
            utils::MakeMagic16('B', 'M'),
            outDataOffset + imageByteSize,
            0,
            0,
            outDataOffset
        };
        m_out.write(reinterpret_cast<const char*>(&outFileHeader), sizeof(outFileHeader));

        const BITMAPINFOHEADER outInfoHeader{
            sizeof(BITMAPINFOHEADER),
            static_cast<LONG>(m_width),
            static_cast<LONG>(m_height),
            1,
            static_cast<WORD>(m_bits_per_pixel),
            BI_RGB,
            imageByteSize,
            1,
            1,
            m_palette_size,
            m_palette_size
        };
        m_out.write(reinterpret_cast<const char*>(&outInfoHeader), sizeof(outInfoHeader));

        for (auto paletteIndex = 0u; paletteIndex < m_palette_size; paletteIndex++)
        {
            RGBQUAD data{
                m_palette[paletteIndex].b,
                m_palette[paletteIndex].g,
                m_palette[paletteIndex].r,
                m_palette[paletteIndex].a
            };
            m_out.write(reinterpret_cast<const char*>(&data), sizeof(data));
        }

        WriteData();
    }

private:
    void ReadPalette()
    {
        if (m_palette_size > BMP_PALETTE_MAX_SIZE)
            throw BmpDumpingException("Palette size too large");

        if (m_palette_size <= 0)
            return;

        for (auto paletteIndex = 0u; paletteIndex < m_palette_size; paletteIndex++)
        {
            RacersCustomBmpPaletteRgb in{};
            m_reader.Read(&in, sizeof(in));

            m_palette[paletteIndex].b = in.b;
            m_palette[paletteIndex].g = in.g;
            m_palette[paletteIndex].r = in.r;
            m_palette[paletteIndex].a = std::numeric_limits<uint8_t>::max();
        }
    }

    void WriteData()
    {
        const auto scanLineDataLen = utils::Align(m_width * m_bits_per_pixel, 8u) / 8u;

        const auto scanLineBuffer = std::make_unique<char[]>(scanLineDataLen * m_height);
        for (auto scanLineIndex = 0u; scanLineIndex < m_height; scanLineIndex++)
        {
            auto remainingScanLineLen = scanLineDataLen;
            char* scanLineInBuffer = &scanLineBuffer[scanLineDataLen * (m_height - scanLineIndex - 1)];

            while (remainingScanLineLen > 0)
            {
                if (m_decompress_pos >= m_decompress_size)
                    NextData();

                const auto lenFromCurrentDecompressBuffer = std::min(remainingScanLineLen, m_decompress_size - m_decompress_pos);
                if (lenFromCurrentDecompressBuffer > 0)
                {
                    memcpy(&scanLineInBuffer[scanLineDataLen - remainingScanLineLen], &m_decompress_buffer[m_decompress_pos], lenFromCurrentDecompressBuffer);
                    m_decompress_pos += lenFromCurrentDecompressBuffer;
                    remainingScanLineLen -= lenFromCurrentDecompressBuffer;
                }
            }
        }

        const auto scanLinePadding = m_out_stride_in_bytes - scanLineDataLen;
        for (auto scanLineIndex = 0u; scanLineIndex < m_height; scanLineIndex++)
        {
            const char* scanLineInBuffer = &scanLineBuffer[scanLineDataLen * scanLineIndex];
            m_out.write(scanLineInBuffer, scanLineDataLen);

            if (scanLinePadding > 0)
                m_out.seekp(scanLinePadding, std::ios::cur);
        }

        assert(m_decompress_pos == m_decompress_size);
    }

    void NextData()
    {
        m_decompress_pos = 0;

        const auto nextDecompressedSize = m_reader.ReadUInt16();
        const auto nextCompressedSize = m_reader.ReadUInt16();

        if (nextDecompressedSize <= nextCompressedSize)
        {
            if (nextDecompressedSize > sizeof(m_decompress_buffer))
                throw BmpDumpingException("Decompress buffer out of bounds");
            m_decompress_size = nextDecompressedSize;
            m_reader.Read(m_decompress_buffer, nextDecompressedSize);
        }
        else
        {
            m_decompress_size = nextDecompressedSize;
            DecompressNext(nextCompressedSize);
        }
    }

    void DecompressNext(const size_t compressedSize)
    {
        const auto* data = &static_cast<const char*>(m_reader.Buffer())[m_reader.Pos()];
        utils::BinaryReaderBuffer compressedReader(data, compressedSize);

        // Copy first byte since it always must be copied anyway
        m_decompress_buffer[m_decompress_pos++] = compressedReader.ReadInt8();

        auto commandsEnd = false;
        do
        {
            auto commandByte = compressedReader.ReadUInt8();
            for (auto i = 0u; i < 8u; i++)
            {
                if (commandByte & 0x80)
                {
                    const auto fleByte = compressedReader.ReadUInt8();
                    const auto lowerCommandNibble = fleByte & 0xF;
                    const auto higherCommandNibble = fleByte & 0xF0;

                    // Offset is made up of higher nibble of command byte and following byte
                    const auto reverseReferenceOffset = static_cast<size_t>(higherCommandNibble << 4 | compressedReader.ReadUInt8());
                    if (reverseReferenceOffset > m_decompress_pos)
                        throw BmpDumpingException("Invalid compression");

                    if (reverseReferenceOffset == 0)
                    {
                        commandsEnd = true;
                        break;
                    }

                    // If repeat count is 0 then next byte is repeat count, otherwise 1 is remapped to 17 and 15 is remapped to 3
                    const auto repeatCount = static_cast<size_t>(lowerCommandNibble ? -(lowerCommandNibble - 18) : compressedReader.ReadUInt8() + 18);
                    if (repeatCount > m_decompress_size - m_decompress_pos)
                        throw BmpDumpingException("Invalid compression");

                    for (auto j = 0u; j < repeatCount; j++)
                    {
                        m_decompress_buffer[m_decompress_pos] = m_decompress_buffer[m_decompress_pos - reverseReferenceOffset];
                        m_decompress_pos++;
                    }
                }
                else
                {
                    if (m_decompress_pos >= m_decompress_size)
                        throw BmpDumpingException("Invalid compression");
                    m_decompress_buffer[m_decompress_pos++] = compressedReader.ReadInt8();
                }
                commandByte <<= 1;
            }
        }
        while (!commandsEnd);

        m_reader.SkipBytes(compressedSize);
        m_decompress_pos = 0;
    }

    utils::BinaryReaderBuffer m_reader;
    std::ostream& m_out;

    RacersCustomBmpPaletteRgba m_palette[BMP_PALETTE_MAX_SIZE];
    char m_decompress_buffer[BMP_DECOMPRESS_BUFFER_SIZE];
    size_t m_decompress_pos;
    size_t m_decompress_size;

    size_t m_palette_size;
    size_t m_bits_per_pixel;
    size_t m_width;
    size_t m_height;
    size_t m_out_stride_in_bytes;
    size_t m_out_image_size_in_byte;
};

bool BmpDumper::SupportFileExtension(const std::string& extension) const
{
    return extension == ".BMP";
}

void BmpDumper::ProcessFile(const std::string& filePath, const void* inputData, const size_t inputDataSize, std::ostream& output) const
{
    if (inputDataSize < sizeof(uint16_t))
        throw BmpDumpingException("Bitmap too small for magic");

    auto* magic = static_cast<const uint16_t*>(inputData);
    if (*magic == utils::MakeMagic16('B', 'M'))
    {
        std::cout << "BMP passthrough dumping \"" << filePath << "\"\n";
        output.write(static_cast<const char*>(inputData), inputDataSize);
        return;
    }

    std::cout << "BMP dumping \"" << filePath << "\"\n";
    CustomBmpDumper dumper(static_cast<const char*>(inputData), inputDataSize, output);
    dumper.Initialize();
    dumper.Write();
}
