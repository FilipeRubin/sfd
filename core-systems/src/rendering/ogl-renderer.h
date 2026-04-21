#pragma once
#include <rendering/i-renderer.h>
#include <ogl-graphics-backend.h>

class OGLRenderer : public IRenderer
{
public:
	OGLRenderer(OGLGraphicsBackend* backend);
	~OGLRenderer();
	void ClearScreen() const override;
	void SetClearColor(const Color& color) override;
	void SetViewportSize(const Dimensions& size) override;
	IRendererParameterManager* GetParameterManager() const override;
	IRendererResourceManager* GetResourceManager() const override;
private:
	IRendererParameterManager* m_parameterManager;
	IRendererResourceManager* m_resourceManager;
};
