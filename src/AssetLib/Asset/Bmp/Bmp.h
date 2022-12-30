#pragma once

#include <cstdint>

namespace bmp
{
    // constants for the biCompression field
    constexpr auto BMP_BI_RGB = 0L;
    constexpr auto BMP_BI_RLE8 = 1L;
    constexpr auto BMP_BI_RLE4 = 2L;
    constexpr auto BMP_BI_BITFIELDS = 3L;
    constexpr auto BMP_BI_JPEG = 4L;
    constexpr auto BMP_BI_PNG = 5L;

#pragma pack(push, 2)
    struct BitmapFileHeader
    {
        uint16_t bfType;
        uint32_t bfSize;
        uint16_t bfReserved1;
        uint16_t bfReserved2;
        uint32_t bfOffBits;
    };
#pragma pack(pop)

    static_assert(sizeof(BitmapFileHeader) == 14u);

    struct BitmapInfoHeader
    {
        uint32_t biSize;
        int32_t biWidth;
        int32_t biHeight;
        uint16_t biPlanes;
        uint16_t biBitCount;
        uint32_t biCompression;
        uint32_t biSizeImage;
        int32_t biXPelsPerMeter;
        int32_t biYPelsPerMeter;
        uint32_t biClrUsed;
        uint32_t biClrImportant;
    };

    static_assert(sizeof(BitmapInfoHeader) == 40u);

    struct BitmapRgbQuad
    {
        uint8_t rgbBlue;
        uint8_t rgbGreen;
        uint8_t rgbRed;
        uint8_t rgbReserved;
    };

    static_assert(sizeof(BitmapRgbQuad) == 4u);
}
