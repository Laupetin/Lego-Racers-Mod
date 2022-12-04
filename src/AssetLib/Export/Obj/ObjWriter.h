#pragma once

#include <ostream>

#include "Obj.h"

namespace obj
{
    class ObjWriter
    {
    public:
        explicit ObjWriter(const ObjModel& model);

        void ExportColors(bool value);
        void ExportNormals(bool value);

        void WriteObj(std::ostream& out, const std::string& matName) const;
        void WriteMtl(std::ostream& out) const;

    private:
        const ObjModel& m_model;
        bool m_include_colors;
        bool m_include_normals;
    };
}
