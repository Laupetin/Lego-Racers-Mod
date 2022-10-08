#pragma once

#include "GdbEmitter.h"

namespace gdb
{
	class GdbStructReader final : public IGdbEmitter
	{
	public:
		void StartMaterials() override;
		void EmitMaterial(std::string materialName) override;
		void EndMaterials() override;
		void EmitScale(float scale) override;
		void StartVertices() override;
		void EmitVertex(Vec3 position) override;
		void EmitVertex(Vec3 position, Vec2 uv) override;
		void EmitVertex(Vec3 position, Vec2 uv, Color4 color) override;
		void EmitVertex(Vec3 position, Vec2 uv, Vec3 normal) override;
		void EndVertices() override;
		void StartFaces() override;
		void EmitFace(unsigned vertex0, unsigned vertex1, unsigned vertex2) override;
		void EndFaces() override;
		void StartMeta() override;
		void EmitMetaKeyword31(int value0, int value1, int value2) override;
		void EmitMetaKeyword2D(int value0, int value1) override;
		void EmitMetaKeyword2F(int value0) override;
		void EmitMetaKeyword30() override;
		void EmitMetaKeyword32(int value0) override;
		void EmitMetaKeyword27(int value0) override;
		void EndMeta() override;

		Model GetModel();

	private:
		Model m_model;
	};
}