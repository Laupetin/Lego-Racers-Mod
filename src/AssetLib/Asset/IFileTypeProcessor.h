#pragma once
#include <istream>

class IFileTypeProcessor
{
public:
    IFileTypeProcessor() = default;
    virtual ~IFileTypeProcessor() = default;
    IFileTypeProcessor(const IFileTypeProcessor& other) = default;
    IFileTypeProcessor(IFileTypeProcessor&& other) noexcept = default;
    IFileTypeProcessor& operator=(const IFileTypeProcessor& other) = default;
    IFileTypeProcessor& operator=(IFileTypeProcessor&& other) noexcept = default;

    [[nodiscard]] virtual bool SupportFileExtension(const std::string& extension) const = 0;
    virtual void ProcessFile(const std::string& filePath, const void* inputData, size_t inputDataSize, std::ostream& output) const = 0;
};

class AbstractStreamingFileTypeProcessor : public IFileTypeProcessor
{
protected:
    virtual void ProcessFile(const std::string& filePath, std::istream& input, std::ostream& output) const = 0;

public:
    void ProcessFile(const std::string& filePath, const void* inputData, size_t inputDataSize, std::ostream& output) const override;
};
