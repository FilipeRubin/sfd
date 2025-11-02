#include "ogl-renderer-resource-manager.h"
#include "ogl-ndc-rendering-rule.h"
#include "ogl-ndc-shape.h"

INDCRenderingRule* OGLRendererResourceManager::CreateNDCRenderingRule()
{
    return new OGLNDCRenderingRule();
}

INDCShape* OGLRendererResourceManager::CreateNDCShape(float* vertices, size_t length)
{
    return new OGLNDCShape(vertices, length);
}
