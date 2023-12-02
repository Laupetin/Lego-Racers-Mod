#pragma once
#include <string>

namespace utils
{
    std::string ConvertWStringToString(const std::wstring& wstr);
    std::wstring ConvertStringToWString(const std::string& str);

    bool StringEndsWith(const std::string& str, const std::string& ending);
    bool StringEndsWithIgnoreCase(const std::string& str, const std::string& ending);
    bool StringEqualsIgnoreCase(const std::string& str0, const std::string& str1);
    void MakeStringLowerCase(std::string& str);
    void MakeStringUpperCase(std::string& str);
} // namespace utils
