#pragma once
#include "i-basic-3d-rendering-rule.h"
#include "i-texture-2d.h"

class ILambertRenderingRule : public IBasic3DRenderingRule
{
public:
	virtual ~ILambertRenderingRule() = default;
	virtual void SetTexture(ITexture2D* texture) = 0;
};
