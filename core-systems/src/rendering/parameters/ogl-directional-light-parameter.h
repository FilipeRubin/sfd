#pragma once
#include <rendering/parameters/i-directional-light-parameter.h>
#include <rendering/resources/ogl-rendering-rule.h>

class OGLDirectionalLightParameter : public IDirectionalLightParameter
{
public:
	void Bind(IRenderingRule* renderingRule) override;
	DirectionalLight& Light() override;
private:
	DirectionalLight m_light;
};
