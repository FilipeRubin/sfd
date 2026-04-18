#pragma once
#include "i-renderer-resource-manager.h"
#include <types/camera.h>
#include <types/directional-light.h>

class IRenderer
{
public:
	virtual ~IRenderer() = default;
	virtual void ClearScreen() const = 0;
	virtual void SetClearColor(float r, float g, float b) = 0;
	virtual void SetViewportSize(int width, int height) = 0;
	virtual IRendererResourceManager* GetResourceManager() const = 0;

	// Temporary - It may be better to move these methods to a new "IObjectManager" or some kind like that
	virtual void SetCamera(const Camera& camera) = 0;
	virtual void SetDirectionalLight(const DirectionalLight& light) = 0;
};
