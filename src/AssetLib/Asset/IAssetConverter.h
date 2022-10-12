#pragma once

#include <string>

class IAssetConverter
{
public:
    [[nodiscard]] virtual bool SupportsExtension(const std::string& extensionName) const = 0;
	virtual bool Convert(const std::string& directory, const std::string& filePath) = 0;

protected:
	IAssetConverter() = default;

public:
    virtual ~IAssetConverter() = default;
    IAssetConverter(const IAssetConverter& other) = default;
    IAssetConverter(IAssetConverter&& other) noexcept = default;
    IAssetConverter& operator=(const IAssetConverter& other) = default;
    IAssetConverter& operator=(IAssetConverter&& other) noexcept = default;
};