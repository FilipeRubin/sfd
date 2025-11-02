#pragma once
#include "i-ndc-rendering-rule.h"
#include "i-ndc-shape.h"

class IRendererResourceManager
{
public:
	virtual ~IRendererResourceManager() = default;
	virtual INDCRenderingRule* CreateNDCRenderingRule() = 0;
	virtual INDCShape* CreateNDCShape(float* vertices, size_t length) = 0;
};