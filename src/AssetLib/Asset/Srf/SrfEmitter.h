#pragma once

#include <string>

namespace srf
{
    class ISrfEmitter
    {
    public:
        ISrfEmitter() = default;
        virtual ~ISrfEmitter() = default;
        ISrfEmitter(const ISrfEmitter& other) = default;
        ISrfEmitter(ISrfEmitter&& other) noexcept = default;
        ISrfEmitter& operator=(const ISrfEmitter& other) = default;
        ISrfEmitter& operator=(ISrfEmitter&& other) noexcept = default;

        virtual void StartStrings() = 0;
        virtual void EndStrings() = 0;

        virtual void EmitString(std::string str) = 0;
    };
}
