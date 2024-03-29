#include "ObjWriter.h"

#include <cassert>

using namespace obj;

ObjWriter::ObjWriter(const ObjModel& model)
    : m_model(model),
      m_include_colors(false),
      m_include_normals(false)
{
}

void ObjWriter::ExportColors(const bool value)
{
    m_include_colors = value;
}

void ObjWriter::ExportNormals(const bool value)
{
    m_include_normals = value;
}

void ObjWriter::WriteObj(std::ostream& out, const std::string& matName) const
{
    out << "# LegoRacersMod OBJ File\n";
    out << "# Object count: " << m_model.m_objects.size() << "\n";

    if (!matName.empty())
        out << "mtllib " << matName << "\n";

    auto objectIndex = 0;
    auto vertexObjectOffset = 0u;
    auto uvObjectOffset = 0u;
    auto normalObjectOffset = 0u;
    for (const auto& object : m_model.m_objects)
    {
        out << "o " << object.m_name << "\n";

        out << std::fixed;

        if (m_include_colors)
        {
            for (const auto& v : object.m_vertices)
                out << "v " << v.m_coordinates[0] << " " << v.m_coordinates[1] << " " << v.m_coordinates[2] << " " << v.m_colors[0] << " " << v.m_colors[1]
                    << " " << v.m_colors[2] << "\n";
        }
        else
        {
            for (const auto& v : object.m_vertices)
                out << "v " << v.m_coordinates[0] << " " << v.m_coordinates[1] << " " << v.m_coordinates[2] << "\n";
        }

        for (const auto& uv : object.m_uvs)
            out << "vt " << uv.m_uv[0] << " " << uv.m_uv[1] << "\n";

        if (m_include_normals)
        {
            for (const auto& n : object.m_normals)
                out << "vn " << n.m_normal[0] << " " << n.m_normal[1] << " " << n.m_normal[2] << "\n";
        }

        if (object.m_material_index >= 0 && static_cast<unsigned>(object.m_material_index) < m_model.m_materials.size())
            out << "usemtl " << m_model.m_materials[object.m_material_index].m_material_name << "\n";

        int currentGroup = -1;
        for (const auto& f : object.m_faces)
        {
            const auto faceHasNormal = m_include_normals && f.HasNormals();
            const auto faceHasUv = f.HasUv();

            if (f.m_group != currentGroup)
            {
                assert(object.m_groups.size() >= f.m_group);
                out << "g " << object.m_groups[f.m_group] << "\n";
                currentGroup = f.m_group;
            }

            if (faceHasNormal && faceHasUv)
            {
                const auto& v = f.m_vertex_index;
                const auto& uv = f.m_uv_index;
                const auto& n = f.m_normal_index;

                out << "f " << v[0] + vertexObjectOffset + 1 << "/" << uv[0] + uvObjectOffset + 1 << "/" << n[0] + normalObjectOffset + 1 << " "
                    << v[1] + vertexObjectOffset + 1 << "/" << uv[1] + uvObjectOffset + 1 << "/" << n[1] + normalObjectOffset + 1 << " "
                    << v[2] + vertexObjectOffset + 1 << "/" << uv[2] + uvObjectOffset + 1 << "/" << n[2] + normalObjectOffset + 1 << "\n";
            }
            else if (faceHasUv && !faceHasNormal)
            {
                const auto& v = f.m_vertex_index;
                const auto& uv = f.m_uv_index;

                out << "f " << v[0] + vertexObjectOffset + 1 << "/" << uv[0] + uvObjectOffset + 1 << " " << v[1] + vertexObjectOffset + 1 << "/"
                    << uv[1] + uvObjectOffset + 1 << " " << v[2] + vertexObjectOffset + 1 << "/" << uv[2] + uvObjectOffset + 1 << "\n";
            }
            else if (faceHasNormal && !faceHasUv)
            {
                const auto& v = f.m_vertex_index;
                const auto& n = f.m_normal_index;

                out << "f " << v[0] + vertexObjectOffset + 1 << "//" << n[0] + normalObjectOffset + 1 << " " << v[1] + vertexObjectOffset + 1 << "//"
                    << n[1] + normalObjectOffset + 1 << " " << v[2] + vertexObjectOffset + 1 << "//" << n[2] + normalObjectOffset + 1 << "\n";
            }
            else
            {
                const auto& v = f.m_vertex_index;

                out << "f " << v[0] + vertexObjectOffset + 1 << " " << v[1] + vertexObjectOffset + 1 << " " << v[2] + vertexObjectOffset + 1 << "\n";
            }
        }

        objectIndex++;
        vertexObjectOffset += object.m_vertices.size();
        uvObjectOffset += object.m_uvs.size();
        normalObjectOffset += object.m_normals.size();
    }
}

void ObjWriter::WriteMtl(std::ostream& out) const
{
    out << "# LegoRacersMod MTL File\n";
    out << "# Material count: " << m_model.m_materials.size() << "\n";

    for (const auto& material : m_model.m_materials)
    {
        out << "\n";
        out << "newmtl " << material.m_material_name << "\n";

        if (!material.m_color_map_name.empty())
            out << "map_Kd " << material.m_color_map_name << ".BMP\n";
    }
}
