#pragma once

#include "Compiler/Compiler.h"

#include <memory>

class LinkerSettings
{
public:
    std::string m_copy_to;
    bool m_verbose;
    bool m_force_linking;

    LinkerSettings();
};

class ILinker
{
public:
    static std::unique_ptr<ILinker> Default(LinkerSettings settings);

    ILinker() = default;
    virtual ~ILinker() = default;
    ILinker(const ILinker& other) = default;
    ILinker(ILinker&& other) noexcept = default;
    ILinker& operator=(const ILinker& other) = default;
    ILinker& operator=(ILinker&& other) noexcept = default;

    virtual bool Link(const ProjectContext& context, const CompilerResult& compilerResult) const = 0;
};
