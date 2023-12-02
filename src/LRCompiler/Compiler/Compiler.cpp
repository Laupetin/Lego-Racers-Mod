#include "Compiler.h"

#include "Localization/SrfUnitProcessor.h"
#include "Material/BmpUnitProcessor.h"
#include "Material/IdbUnitProcessor.h"
#include "Material/MdbUnitProcessor.h"
#include "Material/TdbUnitProcessor.h"
#include "Model/GdbUnitProcessor.h"
#include "Model/ModelUnitProcessor.h"

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <limits>

namespace fs = std::filesystem;

void AddDefaultProcessors(std::vector<std::unique_ptr<IUnitProcessorFactory>>& processors)
{
    // =======================================
    // ADD YOUR CUSTOM UNIT PROCESSORS HERE
    // =======================================
    processors.emplace_back(std::make_unique<ModelUnitProcessorFactory>());
    processors.emplace_back(std::make_unique<BmpUnitProcessorFactory>());
    processors.emplace_back(std::make_unique<IdbUnitProcessorFactory>());
    processors.emplace_back(std::make_unique<GdbUnitProcessorFactory>());
    processors.emplace_back(std::make_unique<MdbUnitProcessorFactory>());
    processors.emplace_back(std::make_unique<SrfUnitProcessorFactory>());
    processors.emplace_back(std::make_unique<TdbUnitProcessorFactory>());
}

CompilerSettings::CompilerSettings()
    : m_verbose(false),
      m_recompile(false)
{
}

CompilerResult::CompilerResult()
    : m_asset_success_count(0u),
      m_asset_failed_count(0u),
      m_asset_skipped_count(0u),
      m_any_changes(false)
{
}

class CompilerImpl final : public ICompiler
{
public:
    explicit CompilerImpl(const CompilerSettings settings, std::vector<std::unique_ptr<IUnitProcessorFactory>> processors)
        : m_settings(settings),
          m_unit_processor_factories(std::move(processors))
    {
    }

    std::unique_ptr<CompilerResult> Compile(const ProjectContext& context) const override
    {
        std::cout << "============== Compiling " << context.m_project_name << " ==============\n";

        if (!PrepareContext(context))
        {
            std::cerr << "Failed to prepare context.\n";
            return nullptr;
        }

        auto result = std::make_unique<CompilerResult>();
        for (const auto& file : fs::recursive_directory_iterator(context.m_data_path))
        {
            if (!file.is_regular_file())
                continue;

            const auto unitProcessor = FindUnitProcessorForFile(context, file.path());
            if (!unitProcessor)
                continue;

            if (!ProcessUnit(*unitProcessor, context, *result, file.path()))
            {
                std::cerr << "Failed to compile \"" << fs::relative(file, context.m_data_path).string() << "\"\n";
                result->m_asset_failed_count++;
            }
        }

        std::cout << "Compiler result: " << result->m_asset_success_count << " compiled, " << result->m_asset_failed_count << " failed, "
                  << result->m_asset_skipped_count << " skipped.\n";
        return result;
    }

private:
    bool PrepareContext(const ProjectContext& context) const
    {
        if (!fs::is_directory(context.m_data_path))
        {
            std::cerr << "Data directory " << context.m_data_path << " does not exist!\n";
            return false;
        }

        if (!fs::is_directory(context.m_dist_path) && !fs::create_directories(context.m_dist_path))
        {
            std::cerr << "Could not create dist directory " << context.m_dist_path << "!\n";
            return false;
        }

        if (!fs::is_directory(context.m_obj_path) && !fs::create_directories(context.m_obj_path))
        {
            std::cerr << "Could not create obj directory " << context.m_obj_path << "!\n";
            return false;
        }

        return true;
    }

    [[nodiscard]] std::unique_ptr<IUnitProcessor> FindUnitProcessorForFile(const ProjectContext& context, const fs::path& filePath) const
    {
        for (const auto& unitProcessorFactory : m_unit_processor_factories)
        {
            if (auto processor = unitProcessorFactory->CreateHandler(context, filePath))
                return processor;
        }

        return nullptr;
    }

