#pragma once
#include "i-rendering-rule.h"
#include <math/matrix4x4.h>

class IBasic3DRenderingRule : public IRenderingRule
{
public:
	virtual ~IBasic3DRenderingRule() = default;
	virtual void SetProjection(const Matrix4x4& projection) = 0;
	virtual void SetModel(const Matrix4x4& model) = 0;
};
