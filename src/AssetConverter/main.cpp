#include <string>
#include <filesystem>
#include <iostream>
#include <iterator>

#include "Asset/IAssetConverter.h"
#include "Export/Obj/ObjExporter.h"
#include "Export/Obj/ObjImporter.h"

namespace fs = std::filesystem;

IAssetConverter* availableConverters[]
{
    new obj::ObjExporter(),
    new obj::ObjImporter()
};

void main(const int argc, const char** argv)
{
    for (auto i = 1; i < argc; i++)
    {
        fs::path targetPath(argv[i]);
        if (!fs::exists(targetPath) || !fs::is_regular_file(targetPath))
        {
            std::cout << "Invalid file \"" << targetPath << "\"\n";
            continue;
        }

        auto extension = targetPath.extension().string();
        for (auto& c : extension)
            c = static_cast<char>(toupper(c));

        const auto availableConverter = std::find_if(std::begin(availableConverters), std::end(availableConverters), [&extension](const IAssetConverter* converter) {
            converter->SupportsExtension(extension);
        });

        if (availableConverter && availableConverter != std::end(availableConverters))
        {
            const auto directory = targetPath.parent_path().string();
            const auto fileName = targetPath.filename().string();

            (*availableConverter)->Convert(directory, fileName);
        }
        else
            std::cout << "No converter for file \"" << targetPath << "\"\n";
    }
}
