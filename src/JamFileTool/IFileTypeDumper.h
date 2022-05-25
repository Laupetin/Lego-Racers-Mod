#pragma once
#include <istream>

class IFileTypeDumper
{
public:
    IFileTypeDumper() = default;
    virtual ~IFileTypeDumper() = default;
    IFileTypeDumper(const IFileTypeDumper& other) = default;
    IFileTypeDumper(IFileTypeDumper&& other) noexcept = default;
    IFileTypeDumper& operator=(const IFileTypeDumper& other) = default;
    IFileTypeDumper& operator=(IFileTypeDumper&& other) noexcept = default;

    [[nodiscard]] virtual bool SupportFileExtension(const std::string& extension) const = 0;
    virtual void DumpFile(const std::string& fileName, const void* inputData, size_t inputDataSize, std::ostream& output) const = 0;
};

class AbstractStreamingFileTypeDumper : public IFileTypeDumper
{
protected:
    virtual void DumpFile(const std::string& filePath, std::istream& input, std::ostream& output) const = 0;

public:
    void DumpFile(const std::string& filePath, const void* inputData, size_t inputDataSize, std::ostream& output) const override;
};
