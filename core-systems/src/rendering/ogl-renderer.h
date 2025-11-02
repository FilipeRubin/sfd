#pragma once
#include <rendering/i-renderer.h>
#include <ogl-graphics-backend.h>

class OGLRenderer : public IRenderer
{
public:
	OGLRenderer(OGLGraphicsBackend* backend);
	~OGLRenderer();
	void SetClearColor(float r, float g, float b) override;
	void ClearScreen() const override;
	IRendererResourceManager* GetResourceManager() const override;
private:
	IRendererResourceManager* m_resourceManager;
};