    bool ProcessUnit(IUnitProcessor& unitProcessor, const ProjectContext& context, CompilerResult& result, const fs::path& file) const
    {
        UnitProcessorInputsAndOutputs io;

        const auto relativePathToData = fs::relative(file, context.m_data_path);
        if (!unitProcessor.ExamineInputsAndOutputs(context, file, io))
            return false;

        if (io.m_inputs.empty() || io.m_outputs.empty())
        {
            std::cerr << "UnitProcessor of file \"" << relativePathToData.string() << "\" must produce inputs and outputs\n";
            return false;
        }

        std::vector<fs::path> missingFiles;
        int64_t maxWriteInput, minWriteOutput;
        ExamineInputFiles(io, missingFiles, maxWriteInput);
        if (!missingFiles.empty())
        {
            std::cerr << "Missing files for compiling \"" << relativePathToData.string() << "\":\n";
            for (const auto& missingFile : missingFiles)
                std::cerr << "  " << missingFile << "\n";

            return false;
        }

        ExamineOutputFiles(io, missingFiles, minWriteOutput);

        if (m_settings.m_recompile || !missingFiles.empty() || minWriteOutput < maxWriteInput)
        {
            std::cout << "Compiling: \"" << relativePathToData.string() << "\"\n";
            if (!CreateDirectoriesForOutput(io))
                return false;

            if (!unitProcessor.Compile(context, file))
            {
                std::cerr << "Compilation failed: \"" << relativePathToData.string() << "\"\n";
                return false;
            }

            result.m_any_changes = true;
            result.m_asset_success_count++;
        }
        else
        {
            std::cout << "File up to date: \"" << relativePathToData.string() << "\"\n";
            result.m_asset_skipped_count++;
        }

        for (auto& output : io.m_outputs)
            result.m_unit_processor_results.emplace_back(std::move(output));

        return true;
    }

    static void ExamineInputFiles(const UnitProcessorInputsAndOutputs& files, std::vector<fs::path>& missingFiles, int64_t& maxTimestamp)
    {
        auto minTimestamp = std::numeric_limits<int64_t>::max();
        maxTimestamp = std::numeric_limits<int64_t>::min();

        for (const auto& file : files.m_inputs)
        {
            ExamineFile(file, missingFiles, minTimestamp, maxTimestamp);
        }
    }

    static void ExamineOutputFiles(const UnitProcessorInputsAndOutputs& files, std::vector<fs::path>& missingFiles, int64_t& minTimestamp)
    {
        minTimestamp = std::numeric_limits<int64_t>::max();
        auto maxTimestamp = std::numeric_limits<int64_t>::min();

        for (const auto& result : files.m_intermediate)
        {
            ExamineFile(result, missingFiles, minTimestamp, maxTimestamp);
        }

        for (const auto& result : files.m_outputs)
        {
            ExamineFile(result.m_file, missingFiles, minTimestamp, maxTimestamp);
        }
    }

    static void ExamineFile(const fs::path& file, std::vector<fs::path>& missingFiles, int64_t& minTimestamp, int64_t& maxTimestamp)
    {
        const auto fileStatus = fs::status(file);
        if (fileStatus.type() != std::filesystem::file_type::regular)
        {
            missingFiles.emplace_back(file);
            return;
        }

        std::error_code err;
        const auto lastWriteTime = fs::last_write_time(file, err);
        if (err)
        {
            missingFiles.emplace_back(file);
            return;
        }

        const auto lastWriteTimeNumeric = static_cast<int64_t>(lastWriteTime.time_since_epoch().count());
        minTimestamp = std::min(minTimestamp, lastWriteTimeNumeric);
        maxTimestamp = std::max(maxTimestamp, lastWriteTimeNumeric);
    }

    static bool CreateDirectoriesForOutput(const UnitProcessorInputsAndOutputs& files)
    {
        return std::all_of(files.m_intermediate.begin(),
                           files.m_intermediate.end(),
                           [](const fs::path& file)
                           {
                               return CreateOutputDirectoryForFile(file);
                           })
               && std::all_of(files.m_outputs.begin(),
                              files.m_outputs.end(),
                              [](const UnitProcessorResult& result)
                              {
                                  return CreateOutputDirectoryForFile(result.m_file);
                              });
    }

    static bool CreateOutputDirectoryForFile(const fs::path& file)
    {
        const auto parentPath = fs::absolute(file).parent_path();

        if (!fs::is_directory(parentPath) && !fs::create_directories(parentPath))
        {
            std::cerr << "Failed to create directory " << parentPath << "!\n";
            return false;
        }

        return true;
    }

    CompilerSettings m_settings;
    std::vector<std::unique_ptr<IUnitProcessorFactory>> m_unit_processor_factories;
};

std::unique_ptr<ICompiler> ICompiler::Default(CompilerSettings settings)
{
    std::vector<std::unique_ptr<IUnitProcessorFactory>> processors;
    AddDefaultProcessors(processors);

    return std::make_unique<CompilerImpl>(settings, std::move(processors));
}

std::unique_ptr<ICompiler> ICompiler::Custom(CompilerSettings settings, std::vector<std::unique_ptr<IUnitProcessorFactory>> processors)
{
    return std::make_unique<CompilerImpl>(settings, std::move(processors));
}
