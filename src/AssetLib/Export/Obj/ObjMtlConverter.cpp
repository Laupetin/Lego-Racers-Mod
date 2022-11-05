#include "ObjMtlConverter.h"

using namespace obj;

namespace obj
{
    class ObjMtlConverterImpl final : public IObjMtlConverter
    {
    public:
        void StartMaterials() override
        {
        }

        void EndMaterials() override
        {
        }

        void StartMaterial(std::string name) override
        {
            m_current_material = MtlMaterial(std::move(name));
        }

        void EmitColor0(uint8_t value0, uint8_t value1, uint8_t value2, uint8_t value3) override
        {
        }

        void EmitColor1(uint8_t value0, uint8_t value1, uint8_t value2, uint8_t value3) override
        {
        }

        void EmitTexture(std::string textureName) override
        {
            m_current_material.m_color_map_name = std::move(textureName);
        }

        void EmitOpacity(uint8_t value) override
        {
        }

        void EmitKeyword4E(int value) override
        {
        }

        void EmitKeyword4F(int value) override
        {
        }

        void EmitKeyword4D(int value) override
        {
        }

        void EmitKeyword50(int value) override
        {
        }

        void EmitKeyword2A() override
        {
        }

        void EmitKeyword2B() override
        {
        }

        void EmitKeyword2D() override
        {
        }

        void EmitKeyword2E() override
        {
        }

        void EmitKeyword44() override
        {
        }

        void EmitKeyword45() override
        {
        }

        void EmitKeyword47() override
        {
        }

        void EmitKeyword48() override
        {
        }

        void EmitKeyword49() override
        {
        }

        void EmitKeyword4A() override
        {
        }

        void EmitKeyword4B() override
        {
        }

        void EmitKeyword4C() override
        {
        }

        void EmitKeyword2F(mdb::MaterialToken subToken, int subTokenValue) override
        {
        }

        void EmitKeyword38(mdb::MaterialToken subToken0, mdb::MaterialToken subToken1) override
        {
        }

        void EndMaterial() override
        {
            m_materials.emplace_back(std::move(m_current_material));
        }

        std::vector<MtlMaterial> RetrieveConvertedMaterials() override
        {
            return std::move(m_materials);
        }

    private:
        MtlMaterial m_current_material;
        std::vector<MtlMaterial> m_materials;
    };
}

std::unique_ptr<IObjMtlConverter> ObjMtlConverter::Create()
{
    return std::make_unique<ObjMtlConverterImpl>();
}
