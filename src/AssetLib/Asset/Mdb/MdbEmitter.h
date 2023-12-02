#pragma once

#include "Mdb.h"

#include <cstdint>
#include <string>

namespace mdb
{
    class IMdbEmitter
    {
    public:
        IMdbEmitter() = default;
        virtual ~IMdbEmitter() = default;
        IMdbEmitter(const IMdbEmitter& other) = default;
        IMdbEmitter(IMdbEmitter&& other) noexcept = default;
        IMdbEmitter& operator=(const IMdbEmitter& other) = default;
        IMdbEmitter& operator=(IMdbEmitter&& other) noexcept = default;

        virtual void StartMaterials() = 0;
        virtual void EndMaterials() = 0;

        virtual void StartMaterial(std::string name) = 0;
        virtual void EmitColor0(uint8_t value0, uint8_t value1, uint8_t value2, uint8_t value3) = 0;
        virtual void EmitColor1(uint8_t value0, uint8_t value1, uint8_t value2, uint8_t value3) = 0;
        virtual void EmitTexture(std::string textureName) = 0;
        virtual void EmitOpacity(uint8_t value) = 0;
        virtual void EmitKeyword4D(int value) = 0;
        virtual void EmitKeyword4E(int value) = 0;
        virtual void EmitKeyword4F(int value) = 0;
        virtual void EmitKeyword50(int value) = 0;
        virtual void EmitKeyword2A() = 0;
        virtual void EmitKeyword2B() = 0;
        virtual void EmitKeyword2D() = 0;
        virtual void EmitKeyword2E() = 0;
        virtual void EmitKeyword44() = 0;
        virtual void EmitKeyword45() = 0;
        virtual void EmitKeyword47() = 0;
        virtual void EmitKeyword48() = 0;
        virtual void EmitKeyword49() = 0;
        virtual void EmitKeyword4A() = 0;
        virtual void EmitKeyword4B() = 0;
        virtual void EmitKeyword4C() = 0;
        virtual void EmitKeyword2F(MaterialToken subToken, int subTokenValue) = 0;
        virtual void EmitKeyword38(MaterialToken subToken0, MaterialToken subToken1) = 0;
        virtual void EndMaterial() = 0;
    };
} // namespace mdb
