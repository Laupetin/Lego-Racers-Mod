#include "MdbDumper.h"

#include <iostream>

#include "TokenStream.h"

namespace mdb
{
    enum MaterialToken
    {
        TOKEN_MATERIAL_DB = TOKEN_CUSTOM_FIRST,
        TOKEN_MATERIAL = TOKEN_MATERIAL_DB // I guess this was not intended but thats how it is
    };

    int ReadMaterialCount(ITokenInputStream* tokenStream)
    {
        tokenStream->ExpectToken(TOKEN_LEFT_BRACKET);
        const auto materialCount = tokenStream->NextIntegerValue();
        tokenStream->ExpectToken(TOKEN_RIGHT_BRACKET);
        tokenStream->ExpectToken(TOKEN_LEFT_CURLY);
        return materialCount;
    }
}

using namespace mdb;

bool MdbDumper::SupportFileExtension(const std::string& extension) const
{
    return extension == ".MDB";
}

void MdbDumper::ProcessFile(const std::string& filePath, std::istream& input, std::ostream& output) const
{
    std::cout << "MDB dumping \"" << filePath << "\"\n";

    const auto tokenStream = ITokenInputStream::Create(input);
    tokenStream->ExpectToken(TOKEN_MATERIAL_DB);

    const auto materialCount = ReadMaterialCount(tokenStream.get());
    for (auto materialIndex = 0; materialIndex < materialCount; materialIndex++)
    {
        tokenStream->ExpectToken(TOKEN_MATERIAL);
        const auto materialName = tokenStream->NextStringValue();
        tokenStream->ExpectToken(TOKEN_LEFT_CURLY);

        Token token;
        do
        {
            token = tokenStream->NextValue();
        }
        while (token.m_type != TOKEN_RIGHT_CURLY && token.m_type != TOKEN_EOF);

        std::cout << "    Material: " << materialName << "\n";
    }

    tokenStream->ExpectToken(TOKEN_RIGHT_CURLY);
}
