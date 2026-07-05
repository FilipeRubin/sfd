#pragma once
#include "i-texture-2d-generator.h"
#include <types/color.h>

class CheckerboardTexture2DGenerator : public ITexture2DGenerator
{
public:
	CheckerboardTexture2DGenerator(Dimensions dimensions, Color color1, Color color2);
	TextureData GenerateTextureData() const override;
private:
	Dimensions m_dimensions;
	Color m_color1;
	Color m_color2;
};
