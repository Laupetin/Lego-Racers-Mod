#include "IUnitProcessor.h"

void UnitProcessorInputsAndOutputs::AddInput(std::filesystem::path inputFile)
{
    m_inputs.emplace_back(std::move(inputFile));
}

void UnitProcessorInputsAndOutputs::AddIntermediate(std::filesystem::path intermediate)
{
    m_intermediate.emplace_back(std::move(intermediate));
}

void UnitProcessorInputsAndOutputs::AddOutput(std::filesystem::path file, jam::JamFilePath jamPath)
{
    m_outputs.emplace_back(std::move(file), std::move(jamPath));
}

UnitProcessorResult::UnitProcessorResult()
= default;

UnitProcessorResult::UnitProcessorResult(std::filesystem::path file, jam::JamFilePath jamPath)
    : m_file(std::move(file)),
      m_jam_path(std::move(jamPath))
{
}
