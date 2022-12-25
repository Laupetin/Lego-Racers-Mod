#pragma once

#include <filesystem>
#include <vector>

#include "Project/ProjectContext.h"

class UnitProcessorInputsAndOutputs
{
public:
    std::vector<std::filesystem::path> m_inputs;
    std::vector<std::filesystem::path> m_outputs;
};

class UnitProcessorResult
{
public:
    std::filesystem::path m_file;
    std::string m_jam_path;

    UnitProcessorResult();
    UnitProcessorResult(std::filesystem::path file, std::string jamPath);
};

class IUnitProcessor
{
public:
    IUnitProcessor() = default;
    virtual ~IUnitProcessor() = default;
    IUnitProcessor(const IUnitProcessor& other) = default;
    IUnitProcessor(IUnitProcessor&& other) noexcept = default;
    IUnitProcessor& operator=(const IUnitProcessor& other) = default;
    IUnitProcessor& operator=(IUnitProcessor&& other) noexcept = default;

    [[nodiscard]] virtual bool Handles(const ProjectContext& context, const std::filesystem::path& file) const = 0;
    [[nodiscard]] virtual bool ExamineInputsAndOutputs(const ProjectContext& context, const std::filesystem::path& file, UnitProcessorInputsAndOutputs& io) const = 0;
    [[nodiscard]] virtual bool Compile(const ProjectContext& context, const std::filesystem::path& file, std::vector<UnitProcessorResult>& results) const = 0;
};
