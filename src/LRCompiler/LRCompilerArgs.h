#pragma once

#include "Arguments/ArgumentParser.h"
#include "Project/ProjectDefinition.h"

#include <string>
#include <vector>

class LRCompilerArgs
{
public:
    LRCompilerArgs();

    bool ParseArgs(int argc, const char** argv);

    void ConfigureProjectDefinition(ProjectDefinition& definition) const;

    std::vector<std::string> m_compile_projects;
    std::string m_dist_folder;
    std::string m_obj_folder;
    std::string m_copy_to;
    bool m_verbose;
    bool m_recompile;
    bool m_force_linking;

private:
    static void PrintUsage();

    ArgumentParser m_argument_parser;
};
