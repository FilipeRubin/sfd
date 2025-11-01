#include "ogl-renderer-resource-manager.h"
#include "ogl-ndc-rendering-rule.h"

INDCRenderingRule* OGLRendererResourceManager::CreateNDCRenderingRule()
{
    return new OGLNCDRenderingRule();
}
