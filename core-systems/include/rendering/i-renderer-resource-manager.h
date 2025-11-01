#pragma once
#include "i-ndc-rendering-rule.h"

class IRendererResourceManager
{
public:
	virtual ~IRendererResourceManager() = default;
	virtual INDCRenderingRule* CreateNDCRenderingRule() = 0;
};