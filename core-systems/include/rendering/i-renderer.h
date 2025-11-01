#pragma once
#include "i-renderer-resource-manager.h"

class IRenderer
{
public:
	virtual ~IRenderer() = default;
	virtual void SetClearColor(float r, float g, float b) = 0;
	virtual void ClearScreen() const = 0;
	virtual IRendererResourceManager* GetResourceManager() const = 0;
};
