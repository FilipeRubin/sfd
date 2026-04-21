#pragma once
#include <containers/texture-data.h>

class ITexture2DGenerator
{
public:
	virtual ~ITexture2DGenerator() = default;
	virtual TextureData GenerateTextureData() const = 0;
};
