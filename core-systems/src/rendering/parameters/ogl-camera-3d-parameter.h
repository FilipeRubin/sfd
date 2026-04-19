#pragma once
#include <rendering/parameters/i-camera-3d-parameter.h>
#include <rendering/resources/ogl-rendering-rule.h>

class OGLCamera3DParameter : public ICamera3DParameter
{
public:
	void Bind(IRenderingRule* renderingRule) override;
	Camera3D& Camera() override;
private:
	Camera3D m_camera;
};