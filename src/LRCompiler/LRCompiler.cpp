#include "LRCompiler.h"

#include "LRCompilerArgs.h"
#include "Compiler/Compiler.h"
#include "Linker/Linker.h"
#include "Project/ProjectContextCreator.h"

bool LRCompiler::Start(const int argc, const char** argv)
{
    LRCompilerArgs args;
    if (!args.ParseArgs(argc, argv))
        return false;

    const ProjectContextCreator contextCreator(args);
    const auto compiler = ICompiler::Default();
    const auto linker = ILinker::Default();
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
