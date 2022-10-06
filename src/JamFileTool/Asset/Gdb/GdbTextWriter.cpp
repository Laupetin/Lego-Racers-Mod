#include "GdbTextWriter.h"

namespace gdb
{
	class GdbTextWriterImpl final : public IGdbEmitter, AbstractTokenTextDumper
	{
	public:
		GdbTextWriterImpl(std::ostream& out)
			: AbstractTokenTextDumper(out),
			  m_first_vertex_element(true)
		{
		}

		void StartMaterials() override
		{
			m_stream << "materials\n";
			Indent();
			m_stream << "{\n";
			IncIndent();
		}

		void EmitMaterial(std::string materialName) override
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

		void EmitScale(float scale) override
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

		void EmitVertex(Vec3 position) override
		{
			Indent();
			m_stream << "v " << position.x << " " << position.y << " " << position.z << "\n";
		}

		void EmitVertex(Vec3 position, Vec2 uv) override
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

		void EmitVertex(Vec3 position, Vec2 uv, Color4 color) override
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
			m_stream << "clr " << static_cast<unsigned>(color.r) << " " << static_cast<unsigned>(color.g)
				<< " " << static_cast<unsigned>(color.b) << " " << static_cast<unsigned>(color.a) << "\n";
		}

		void EmitVertex(Vec3 position, Vec2 uv, Vec3 normal) override
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

		void EmitFace(unsigned vertex0, unsigned vertex1, unsigned vertex2) override
		{
			Indent();
			m_stream << "f " << vertex0 << " " << vertex1 << " " << vertex2 << "\n";
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

		void EmitMetaKeyword31(int value0, int value1, int value2) override
		{
			Indent();
			m_stream << "keyword31 " << value0 << " " << value1 << " " << value2 << "\n";
		}

		void EmitMetaKeyword2D(int value0, int value1) override
		{
			Indent();
			m_stream << "keyword2D " << value0 << " " << value1 << "\n";
		}

		void EmitMetaKeyword2F(int value0) override
		{
			Indent();
			m_stream << "keyword2F " << value0 << "\n";
		}

		void EmitMetaKeyword30() override
		{
			Indent();
			m_stream << "keyword30 " << "\n";
		}

		void EmitMetaKeyword32(int value0) override
		{
			Indent();
			m_stream << "keyword32 " << value0 << "\n";
		}

		void EmitMetaKeyword27(int value0) override
		{
			Indent();
			m_stream << "keyword27 " << value0 << "\n";
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
}

using namespace gdb;

std::unique_ptr<IGdbEmitter> GdbTextWriter::Create(std::ostream& out)
{
	return std::make_unique<GdbTextWriterImpl>(out);
}
