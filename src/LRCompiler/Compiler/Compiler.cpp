#include "Compiler.h"

#include <cstdint>
#include <filesystem>
#include <limits>

#include "Material/MdbUnitProcessor.h"
#include "Model/GdbUnitProcessor.h"

namespace fs = std::filesystem;

void AddDefaultProcessors(std::vector<std::unique_ptr<IUnitProcessorFactory>>& processors)
{
    // =======================================
    // ADD YOUR CUSTOM UNIT PROCESSORS HERE
    // =======================================
    processors.emplace_back(std::make_unique<GdbUnitProcessorFactory>());
    processors.emplace_back(std::make_unique<MdbUnitProcessorFactory>());
}

CompilerResult::CompilerResult()
    : m_any_changes(false)
{
}

class CompilerImpl final : public ICompiler
{
public:
    explicit CompilerImpl(std::vector<std::unique_ptr<IUnitProcessorFactory>> processors)
        : m_unit_processor_factories(std::move(processors))
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
                std::cerr << "Failed to compile \"" << fs::relative(file, context.m_data_path).string() << "\"\n";
        }

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

        if (!missingFiles.empty() || minWriteOutput < maxWriteInput)
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
        }
        else
            std::cout << "File up to date: \"" << relativePathToData.string() << "\"\n";

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
        for (const auto& result : files.m_outputs)
        {
            const auto parentPath = fs::absolute(result.m_file).parent_path();

            if (!fs::is_directory(parentPath) && !fs::create_directories(parentPath))
            {
                std::cerr << "Failed to create directory " << parentPath << "!\n";
                return false;
            }
        }

        return true;
    }

    std::vector<std::unique_ptr<IUnitProcessorFactory>> m_unit_processor_factories;
};

std::unique_ptr<ICompiler> ICompiler::Default()
{
    std::vector<std::unique_ptr<IUnitProcessorFactory>> processors;
    AddDefaultProcessors(processors);

    return std::make_unique<CompilerImpl>(std::move(processors));
}

std::unique_ptr<ICompiler> ICompiler::Custom(std::vector<std::unique_ptr<IUnitProcessorFactory>> processors)
{
    return std::make_unique<CompilerImpl>(std::move(processors));
}
