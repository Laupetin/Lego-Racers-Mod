#include "LRCompiler.h"

#include "Compiler/Compiler.h"
#include "LRCompilerArgs.h"
#include "Linker/Linker.h"
#include "Project/ProjectContextCreator.h"

namespace
{
    CompilerSettings CreateCompilerSettings(const LRCompilerArgs& args)
    {
        CompilerSettings settings;

        settings.m_verbose = args.m_verbose;
        settings.m_recompile = args.m_recompile;

        return settings;
    }

    LinkerSettings CreateLinkerSettings(const LRCompilerArgs& args)
    {
        LinkerSettings settings;

        settings.m_verbose = args.m_verbose;
        settings.m_force_linking = args.m_force_linking;
        settings.m_copy_to = args.m_copy_to;

        return settings;
    }
} // namespace

bool LRCompiler::Start(const int argc, const char** argv)
{
    LRCompilerArgs args;
    if (!args.ParseArgs(argc, argv))
        return false;

    const ProjectContextCreator contextCreator(args);
    const auto compiler = ICompiler::Default(CreateCompilerSettings(args));
    const auto linker = ILinker::Default(CreateLinkerSettings(args));
    size_t projectCount = 0u;
    size_t projectSuccessCount = 0u;
    for (const auto& project : args.m_compile_projects)
    {
        const auto contexts = contextCreator.CreateContexts(project);

        for (const auto& context : contexts)
        {
            projectCount++;

            const auto compilationResult = compiler->Compile(*context);
            if (!compilationResult || compilationResult->m_asset_failed_count > 0)
                continue;

            if (!linker->Link(*context, *compilationResult))
                continue;

            projectSuccessCount++;
        }
    }

    if (projectCount > 1)
    {
        std::cout << "\nProjects successfully handled: " << projectSuccessCount << "/" << projectCount << "\n";
    }

    return projectSuccessCount == projectCount;
}
