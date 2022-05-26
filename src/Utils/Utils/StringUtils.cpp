#include "StringUtils.h"

#include <Windows.h>

std::string utils::ConvertWStringToString(const std::wstring& wstr)
{
    const auto bufferSize = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), static_cast<int>(wstr.size()), nullptr, 0, nullptr, nullptr);
    if (bufferSize <= 0)
        return {};

    std::string result(bufferSize, '\0');
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, result.data(), bufferSize, nullptr, nullptr);
    return result;
}

std::wstring utils::ConvertStringToWString(const std::string& str)
{
    const auto bufferSize = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), nullptr, 0);
    if (bufferSize <= 0)
        return {};

    std::wstring result(bufferSize, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, result.data(), bufferSize);
    return result;
}
