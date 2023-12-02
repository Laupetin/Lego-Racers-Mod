#pragma once

#include "Gdb.h"

#include <cstdint>
#include <string>

namespace gdb
{
    class IGdbEmitter
    {
    public:
        IGdbEmitter() = default;
        virtual ~IGdbEmitter() = default;
        IGdbEmitter(const IGdbEmitter& other) = default;
        IGdbEmitter(IGdbEmitter&& other) noexcept = default;
        IGdbEmitter& operator=(const IGdbEmitter& other) = default;
        IGdbEmitter& operator=(IGdbEmitter&& other) noexcept = default;

        virtual void StartMaterials() = 0;
        virtual void EmitMaterial(std::string materialName) = 0;
        virtual void EndMaterials() = 0;

        virtual void EmitScale(float scale) = 0;

        virtual void StartVertices() = 0;
        virtual void EmitVertex(Vec3 position) = 0;
        virtual void EmitVertex(Vec3 position, Vec2 uv) = 0;
        virtual void EmitVertex(Vec3 position, Vec2 uv, Color4 color) = 0;
        virtual void EmitVertex(Vec3 position, Vec2 uv, Vec3 normal) = 0;
        virtual void EndVertices() = 0;

        virtual void StartFaces() = 0;
        virtual void EmitFace(uint8_t vertex0, uint8_t vertex1, uint8_t vertex2) = 0;
        virtual void EndFaces() = 0;

        virtual void StartMeta() = 0;
        virtual void EmitMetaSelectVertices(uint8_t shiftForwardCount, size_t vertexOffset, uint8_t vertexCount) = 0;
        virtual void EmitMetaAddFaces(size_t faceOffset, uint8_t faceCount) = 0;
        virtual void EmitMetaKeyword2F(int value0) = 0;
        virtual void EmitMetaKeyword30() = 0;
        virtual void EmitMetaBone(size_t boneIndex) = 0;
        virtual void EmitMetaNewObject(size_t materialIndex) = 0;
        virtual void EndMeta() = 0;
    };
} // namespace gdb
