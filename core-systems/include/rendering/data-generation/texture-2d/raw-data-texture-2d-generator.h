#pragma once
#include "i-texture-2d-generator.h"

class RawDataTexture2DGenerator : public ITexture2DGenerator
{
public:
	RawDataTexture2DGenerator(Shared<FixedArray<Color8>> data, const Dimensions& dimensions);
	TextureData GenerateTextureData() const override;
private:
	Shared<FixedArray<Color8>> m_data;
	Dimensions m_dimensions;
};