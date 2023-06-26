#include "GltfWriter.h"

#include <cassert>
#include <nlohmann/json.hpp>

using namespace gltf;
using namespace nlohmann;

namespace gltf
{
    class GltfWriterImpl final : public GltfWriter
    {
    public:
        GltfWriterImpl(const obj::ObjModel& model)
            : m_model(model),
              m_include_colors(false),
              m_include_normals(false)
        {
        }

        void ExportColors(const bool value) override
        {
            m_include_colors = value;
        }

        void ExportNormals(const bool value) override
        {
            m_include_normals = value;
        }

        void WriteGltf(std::ostream& out, const std::string& matName) const override
        {
            json data;

            AddAssetInfo(data);

            out << data.dump(1, '\t');
        }

    private:
        static void AddAssetInfo(json& data)
        {
            json asset;

            asset["generator"] = "LegoRacersMod glTF Exporter";
            asset["version"] = "2.0";

            data["asset"] = std::move(asset);
        }

        const obj::ObjModel& m_model;
        bool m_include_colors;
        bool m_include_normals;
    };
}

std::unique_ptr<GltfWriter> GltfWriter::Create(const obj::ObjModel& model)
{
    return std::make_unique<GltfWriterImpl>(model);
}
