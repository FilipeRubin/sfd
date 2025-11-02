#include "ogl-renderer.h"
#include "ogl.h"
#include "ogl-renderer-resource-manager.h"

OGLRenderer::OGLRenderer(OGLGraphicsBackend* backend) :
	m_resourceManager(new OGLRendererResourceManager(backend))
{
}

OGLRenderer::~OGLRenderer()
{
	delete m_resourceManager;
}

void OGLRenderer::SetClearColor(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
}

void OGLRenderer::ClearScreen() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

IRendererResourceManager* OGLRenderer::GetResourceManager() const
{
	return m_resourceManager;
}
