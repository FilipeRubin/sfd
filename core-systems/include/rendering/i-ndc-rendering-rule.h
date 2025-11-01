#pragma once
#include "i-rendering-rule.h"

class INDCRenderingRule : public IRenderingRule
{
public:
	virtual ~INDCRenderingRule() = default;
	virtual void SetColor(float r, float g, float b) = 0;
};