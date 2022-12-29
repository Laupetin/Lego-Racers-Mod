#pragma once

#include <cassert>
#include <filesystem>
#include <memory>
#include <vector>

#include "Jam/JamFilePath.h"
#include "Project/ProjectContext.h"

class UnitProcessorResult
{
public:
    std::filesystem::path m_file;
    jam::JamFilePath m_jam_path;

    UnitProcessorResult();
    UnitProcessorResult(std::filesystem::path file, jam::JamFilePath jamPath);
};

class UnitProcessorInputsAndOutputs
{
public:
    std::vector<std::filesystem::path> m_inputs;
    std::vector<UnitProcessorResult> m_outputs;

    void AddInput(std::filesystem::path inputFile);
    void AddOutput(UnitProcessorResult output);
    void AddOutput(std::filesystem::path file, jam::JamFilePath jamPath);
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

    [[nodiscard]] virtual bool ExamineInputsAndOutputs(const ProjectContext& context, const std::filesystem::path& file, UnitProcessorInputsAndOutputs& io) = 0;
    [[nodiscard]] virtual bool Compile(const ProjectContext& context, const std::filesystem::path& file) = 0;
};

class IUnitProcessorFactory
{
public:
    IUnitProcessorFactory() = default;
    virtual ~IUnitProcessorFactory() = default;
    IUnitProcessorFactory(const IUnitProcessorFactory& other) = default;
    IUnitProcessorFactory(IUnitProcessorFactory&& other) noexcept = default;
    IUnitProcessorFactory& operator=(const IUnitProcessorFactory& other) = default;
    IUnitProcessorFactory& operator=(IUnitProcessorFactory&& other) noexcept = default;

    [[nodiscard]] virtual std::unique_ptr<IUnitProcessor> CreateHandler(const ProjectContext& context, const std::filesystem::path& file) const = 0;
};
