#include <string>
#include <filesystem>
#include <iostream>

#include "JamFileCreator.h"
#include "JamFileDumper.h"

namespace fs = std::filesystem;

int main(const int argc, const char** argv)
{
    for (auto i = 1; i < argc; i++)
    {
        fs::path targetPath(argv[i]);
        if (!fs::exists(targetPath))
        {
            std::cout << "Invalid file or directory \"" << targetPath << "\"\n";
            continue;
        }

        if (fs::is_directory(targetPath))
        {
            creating::CreateJamFile(targetPath.string());
        }
        else if (fs::is_regular_file(targetPath))
        {
            dumping::DumpJamFile(targetPath.string());
        }
        else
        {
            std::cout << "Unknown filesystem element type for \"" << targetPath << "\"\n";
        }
    }

    return 0;
}
