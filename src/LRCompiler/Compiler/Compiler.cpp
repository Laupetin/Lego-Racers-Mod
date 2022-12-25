#include "Compiler.h"

#include <filesystem>

namespace fs = std::filesystem;

class CompilerImpl final : public ICompiler
{
public:
    explicit CompilerImpl(std::vector<std::unique_ptr<IUnitProcessor>> processors)
        : m_unit_processors(std::move(processors))
    {
    }

    ~CompilerImpl() override = default;
    CompilerImpl(const CompilerImpl& other) = delete;
    CompilerImpl(CompilerImpl&& other) noexcept = default;
    CompilerImpl& operator=(const CompilerImpl& other) = delete;
    CompilerImpl& operator=(CompilerImpl&& other) noexcept = default;

    std::unique_ptr<CompilerResult> Compile(const ProjectContext& context) const override
    {
        if (!PrepareContext(context))
        {
            std::cerr << "Failed to prepare context.\n";
            return nullptr;
        }

        // TODO
        return nullptr;
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

    std::vector<std::unique_ptr<IUnitProcessor>> m_unit_processors;
};

std::unique_ptr<ICompiler> ICompiler::Default()
{
    // =======================================
    // ADD YOUR CUSTOM UNIT PROCESSORS HERE
    // =======================================
    return std::make_unique<CompilerImpl>(std::vector<std::unique_ptr<IUnitProcessor>>());
}

std::unique_ptr<ICompiler> ICompiler::Custom(std::vector<std::unique_ptr<IUnitProcessor>> processors)
{
    return std::make_unique<CompilerImpl>(std::move(processors));
}
