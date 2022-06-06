#include "MdbDumper.h"

#include <iostream>

#include "TokenStream.h"
#include "Utils/AbstractTextDumper.h"

namespace mdb
{
    enum MaterialToken
    {
        TOKEN_MATERIAL_DB = 0x27,
        // I guess having two tokens the same value was not intended but thats how it is
        TOKEN_MATERIAL = TOKEN_MATERIAL_DB,
        TOKEN_KEYWORD_COLOR_1 = 0x28,
        TOKEN_KEYWORD_COLOR_0 = 0x29,
        TOKEN_KEYWORD_2A = 0x2A,
        TOKEN_KEYWORD_2B = 0x2B,
        TOKEN_KEYWORD_2C = 0x2C,
        TOKEN_KEYWORD_2D = 0x2D,
        TOKEN_KEYWORD_2E = 0x2E,
        TOKEN_KEYWORD_2F = 0x2F,
        TOKEN_KEYWORD_2F_SUB_30 = 0x30,
        TOKEN_KEYWORD_2F_SUB_31 = 0x31,
        TOKEN_KEYWORD_2F_SUB_32 = 0x32,
        TOKEN_KEYWORD_2F_SUB_33 = 0x33,
        TOKEN_KEYWORD_2F_SUB_34 = 0x34,
        TOKEN_KEYWORD_2F_SUB_35 = 0x35,
        TOKEN_KEYWORD_2F_SUB_36 = 0x36,
        TOKEN_KEYWORD_2F_SUB_37 = 0x37,
        TOKEN_KEYWORD_38 = 0x38,
        TOKEN_KEYWORD_38_SUB_39 = 0x39,
        TOKEN_KEYWORD_38_SUB_3A = 0x3A,
        TOKEN_KEYWORD_38_SUB_3B = 0x3B,
        TOKEN_KEYWORD_38_SUB_3C = 0x3C,
        TOKEN_KEYWORD_38_SUB_3D = 0x3D,
        TOKEN_KEYWORD_38_SUB_3E = 0x3E,
        TOKEN_KEYWORD_38_SUB_3F = 0x3F,
        TOKEN_KEYWORD_38_SUB_40 = 0x40,
        TOKEN_KEYWORD_38_SUB_41 = 0x41,
        TOKEN_KEYWORD_38_SUB_42 = 0x42,
        TOKEN_KEYWORD_38_SUB_43 = 0x43,
        TOKEN_KEYWORD_44 = 0x44,
        TOKEN_KEYWORD_45 = 0x45,
        TOKEN_KEYWORD_46 = 0x46,
        TOKEN_KEYWORD_47 = 0x47,
        TOKEN_KEYWORD_48 = 0x48,
        TOKEN_KEYWORD_49 = 0x49,
        TOKEN_KEYWORD_4A = 0x4A,
        TOKEN_KEYWORD_4B = 0x4B,
        TOKEN_KEYWORD_4C = 0x4C,
        TOKEN_KEYWORD_4D = 0x4D,
        TOKEN_KEYWORD_4E = 0x4E,
        TOKEN_KEYWORD_4F = 0x4F,
        TOKEN_KEYWORD_50 = 0x50,
    };
}

using namespace mdb;

class MdbTextOutputStream final : public AbstractTextDumper
{
public:
    explicit MdbTextOutputStream(std::istream& in, std::ostream& out)
        : AbstractTextDumper(out),
          m_tokens(ITokenInputStream::Create(in))
    {
    }

    void Write()
    {
        m_tokens->ExpectToken(TOKEN_MATERIAL_DB);
        BeginMaterials();

        const auto materialCount = ReadMaterialCount();
        for (auto materialIndex = 0; materialIndex < materialCount; materialIndex++)
        {
            m_tokens->ExpectToken(TOKEN_MATERIAL);
            const auto materialName = m_tokens->NextStringValue();
            m_tokens->ExpectToken(TOKEN_LEFT_CURLY);
            BeginMaterial(materialIndex, materialName);

            Token token;
            do
            {
                token = m_tokens->NextValue();
            }
            while (token.m_type != TOKEN_RIGHT_CURLY && token.m_type != TOKEN_EOF);

            EndMaterial();
            std::cout << "    Material: " << materialName << "\n";
        }

        m_tokens->ExpectToken(TOKEN_RIGHT_CURLY);
        EndMaterials();
    }

private:
    [[nodiscard]] int ReadMaterialCount() const
    {
        m_tokens->ExpectToken(TOKEN_LEFT_BRACKET);
        const auto materialCount = m_tokens->NextIntegerValue();
        m_tokens->ExpectToken(TOKEN_RIGHT_BRACKET);
        m_tokens->ExpectToken(TOKEN_LEFT_CURLY);
        return materialCount;
    }

    void BeginMaterials()
    {
        Indent();
        m_stream << "materials\n";

        Indent();
        m_stream << "{\n";
        IncIndent();
    }

    void EndMaterials()
    {
        DecIndent();
        Indent();
        m_stream << "}\n";
    }

    void BeginMaterial(const int materialIndex, const std::string& materialName)
    {
        if (materialIndex > 0)
            m_stream << "\n";

        Indent();
        m_stream << "material \"" << materialName << "\"\n";

        Indent();
        m_stream << "{\n";
        IncIndent();
    }

    void EndMaterial()
    {
        DecIndent();
        Indent();
        m_stream << "}\n";
    }

    std::unique_ptr<ITokenInputStream> m_tokens;
};

bool MdbDumper::SupportFileExtension(const std::string& extension) const
{
    return extension == ".MDB";
}

void MdbDumper::ProcessFile(const std::string& filePath, std::istream& input, std::ostream& output) const
{
    std::cout << "MDB dumping \"" << filePath << "\"\n";

    MdbTextOutputStream out(input, output);
    out.Write();
}
