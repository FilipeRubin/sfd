#pragma once
#include "i-renderer-resource.h"
#include <types/dimensions.h>

class ITexture2D : public IRendererResource
{
public:
	virtual ~ITexture2D() = default;
	virtual void Bind() = 0;
	virtual const Dimensions& GetDimensions() const = 0;
};
