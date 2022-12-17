#pragma once

#include <string>
#include <vector>

#include "Arguments/ArgumentParser.h"

class LRCompilerArgs
{
public:
    static constexpr const char* DEFAULT_OUTPUT_FOLDER = "dist";
    static constexpr const char* DEFAULT_OBJ_FOLDER = "obj";

    LRCompilerArgs();

    bool ParseArgs(int argc, const char** argv);

    std::vector<std::string> m_compile_objects;
    std::string m_output_folder;
    std::string m_obj_folder;
    bool m_verbose;

private:
    static void PrintUsage();

    ArgumentParser m_argument_parser;
};
