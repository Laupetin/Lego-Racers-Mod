#include "GdbStructReader.h"

#include <cassert>

namespace gdb
{
    class GdbStructReaderInternal
    {
    public:
        GdbStructReaderInternal(const Model& model, IGdbEmitter& emitter)
            : m_model(model),
              m_emitter(emitter)
        {
        }

        void Read() const
        {
            ReadMaterials();
        }

    private:
        void ReadMaterials() const
        {
            m_emitter.StartMaterials();

            for (const auto& material : m_model.m_materials)
                m_emitter.EmitMaterial(material);

            m_emitter.EndMaterials();
        }

        void ReadVertices() const
        {
            switch (m_model.m_vertex_format)
            {
            case VertexFormat::POSITION:
                ReadVerticesPosition();
                break;

            case VertexFormat::POSITION_UV:
                ReadVerticesPositionUv();
                break;

            case VertexFormat::POSITION_UV_COLOR:
                ReadVerticesPositionUvColor();
                break;

            case VertexFormat::POSITION_UV_NORMAL:
                ReadVerticesPositionUvNormal();
                break;

            default:
                assert(false);
                break;
            }
        }

        void ReadVerticesPosition() const
        {
            m_emitter.StartVertices();

            for (const auto& vertex : m_model.m_vertices)
                m_emitter.EmitVertex(vertex.m_position);

            m_emitter.EndVertices();
        }

        void ReadVerticesPositionUv() const
        {
            m_emitter.StartVertices();

            for (const auto& vertex : m_model.m_vertices)
                m_emitter.EmitVertex(vertex.m_position, vertex.m_uv);

            m_emitter.EndVertices();
        }

        void ReadVerticesPositionUvColor() const
        {
            m_emitter.StartVertices();

            for (const auto& vertex : m_model.m_vertices)
                m_emitter.EmitVertex(vertex.m_position, vertex.m_uv, vertex.m_color);

            m_emitter.EndVertices();
        }

        void ReadVerticesPositionUvNormal() const
        {
            m_emitter.StartVertices();

            for (const auto& vertex : m_model.m_vertices)
                m_emitter.EmitVertex(vertex.m_position, vertex.m_uv, vertex.m_normal);

            m_emitter.EndVertices();
        }

        void ReadFaces() const
        {
            m_emitter.StartFaces();

            for (const auto& face : m_model.m_faces)
                m_emitter.EmitFace(face.m_indices[0], face.m_indices[1], face.m_indices[2]);

            m_emitter.EndFaces();
        }

        void ReadMeta() const
        {
            m_emitter.StartMeta();

            for(const auto& meta : m_model.m_meta)
            {
                switch (meta.m_keyword)
                {
                case TOKEN_META_NEW_OBJECT:
                    m_emitter.EmitMetaKeyword27(meta.m_value0);
                    break;

                case TOKEN_META_30:
                    m_emitter.EmitMetaKeyword30();
                    break;

                case TOKEN_META_ADD_VERTICES:
                    m_emitter.EmitMetaKeyword31(meta.m_value0, meta.m_value1, meta.m_value2);
                    break;

                case TOKEN_META_FACES:
                    m_emitter.EmitMetaKeyword2D(meta.m_value0, meta.m_value1);
                    break;

                case TOKEN_META_2F:
                    m_emitter.EmitMetaKeyword2F(meta.m_value0);
                    break;

                case TOKEN_META_32:
                    m_emitter.EmitMetaKeyword32(meta.m_value0);
                    break;

                default:
                    assert(false);
                    break;
                }
            }

            m_emitter.EndMeta();
        }

        const Model& m_model;
        IGdbEmitter& m_emitter;
    };
}

using namespace gdb;

void GdbStructReader::Read(const Model& model, IGdbEmitter& emitter)
{
    const GdbStructReaderInternal internal(model, emitter);
    internal.Read();
}
