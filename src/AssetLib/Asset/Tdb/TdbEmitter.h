#pragma once

#include <cstdint>
#include <string>

namespace tdb
{
    class ITdbEmitter
    {
    public:
        ITdbEmitter() = default;
        virtual ~ITdbEmitter() = default;
        ITdbEmitter(const ITdbEmitter& other) = default;
        ITdbEmitter(ITdbEmitter&& other) noexcept = default;
        ITdbEmitter& operator=(const ITdbEmitter& other) = default;
        ITdbEmitter& operator=(ITdbEmitter&& other) noexcept = default;

        virtual void StartTextures() = 0;
        virtual void EndTextures() = 0;

        virtual void StartTexture(std::string name) = 0;
        virtual void EmitFlipVertical() = 0;
        virtual void EmitKeyword29(int value) = 0;
        virtual void EmitBmp() = 0;
        virtual void EmitTga() = 0;
        virtual void EmitChromaKey(uint8_t r, uint8_t g, uint8_t b) = 0;
        virtual void EmitKeyword2D() = 0;
        virtual void EmitKeyword2E() = 0;
        virtual void EndTexture() = 0;
    };
} // namespace tdb
