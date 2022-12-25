#include "IUnitProcessor.h"

UnitProcessorResult::UnitProcessorResult()
= default;

UnitProcessorResult::UnitProcessorResult(std::filesystem::path file, std::string jamPath)
    : m_file(std::move(file)),
      m_jam_path(std::move(jamPath))
{
}
