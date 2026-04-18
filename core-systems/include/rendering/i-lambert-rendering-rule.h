#pragma once
#include "i-rendering-rule.h"
#include "i-texture-2d.h"
#include <math/matrix4x4.h>
#include <types/color8.h>
#include <types/directional-light.h>

class ILambertRenderingRule : public IRenderingRule
{
public:
	virtual ~ILambertRenderingRule() = default;
	virtual void SetDirectionalLight(const DirectionalLight& directionalLight) = 0;
	virtual void SetModel(const Matrix4x4& model) = 0;
	virtual void SetView(const Matrix4x4& view) = 0;
	virtual void SetProjection(const Matrix4x4& projection) = 0;
};
