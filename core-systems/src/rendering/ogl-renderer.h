#pragma once
#include <rendering/i-renderer.h>
#include <ogl-graphics-backend.h>

class OGLRenderer : public IRenderer
{
public:
	OGLRenderer(OGLGraphicsBackend* backend);
	~OGLRenderer();
	void ClearScreen() const override;
	IRenderingRule* GetRenderingRule() override;
	void SetClearColor(float r, float g, float b) override;
	void SetRenderingRule(IRenderingRule* renderingRule) override;
	void SetViewportSize(int width, int height) override;
	IRendererResourceManager* GetResourceManager() const override;
private:
	IRendererResourceManager* m_resourceManager;
	IRenderingRule* m_renderingRule;
};
