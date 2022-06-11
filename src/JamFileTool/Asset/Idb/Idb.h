#pragma once

namespace idb
{
    enum ImageToken
    {
        TOKEN_IMAGE_DB = 0x27,
        TOKEN_IMAGE = TOKEN_IMAGE_DB,
        TOKEN_KEYWORD_FLIP_VERTICAL = 0x28,
        TOKEN_KEYWORD_BMP = 0x29,
        TOKEN_KEYWORD_TGA = 0x2A,
        TOKEN_KEYWORD_CHROMA_KEY = 0x2B,
        TOKEN_KEYWORD_TINT = 0x2C,
    };
}