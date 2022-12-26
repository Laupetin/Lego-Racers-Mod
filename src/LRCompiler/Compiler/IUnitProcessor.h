#pragma once

#include <cassert>
#include <filesystem>
#include <memory>
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

class IUnitProcessorUserPayload
{
protected:
    IUnitProcessorUserPayload() = default;

public:
    virtual ~IUnitProcessorUserPayload() = default;
    IUnitProcessorUserPayload(const IUnitProcessorUserPayload& other) = default;
    IUnitProcessorUserPayload(IUnitProcessorUserPayload&& other) noexcept = default;
    IUnitProcessorUserPayload& operator=(const IUnitProcessorUserPayload& other) = default;
    IUnitProcessorUserPayload& operator=(IUnitProcessorUserPayload&& other) noexcept = default;
};

class UnitProcessorUserData
{
public:
    void Set(std::unique_ptr<IUnitProcessorUserPayload> payload);

    template <typename T>
    T& As() const
    {
        assert(m_payload);
        return *reinterpret_cast<T*>(m_payload.get());
    }

private:
    std::unique_ptr<IUnitProcessorUserPayload> m_payload;
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
    [[nodiscard]] virtual bool ExamineInputsAndOutputs(const ProjectContext& context, UnitProcessorUserData& userData, const std::filesystem::path& file,
                                                       UnitProcessorInputsAndOutputs& io) const = 0;
    [[nodiscard]] virtual bool Compile(const ProjectContext& context, UnitProcessorUserData& userData, const std::filesystem::path& file,
                                       std::vector<UnitProcessorResult>& results) const = 0;
};
