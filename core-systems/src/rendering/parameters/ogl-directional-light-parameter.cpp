#include "ogl-directional-light-parameter.h"

void OGLDirectionalLightParameter::Bind(IRenderingRule* renderingRule)
{
    OGLRenderingRule* oglRenderingRule = dynamic_cast<OGLRenderingRule*>(renderingRule);
    oglRenderingRule->SetUniform("u_ambientLight", m_light.ambient);
    oglRenderingRule->SetUniform("u_directionalLightDiffuse", m_light.diffuse);
    oglRenderingRule->SetUniform("u_directionalLightDirection", m_light.direction);
}

DirectionalLight& OGLDirectionalLightParameter::Light()
{
    return m_light;
}
