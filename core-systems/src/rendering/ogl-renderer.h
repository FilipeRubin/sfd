#pragma once
#include <rendering/i-renderer.h>

class OGLRenderer : public IRenderer
{
public:
	OGLRenderer();
	~OGLRenderer();
	void SetClearColor(float r, float g, float b) override;
	void ClearScreen() const override;
	IRendererResourceManager* GetResourceManager() const override;
private:
	IRendererResourceManager* m_resourceManager;
};
