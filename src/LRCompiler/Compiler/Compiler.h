#pragma once

#include <memory>
#include <vector>

#include "IUnitProcessor.h"

class CompilerSettings
{
public:
    bool m_verbose;
    bool m_recompile;

    CompilerSettings();
};

class CompilerResult
{
public:
    bool m_any_changes;
    std::vector<UnitProcessorResult> m_unit_processor_results;

    CompilerResult();
};

class ICompiler
{
public:
    static std::unique_ptr<ICompiler> Default(CompilerSettings settings);
    static std::unique_ptr<ICompiler> Custom(CompilerSettings settings, std::vector<std::unique_ptr<IUnitProcessorFactory>> processors);

    ICompiler() = default;
    virtual ~ICompiler() = default;
    ICompiler(const ICompiler& other) = default;
    ICompiler(ICompiler&& other) noexcept = default;
    ICompiler& operator=(const ICompiler& other) = default;
    ICompiler& operator=(ICompiler&& other) noexcept = default;

    virtual std::unique_ptr<CompilerResult> Compile(const ProjectContext& context) const = 0;
};
