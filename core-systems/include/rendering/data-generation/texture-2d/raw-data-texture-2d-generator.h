#pragma once
#include "i-texture-2d-generator.h"

class RawDataTexture2DGenerator : public ITexture2DGenerator
{
public:
	RawDataTexture2DGenerator(Color8* data, const Dimensions& dimensions);
	~RawDataTexture2DGenerator();
	TextureData GenerateTextureData() const override;
private:
	Color8* m_data;
	Dimensions m_dimensions;
};