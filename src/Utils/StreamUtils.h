#pragma once
#include <istream>
#include <exception>

namespace utils
{
    class ReadingException final : public std::exception
    {
    public:
        explicit ReadingException(const char* msg)
            : exception(msg)
        {
        }
    };

    inline void ReadOrThrow(std::istream& stream, void* buffer, const size_t readSize)
    {
        if (stream.read(static_cast<char*>(buffer), readSize).gcount() != readSize)
            throw ReadingException("Unexpected EOF");
    }
}
