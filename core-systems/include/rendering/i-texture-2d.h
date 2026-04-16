#pragma once
#include <math/dimensions.h>

class ITexture2D
{
public:
	virtual ~ITexture2D() = default;
	virtual Dimensions GetSize() = 0;
};