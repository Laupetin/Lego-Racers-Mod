#pragma once

#include <memory>

#include "Compiler/Compiler.h"

class ILinker
{
public:
    static std::unique_ptr<ILinker> Default();

    ILinker() = default;
    virtual ~ILinker() = default;
    ILinker(const ILinker& other) = default;
    ILinker(ILinker&& other) noexcept = default;
    ILinker& operator=(const ILinker& other) = default;
    ILinker& operator=(ILinker&& other) noexcept = default;

    virtual bool Link(const ProjectContext& context, const CompilerResult& compilerResult) const = 0;
};
