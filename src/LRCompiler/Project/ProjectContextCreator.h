#pragma once

#include <string>
#include <memory>

#include "LRCompilerArgs.h"
#include "ProjectContext.h"

class ProjectContextCreator
{
public:
    explicit ProjectContextCreator(const LRCompilerArgs& args);

    std::vector<std::unique_ptr<ProjectContext>> CreateContexts(const std::string& projectPath) const;

private:
    std::vector<std::unique_ptr<ProjectContext>> CreateContextsForDirectoryOrFiles(const std::string& projectDirectory) const;
    std::unique_ptr<ProjectContext> CreateContextForDirectory(const std::string& projectDirectory) const;
    static void SetDefaultsFromFileName(ProjectDefinition& definition, const std::string& projectFile);
    std::unique_ptr<ProjectContext> CreateContextForFile(const std::string& projectFile) const;

    const LRCompilerArgs& m_args;
};
