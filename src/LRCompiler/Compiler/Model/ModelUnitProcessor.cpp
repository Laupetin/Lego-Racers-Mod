#include "ModelUnitProcessor.h"

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

#include "FileUtils.h"
#include "StringUtils.h"
#include "Asset/Gdb/GdbBinaryWriter.h"
#include "Asset/Gdb/GdbStructReader.h"
#include "Asset/Gdb/GdbStructWriter.h"
#include "Asset/Gdb/GdbTextReader.h"

namespace fs = std::filesystem;
using namespace nlohmann;

namespace model
{
    static constexpr auto PROPERTY_MODEL_FILE = "modelFile";
    static constexpr auto PROPERTY_SCALE = "scale";

    enum class SupportedModelFormat
    {
        UNKNOWN,

        OBJ,
        GDB
    };
}

class ModelUnitProcessor final : public IUnitProcessor
{
public:
    ModelUnitProcessor()
        : m_model_format(model::SupportedModelFormat::UNKNOWN),
          m_scale(1.0f),
          m_scale_specified(false)
    {
    }

    [[nodiscard]] bool ExamineInputsAndOutputs(const ProjectContext& context, const std::filesystem::path& file, UnitProcessorInputsAndOutputs& io) override
    {
        const auto relativeFilePath = fs::relative(file, context.m_data_path);
        m_out_path = (context.m_obj_path / relativeFilePath).replace_extension(".gdb_bin");

        if (!ParseAsset(file))
            return false;

        io.AddInput(file);
        io.AddInput(m_model_file);
        io.AddOutput(m_out_path, jam::JamFilePath(relativeFilePath.string()));

        return true;
    }

    [[nodiscard]] bool Compile(const ProjectContext& context, const std::filesystem::path& file) override
    {
        std::ifstream model(m_model_file, std::ios::out | std::ios::binary);
        if (!model.is_open())
        {
            std::cerr << "Could not open model file " << m_out_path << "!\n";
            return false;
        }
        std::ofstream out(m_out_path, std::ios::out | std::ios::binary);
        if (!out.is_open())
        {
            std::cerr << "Could not open output file " << m_out_path << "!\n";
            return false;
        }

        std::unique_ptr<gdb::Model> gdbModel;

        switch (m_model_format)
        {
        case model::SupportedModelFormat::GDB:
            gdbModel = LoadFromGdb(model, m_model_file);
            break;

        case model::SupportedModelFormat::OBJ:
            gdbModel = LoadAndConvertFromObj(model, m_model_file);
            break;

        case model::SupportedModelFormat::UNKNOWN:
        default:
            assert(false);
            break;
        }

        if (!gdbModel)
        {
            std::cerr << "Failed to convert model to GDB: " << m_model_file << "!\n";
            return false;
        }

        ApplyModelValuesToGdb(*gdbModel);

        try
        {
            const auto writer = gdb::GdbBinaryWriter::Create(out);
            gdb::GdbStructReader::Read(*gdbModel, *writer);
        }
        catch (std::exception& e)
        {
            std::cerr << "Compiling GDB failed: " << e.what() << "\n";
            return false;
        }

        return true;
    }

private:
    bool ParseAsset(const std::filesystem::path& file)
    {
        std::ifstream in(file, std::ios::in | std::ios::binary);
        if (!in.is_open())
        {
            std::cerr << "Could not open input file " << file << "!\n";
            return false;
        }

        json root;
        try
        {
            root = json::parse(in);
        }
        catch (json::parse_error& e)
        {
            std::cerr << "Parsing model asset failed (JsonParseError): " << e.what() << "!\n";
            return false;
        }

        return ParseModelFile(root, file)
            && ParseScale(root, file);
    }

    bool ParseModelFile(const json& root, const std::filesystem::path& file)
    {
        if (!root.contains(model::PROPERTY_MODEL_FILE))
        {
            std::cerr << "Model asset must contain string modelFile property: " << file << "!\n";
            return false;
        }

        const auto& modelFile = root["modelFile"];
        if (!modelFile.is_string())
        {
            std::cerr << "Model asset modelFile property must be a string: " << file << "!\n";
            return false;
        }

        const auto modelFileString = modelFile.get<std::string>();
        if (modelFileString.empty())
        {
            std::cerr << "Model file path cannot be empty: " << file << "!\n";
            return false;
        }

        if (modelFileString.find_first_of(utils::ILLEGAL_PATH_CHARS) != std::string::npos)
        {
            std::cerr << "Model file path contains illegal characters: " << file << "!\n";
            return false;
        }

        fs::path modelFilePath(modelFileString);
        if (modelFilePath.is_relative())
            m_model_file = fs::absolute(file).parent_path() / modelFilePath;
        else
            m_model_file = std::move(modelFilePath);

        const auto modelFileExtension = m_model_file.extension().string();
        if (utils::StringEqualsIgnoreCase(modelFileExtension, ".obj"))
        {
            m_model_format = model::SupportedModelFormat::OBJ;
        }
        else if (utils::StringEqualsIgnoreCase(modelFileExtension, ".gdb"))
        {
            m_model_format = model::SupportedModelFormat::GDB;
        }
        else
        {
            std::cerr << "Model uses unsupported extension \"" << modelFileExtension << "\": " << file << "!\n";
            return false;
        }

        return true;
    }

    bool ParseScale(const json& root, const std::filesystem::path& file)
    {
        if (!root.contains(model::PROPERTY_SCALE))
        {
            m_scale = 1.0f;
            m_scale_specified = false;
            return true;
        }

        const auto& scale = root["scale"];
        if (!scale.is_number_float())
        {
            std::cerr << "Model asset scale property must be floating point: " << file << "!\n";
            return false;
        }

        m_scale = scale.get<float>();
        m_scale_specified = true;

        return true;
    }

    std::unique_ptr<gdb::Model> LoadFromGdb(std::ifstream& in, const fs::path& file) const
    {
        auto model = std::make_unique<gdb::Model>();

        try
        {
            const auto writer = gdb::GdbStructWriter::Create(*model);
            gdb::GdbTextReader::Read(in, *writer);
        }
        catch (std::exception& e)
        {
            std::cerr << "Failed to read model: " << file << "!\n";
            return nullptr;
        }

        return model;
    }

    std::unique_ptr<gdb::Model> LoadAndConvertFromObj(std::ifstream& in, const fs::path& file)
    {
        // TODO
        return nullptr;
    }

    void ApplyModelValuesToGdb(gdb::Model& model) const
    {
        if (m_scale_specified)
            model.m_scale = m_scale;
    }

    fs::path m_out_path;
    fs::path m_model_file;
    model::SupportedModelFormat m_model_format;
    float m_scale;
    bool m_scale_specified;
};

std::unique_ptr<IUnitProcessor> ModelUnitProcessorFactory::CreateHandler(const ProjectContext& context, const std::filesystem::path& file) const
{
    if (utils::StringEndsWithIgnoreCase(file.filename().string(), ".model.json"))
        return std::make_unique<ModelUnitProcessor>();

    return nullptr;
}
