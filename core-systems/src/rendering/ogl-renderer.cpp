#include "ogl-renderer.h"
#include "ogl.h"
#include "ogl-renderer-parameter-manager.h"
#include "ogl-renderer-resource-manager.h"

OGLRenderer::OGLRenderer(OGLGraphicsBackend* backend) :
	m_parameterManager(new OGLRendererParameterManager()),
	m_resourceManager(new OGLRendererResourceManager(backend))
{
}

OGLRenderer::~OGLRenderer()
{
	delete m_parameterManager;
	delete m_resourceManager;
}

void OGLRenderer::ClearScreen() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OGLRenderer::SetClearColor(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
}

void OGLRenderer::SetViewportSize(int width, int height)
{
	glViewport(0, 0, width, height);
}

IRendererParameterManager* OGLRenderer::GetParameterManager() const
{
	return m_parameterManager;
}

IRendererResourceManager* OGLRenderer::GetResourceManager() const
{
	return m_resourceManager;
}
