#pragma once
#include "i-drawable.h"

class IRenderer
{
public:
	virtual ~IRenderer() = default;
	virtual void SetClearColor(float r, float g, float b) = 0;
	virtual void ClearScreen() const = 0;
	virtual IDrawable* CreateNDCMesh(float* data, size_t dataLength) const = 0;
};
