#include "GdbStructReader.h"

using namespace gdb;

void GdbStructReader::StartMaterials()
{
}

void GdbStructReader::EmitMaterial(std::string materialName)
{
	m_model.m_materials.emplace_back(std::move(materialName));
}

void GdbStructReader::EndMaterials()
{
}

void GdbStructReader::EmitScale(float scale)
{
	m_model.m_scale = scale;
}

void GdbStructReader::StartVertices()
{
}

void GdbStructReader::EmitVertex(Vec3 position)
{
}

void GdbStructReader::EmitVertex(Vec3 position, Vec2 uv)
{
}

void GdbStructReader::EmitVertex(Vec3 position, Vec2 uv, Color4 color)
{
}

void GdbStructReader::EmitVertex(Vec3 position, Vec2 uv, Vec3 normal)
{
}

void GdbStructReader::EndVertices()
{
}

void GdbStructReader::StartFaces()
{
}

void GdbStructReader::EmitFace(unsigned vertex0, unsigned vertex1, unsigned vertex2)
{
}

void GdbStructReader::EndFaces()
{
}

void GdbStructReader::StartMeta()
{
}

void GdbStructReader::EmitMetaKeyword31(int value0, int value1, int value2)
{
}

void GdbStructReader::EmitMetaKeyword2D(int value0, int value1)
{
}

void GdbStructReader::EmitMetaKeyword2F(int value0)
{
}

void GdbStructReader::EmitMetaKeyword30()
{
}

void GdbStructReader::EmitMetaKeyword32(int value0)
{
}

void GdbStructReader::EmitMetaKeyword27(int value0)
{
}

void GdbStructReader::EndMeta()
{
}

Model GdbStructReader::GetModel()
{
	return std::move(m_model);
}