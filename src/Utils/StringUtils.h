#pragma once
#include <string>

namespace utils
{
    std::string ConvertWStringToString(const std::wstring& wstr);
    std::wstring ConvertStringToWString(const std::string& str);

    bool StringEqualsIgnoreCase(const std::string& str0, const std::string& str1);
}
