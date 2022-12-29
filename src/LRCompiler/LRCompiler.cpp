#include "LRCompiler.h"

#include "LRCompilerArgs.h"
#include "Compiler/Compiler.h"
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

        return settings;
    }
}

bool LRCompiler::Start(const int argc, const char** argv)
{
    LRCompilerArgs args;
    if (!args.ParseArgs(argc, argv))
        return false;

    const ProjectContextCreator contextCreator(args);
    const auto compiler = ICompiler::Default(CreateCompilerSettings(args));
    const auto linker = ILinker::Default(CreateLinkerSettings(args));
    for (const auto& project : args.m_compile_projects)
    {
        const auto contexts = contextCreator.CreateContexts(project);

        for (const auto& context : contexts)
        {
            const auto compilationResult = compiler->Compile(*context);
            if (!compilationResult)
                continue;

            if (!linker->Link(*context, *compilationResult))
                continue;
        }
    }

    return true;
}
