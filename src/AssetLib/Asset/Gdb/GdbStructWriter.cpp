#include "GdbStructWriter.h"

namespace gdb
{
    class GdbStructWriterInternal final : public IGdbEmitter
    {
    public:
        explicit GdbStructWriterInternal(Model& model)
            : m_model(model)
        {
        }

        void StartMaterials() override
        {
            // Do nothing
        }

        void EmitMaterial(std::string materialName) override
        {
            m_model.m_materials.emplace_back(std::move(materialName));
        }

        void EndMaterials() override
        {
            // Do nothing
        }

        void EmitScale(const float scale) override
        {
            m_model.m_scale = scale;
        }

        void StartVertices() override
        {
            // Do nothing
        }

        void EmitVertex(const Vec3 position) override
        {
            m_model.m_vertex_format = VertexFormat::POSITION;
            m_model.m_vertices.emplace_back(position);
        }

        void EmitVertex(Vec3 position, Vec2 uv) override
        {
            m_model.m_vertex_format = VertexFormat::POSITION_UV;
            m_model.m_vertices.emplace_back(position, uv);
        }

        void EmitVertex(Vec3 position, Vec2 uv, Color4 color) override
        {
            m_model.m_vertex_format = VertexFormat::POSITION_UV_COLOR;
            m_model.m_vertices.emplace_back(position, uv, color);
        }

        void EmitVertex(Vec3 position, Vec2 uv, Vec3 normal) override
        {
            m_model.m_vertex_format = VertexFormat::POSITION_UV_NORMAL;
            m_model.m_vertices.emplace_back(position, uv, normal);
        }

        void EndVertices() override
        {
            // Do nothing
        }

        void StartFaces() override
        {
            // Do nothing
        }

        void EmitFace(unsigned int vertex0, unsigned int vertex1, unsigned int vertex2) override
        {
            m_model.m_faces.emplace_back(vertex0, vertex1, vertex2);
        }

        void EndFaces() override
        {
            // Do nothing
        }

        void StartMeta() override
        {
            // Do nothing
        }

        void EmitMetaKeyword31(int value0, int value1, int value2) override
        {
            m_model.m_meta.emplace_back(TOKEN_META_ADD_VERTICES, value0, value1, value2);
        }

        void EmitMetaKeyword2D(int value0, int value1) override
        {
            m_model.m_meta.emplace_back(TOKEN_META_FACES, value0, value1);
        }

        void EmitMetaKeyword2F(int value0) override
        {
            m_model.m_meta.emplace_back(TOKEN_META_2F, value0);
        }

        void EmitMetaKeyword30() override
        {
            m_model.m_meta.emplace_back(TOKEN_META_30);
        }

        void EmitMetaKeyword32(int value0) override
        {
            m_model.m_meta.emplace_back(TOKEN_META_32, value0);
        }

        void EmitMetaKeyword27(int value0) override
        {
            m_model.m_meta.emplace_back(TOKEN_META_NEW_OBJECT, value0);
        }

        void EndMeta() override
        {
            // Do nothing
        }

    private:
        Model& m_model;
    };
}

using namespace gdb;

std::unique_ptr<IGdbEmitter> GdbStructWriter::Create(Model& model)
{
    return std::make_unique<GdbStructWriterInternal>(model);
}
