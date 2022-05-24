#include <string>
#include <filesystem>
#include <iostream>

#include "JamFileDumper.h"

namespace fs = std::filesystem;

void main(const int argc, const char** argv)
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
            std::cout << "Creating JAM file from " << targetPath << "\n";
        }
        else if (fs::is_regular_file(targetPath))
        {
            dumping::DumpJamFile(targetPath.generic_string());
        }
        else
        {
            std::cout << "Unknown filesystem element type for \"" << targetPath << "\"\n";
        }
    }
}
