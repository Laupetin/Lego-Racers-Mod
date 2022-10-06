#pragma once

#include <string>

#include "Gdb.h"

namespace gdb
{
	class IGdbEmitter
	{
	public:
		IGdbEmitter() = default;
		virtual ~IGdbEmitter() = default;

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
		virtual void EmitFace(unsigned vertex0, unsigned vertex1, unsigned vertex2) = 0;
		virtual void EndFaces() = 0;

		virtual void StartMeta() = 0;
		virtual void EmitMetaKeyword31(int value0, int value1, int value2) = 0;
		virtual void EmitMetaKeyword2D(int value0, int value1) = 0;
		virtual void EmitMetaKeyword2F(int value0) = 0;
		virtual void EmitMetaKeyword30() = 0;
		virtual void EmitMetaKeyword32(int value0) = 0;
		virtual void EmitMetaKeyword27(int value0) = 0;
		virtual void EndMeta() = 0;
	};
}