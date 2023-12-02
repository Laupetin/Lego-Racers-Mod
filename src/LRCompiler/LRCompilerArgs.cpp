#include "LRCompilerArgs.h"

#include "Arguments/UsageInformation.h"
#include "Project/ProjectDefinition.h"

#include <regex>
#include <type_traits>

// clang-format off

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
    .WithDescription("Specifies the dist folder containing the compilation results. Defaults to \"" 
        + std::string(ProjectDefinition::DEFAULT_DIST_FOLDER) + "\"")
    .WithParameter("distFolderPath")
    .Build();

const CommandLineOption* const OPTION_OBJ_FOLDER = 
    CommandLineOption::Builder::Create()
    .WithLongName("obj")
    .WithDescription("Specifies the obj folder containing intermediate compilation files. Defaults to \""
        + std::string(ProjectDefinition::DEFAULT_OBJ_FOLDER) + "\"")
    .WithParameter("objFolderPath")
    .Build();

const CommandLineOption* const OPTION_RECOMPILE =
    CommandLineOption::Builder::Create()
    .WithLongName("recompile")
    .WithDescription("Recompiles everything regardless whether it is outdated or not.")
    .Build();

const CommandLineOption* const OPTION_FORCE_LINKING = 
    CommandLineOption::Builder::Create()
    .WithLongName("force-linking")
    .WithDescription("Forces the linker to produce new target regardless whether it is outdated or not.")
    .Build();

const CommandLineOption* const OPTION_COPY_TO = 
    CommandLineOption::Builder::Create()
    .WithLongName("copy-to")
    .WithDescription("Copies the newly linked target to the specified location.")
    .WithParameter("copyToPath")
    .Build();

// clang-format on

const CommandLineOption* const COMMAND_LINE_OPTIONS[]{
    OPTION_HELP,
    OPTION_VERBOSE,
    OPTION_DIST_FOLDER,
    OPTION_OBJ_FOLDER,
    OPTION_RECOMPILE,
    OPTION_FORCE_LINKING,
    OPTION_COPY_TO,
};

LRCompilerArgs::LRCompilerArgs()
    : m_verbose(false),
      m_recompile(false),
      m_force_linking(false),
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

    usage.AddArgument("compilationProjects");
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

    m_compile_projects = m_argument_parser.GetArguments();
    const size_t compileProjectCount = m_compile_projects.size();
    if (compileProjectCount < 1)
    {
        // No compile projects specified...
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

    // --copy-to
    if (m_argument_parser.IsOptionSpecified(OPTION_COPY_TO))
        m_copy_to = m_argument_parser.GetValueForOption(OPTION_COPY_TO);

    // --recompile
    m_recompile = m_argument_parser.IsOptionSpecified(OPTION_RECOMPILE);

    // --force-linking
    m_force_linking = m_argument_parser.IsOptionSpecified(OPTION_FORCE_LINKING);

    return true;
}

void LRCompilerArgs::ConfigureProjectDefinition(ProjectDefinition& definition) const
{
    if (!m_dist_folder.empty())
        definition.m_dist_directory = m_dist_folder;

    if (!m_obj_folder.empty())
        definition.m_obj_directory = m_obj_folder;
}
