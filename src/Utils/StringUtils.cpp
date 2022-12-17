// Even with codecvt being deprecated there is no suitable replacement yet.
// So this will be used to be able to have multi platform compilation until a replacement is available
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include "StringUtils.h"

#include <codecvt>
#include <locale>

namespace utils
{
    std::string ConvertWStringToString(const std::wstring& wstr)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

        return converter.to_bytes(wstr);
    }

    std::wstring ConvertStringToWString(const std::string& str)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        return converter.from_bytes(str);
    }

    bool StringEqualsIgnoreCase(const std::string& str0, const std::string& str1)
    {
        const auto stringSize = str0.size();

        if (stringSize != str1.size())
            return false;

        for (auto i = 0u; i < stringSize; i++)
        {
            if (tolower(str0[i]) != tolower(str1[i]))
                return false;
        }

        return true;
    }
}
