#pragma once

#include "Asset/IAssetConverter.h"

namespace gltf
{
	class GltfExporter final : public IAssetConverter
	{
	public:
		[[nodiscard]] bool SupportsExtension(const std::string& extensionName) const override;
		bool Convert(const std::string& directory, const std::string& filePath) override;
	};
}