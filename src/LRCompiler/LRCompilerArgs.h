#pragma once

#include <string>
#include <vector>

#include "Arguments/ArgumentParser.h"
#include "Project/ProjectDefinition.h"

class LRCompilerArgs
{
public:
    LRCompilerArgs();

    bool ParseArgs(int argc, const char** argv);

    void ConfigureProjectDefinition(ProjectDefinition& definition) const;

    std::vector<std::string> m_compile_objects;
    std::string m_dist_folder;
    std::string m_obj_folder;
    bool m_verbose;

private:
    static void PrintUsage();

    ArgumentParser m_argument_parser;
};
