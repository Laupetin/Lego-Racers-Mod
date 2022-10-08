#pragma once

#include "Asset/IAssetConverter.h"

namespace obj
{
	class ObjImporter final : public IAssetConverter
	{
	public:
		bool SupportsExtension(const std::string& extensionName) const override;
		bool Convert(const std::string& directory, const std::string& filePath) override;
	};
}