#pragma once

#include <filesystem>
#include <vector>

#include "JamFilePath.h"
#include "Project/ProjectContext.h"

class UnitProcessorResult
{
public:
    std::filesystem::path m_file;
    JamFilePath m_jam_path;

    UnitProcessorResult();
    UnitProcessorResult(std::filesystem::path file, JamFilePath jamPath);
};

class UnitProcessorInputsAndOutputs
{
public:
    std::vector<std::filesystem::path> m_inputs;
    std::vector<UnitProcessorResult> m_outputs;

    void AddInput(std::filesystem::path inputFile);
    void AddOutput(UnitProcessorResult output);
    void AddOutput(std::filesystem::path file, JamFilePath jamPath);
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
