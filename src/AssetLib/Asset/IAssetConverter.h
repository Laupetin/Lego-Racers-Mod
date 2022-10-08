#pragma once

#include <string>

class IAssetConverter
{
public:
	virtual bool SupportsExtension(const std::string& extensionName) const = 0;
	virtual bool Convert(const std::string& directory, const std::string& filePath) = 0;

protected:
	IAssetConverter() = default;
	virtual ~IAssetConverter() = default;
};