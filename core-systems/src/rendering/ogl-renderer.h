#pragma once
#include <rendering/i-renderer.h>

class OGLRenderer : public IRenderer
{
public:
	void SetClearColor(float r, float g, float b) override;
	void ClearScreen() const override;
	IDrawable* CreateNDCMesh(float* data, size_t dataLength) const override;
};
