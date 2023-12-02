#include "GdbTextWriter.h"

#include "Utils/AbstractTextDumper.h"

#include <iomanip>

namespace gdb
{
    class GdbTextWriterImpl final : public IGdbEmitter, AbstractTokenTextDumper
    {
    public:
        explicit GdbTextWriterImpl(std::ostream& out)
            : AbstractTokenTextDumper(out),
              m_first_vertex_element(true)
        {
            m_stream << std::fixed << std::showpoint;
        }

        void StartMaterials() override
        {
            m_stream << "materials\n";
            Indent();
            m_stream << "{\n";
            IncIndent();
        }

        void EmitMaterial(const std::string materialName) override
        {
            Indent();
            m_stream << "\"" << materialName << "\"\n";
        }

        void EndMaterials() override
        {
            DecIndent();
            Indent();
            m_stream << "}\n\n";
        }

        void EmitScale(const float scale) override
        {
            Indent();
            m_stream << "scale " << scale << "\n\n";
        }

        void StartVertices() override
        {
            m_stream << "vertices\n";
            Indent();
            m_stream << "{\n";
            IncIndent();

            m_first_vertex_element = true;
        }

        void EmitVertex(const Vec3 position) override
        {
            Indent();
            m_stream << "v " << position.x << " " << position.y << " " << position.z << "\n";
        }

        void EmitVertex(const Vec3 position, const Vec2 uv) override
        {
            if (m_first_vertex_element)
                m_first_vertex_element = false;
            else
                m_stream << "\n";

            Indent();
            m_stream << "v " << position.x << " " << position.y << " " << position.z << "\n";

            Indent();
            m_stream << "uv " << uv.x << " " << uv.y << "\n";
        }

        void EmitVertex(const Vec3 position, const Vec2 uv, const Color4 color) override
        {
            if (m_first_vertex_element)
                m_first_vertex_element = false;
            else
                m_stream << "\n";

            Indent();
            m_stream << "v " << position.x << " " << position.y << " " << position.z << "\n";

            Indent();
            m_stream << "uv " << uv.x << " " << uv.y << "\n";

            Indent();
            m_stream << "clr " << static_cast<unsigned>(color.r) << " " << static_cast<unsigned>(color.g) << " " << static_cast<unsigned>(color.b) << " "
                     << static_cast<unsigned>(color.a) << "\n";
        }

        void EmitVertex(const Vec3 position, const Vec2 uv, const Vec3 normal) override
        {
            if (m_first_vertex_element)
                m_first_vertex_element = false;
            else
                m_stream << "\n";

            Indent();
            m_stream << "v " << position.x << " " << position.y << " " << position.z << "\n";

            Indent();
            m_stream << "uv " << uv.x << " " << uv.y << "\n";

            Indent();
            m_stream << "vn " << normal.x << " " << normal.y << " " << normal.z << "\n";
        }

        void EndVertices() override
        {
            DecIndent();
            Indent();
            m_stream << "}\n\n";
        }

        void StartFaces() override
        {
            m_stream << "faces\n";
            Indent();
            m_stream << "{\n";
            IncIndent();
        }

        void EmitFace(const uint8_t vertex0, const uint8_t vertex1, const uint8_t vertex2) override
        {
            Indent();
            m_stream << "f " << static_cast<int>(vertex0) << " " << static_cast<int>(vertex1) << " " << static_cast<int>(vertex2) << "\n";
        }

        void EndFaces() override
        {
            DecIndent();
            Indent();
            m_stream << "}\n\n";
        }

        void StartMeta() override
        {
            m_stream << "meta\n";
            Indent();
            m_stream << "{\n";
            IncIndent();
        }

        void EmitMetaSelectVertices(const uint8_t shiftForwardCount, const size_t vertexOffset, const uint8_t vertexCount) override
        {
            Indent();
            m_stream << "vertices " << static_cast<int>(shiftForwardCount) << " " << vertexOffset << " " << static_cast<int>(vertexCount) << "\n";
        }

        void EmitMetaAddFaces(const size_t faceOffset, const uint8_t faceCount) override
        {
            Indent();
            m_stream << "faces " << faceOffset << " " << static_cast<int>(faceCount) << "\n";
        }

        void EmitMetaKeyword2F(const int value0) override
        {
            Indent();
            m_stream << "keyword2F " << value0 << "\n";
        }

        void EmitMetaKeyword30() override
        {
            Indent();
            m_stream << "keyword30 "
                     << "\n";
        }

        void EmitMetaBone(const size_t value0) override
        {
            Indent();
            m_stream << "bone " << value0 << "\n";
        }

        void EmitMetaNewObject(const size_t materialIndex) override
        {
            Indent();
            m_stream << "object " << materialIndex << "\n";
        }

        void EndMeta() override
        {
            DecIndent();
            Indent();
            m_stream << "}\n\n";
        }

    private:
        bool m_first_vertex_element;
    };
} // namespace gdb

using namespace gdb;

std::unique_ptr<IGdbEmitter> GdbTextWriter::Create(std::ostream& out)
{
    return std::make_unique<GdbTextWriterImpl>(out);
}
