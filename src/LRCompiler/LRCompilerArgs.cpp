#include "LRCompilerArgs.h"

#include <regex>
#include <type_traits>

#include "Arguments/UsageInformation.h"
#include "Project/ProjectDefinition.h"

const CommandLineOption* const OPTION_HELP =
    CommandLineOption::Builder::Create()
    .WithShortName("?")
    .WithLongName("help")
    .WithDescription("Displays usage information.")
    .Build();

const CommandLineOption* const OPTION_VERBOSE =
    CommandLineOption::Builder::Create()
    .WithShortName("v")
    .WithLongName("verbose")
    .WithDescription("Outputs a lot more and more detailed messages.")
    .Build();

const CommandLineOption* const OPTION_DIST_FOLDER =
    CommandLineOption::Builder::Create()
    .WithShortName("d")
    .WithLongName("dist")
    .WithDescription("Specifies the dist folder containing the compilation results. Defaults to \"" + std::string(ProjectDefinition::DEFAULT_DIST_FOLDER) + "\"")
    .WithParameter("distFolderPath")
    .Build();

const CommandLineOption* const OPTION_OBJ_FOLDER =
    CommandLineOption::Builder::Create()
    .WithLongName("obj")
    .WithDescription("Specifies the obj folder containing intermediate compilation files. Defaults to \"" + std::string(ProjectDefinition::DEFAULT_OBJ_FOLDER) + "\"")
    .WithParameter("objFolderPath")
    .Build();

const CommandLineOption* const COMMAND_LINE_OPTIONS[]
{
    OPTION_HELP,
    OPTION_VERBOSE,
    OPTION_DIST_FOLDER,
    OPTION_OBJ_FOLDER
};

LRCompilerArgs::LRCompilerArgs()
    : m_verbose(false),
      m_argument_parser(COMMAND_LINE_OPTIONS, std::extent_v<decltype(COMMAND_LINE_OPTIONS)>)
{
}

void LRCompilerArgs::PrintUsage()
{
    UsageInformation usage("lrcompile");

    for (const auto* commandLineOption : COMMAND_LINE_OPTIONS)
    {
        usage.AddCommandLineOption(commandLineOption);
    }

    usage.AddArgument("compilationObjects");
    usage.SetVariableArguments(true);

    usage.Print();
}

bool LRCompilerArgs::ParseArgs(const int argc, const char** argv)
{
    if (!m_argument_parser.ParseArguments(argc - 1, &argv[1]))
    {
        PrintUsage();
        return false;
    }

    // Check if the user requested help
    if (m_argument_parser.IsOptionSpecified(OPTION_HELP))
    {
        PrintUsage();
        return false;
    }

    m_compile_objects = m_argument_parser.GetArguments();
    const size_t compileObjectCount = m_compile_objects.size();
    if (compileObjectCount < 1)
    {
        // No compile objects specified...
        PrintUsage();
        return false;
    }

    // -v; --verbose
    m_verbose = m_argument_parser.IsOptionSpecified(OPTION_VERBOSE);

    // -d; --dist
    if (m_argument_parser.IsOptionSpecified(OPTION_DIST_FOLDER))
        m_dist_folder = m_argument_parser.GetValueForOption(OPTION_DIST_FOLDER);

    // --obj
    if (m_argument_parser.IsOptionSpecified(OPTION_OBJ_FOLDER))
        m_obj_folder = m_argument_parser.GetValueForOption(OPTION_OBJ_FOLDER);

    return true;
}

void LRCompilerArgs::ConfigureProjectDefinition(ProjectDefinition& definition) const
{
    if (!m_dist_folder.empty())
        definition.m_dist_directory = m_dist_folder;

    if (!m_obj_folder.empty())
        definition.m_obj_directory = m_obj_folder;
}
