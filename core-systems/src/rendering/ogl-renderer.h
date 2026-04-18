#pragma once
#include <rendering/i-renderer.h>
#include <ogl-graphics-backend.h>

class OGLRenderer : public IRenderer
{
public:
	OGLRenderer(OGLGraphicsBackend* backend);
	~OGLRenderer();
	void ClearScreen() const override;
	void SetClearColor(float r, float g, float b) override;
	void SetViewportSize(int width, int height) override;
	IRendererResourceManager* GetResourceManager() const override;

	void SetCamera(const Camera& camera) override;
	void SetDirectionalLight(const DirectionalLight& light) override;
private:
	IRendererResourceManager* m_resourceManager;
};
