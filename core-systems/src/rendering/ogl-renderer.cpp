#include "ogl-renderer.h"
#include "ogl.h"
#include "ogl-renderer-resource-manager.h"

OGLRenderer::OGLRenderer(OGLGraphicsBackend* backend) :
	m_resourceManager(new OGLRendererResourceManager(backend)),
	m_renderingRule(nullptr)
{
}

OGLRenderer::~OGLRenderer()
{
	delete m_resourceManager;
}

void OGLRenderer::ClearScreen() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

IRenderingRule* OGLRenderer::GetRenderingRule()
{
	return m_renderingRule;
}

void OGLRenderer::SetClearColor(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
}

void OGLRenderer::SetRenderingRule(IRenderingRule* renderingRule)
{
	renderingRule->Bind();
	m_renderingRule = renderingRule;
}

void OGLRenderer::SetViewportSize(int width, int height)
{
	glViewport(0, 0, width, height);
}

IRendererResourceManager* OGLRenderer::GetResourceManager() const
{
	return m_resourceManager;
}
