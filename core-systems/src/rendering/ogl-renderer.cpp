#include "ogl-renderer.h"
#include "ogl.h"
#include "ogl-ndc-mesh.h"

void OGLRenderer::SetClearColor(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
}

void OGLRenderer::ClearScreen() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

IDrawable* OGLRenderer::CreateNDCMesh(float* data, size_t dataLength) const
{
	return new OGLNDCMesh(data, dataLength);
}
