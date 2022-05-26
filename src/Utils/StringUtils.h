#pragma once
#include <string>

namespace utils
{
    std::string ConvertWStringToString(const std::wstring& wstr);
    std::wstring ConvertStringToWString(const std::string& str);
}
