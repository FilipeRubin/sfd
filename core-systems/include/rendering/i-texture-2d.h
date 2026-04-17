#pragma once
#include <types/dimensions.h>

class ITexture2D
{
public:
	virtual ~ITexture2D() = default;
	virtual Dimensions GetSize() = 0;
};