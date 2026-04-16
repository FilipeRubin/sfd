#pragma once
#include "i-renderer-resource-manager.h"

class IRenderer
{
public:
	virtual ~IRenderer() = default;
	virtual void ClearScreen() const = 0;
	virtual IRenderingRule* GetRenderingRule() = 0;
	virtual void SetClearColor(float r, float g, float b) = 0;
	virtual void SetRenderingRule(IRenderingRule* renderingRule) = 0;
	virtual void SetViewportSize(int width, int height) = 0;
	virtual IRendererResourceManager* GetResourceManager() const = 0;
};
