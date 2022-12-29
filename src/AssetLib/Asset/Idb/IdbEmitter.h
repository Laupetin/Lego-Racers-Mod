#pragma once

#include <string>
#include <cstdint>

namespace idb
{
    class IIdbEmitter
    {
    public:
        IIdbEmitter() = default;
        virtual ~IIdbEmitter() = default;
        IIdbEmitter(const IIdbEmitter& other) = default;
        IIdbEmitter(IIdbEmitter&& other) noexcept = default;
        IIdbEmitter& operator=(const IIdbEmitter& other) = default;
        IIdbEmitter& operator=(IIdbEmitter&& other) noexcept = default;

        virtual void StartImages() = 0;
        virtual void EndImages() = 0;

        virtual void StartImage(std::string name) = 0;
        virtual void EmitFlipVertical() = 0;
        virtual void EmitBmp() = 0;
        virtual void EmitTga() = 0;
        virtual void EmitChromaKey(uint8_t r, uint8_t g, uint8_t b) = 0;
        virtual void EmitTint(uint8_t r, uint8_t g, uint8_t b) = 0;
        virtual void EndImage() = 0;
    };
}
