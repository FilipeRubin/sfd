#include "ogl-camera-3d-parameter.h"

void OGLCamera3DParameter::Bind(IRenderingRule* renderingRule)
{
	Matrix4x4 projection = Matrix4x4::Perspective(
		m_camera.aspectRatio,
		m_camera.vFOV,
		m_camera.zNear,
		m_camera.zFar
	);
	Matrix4x4 view = Matrix4x4::RotationX(m_camera.rotation.x) * Matrix4x4::RotationY(m_camera.rotation.y) * Matrix4x4::RotationZ(m_camera.rotation.z) * Matrix4x4::Translation(m_camera.position);

	OGLRenderingRule* oglRenderingRule = dynamic_cast<OGLRenderingRule*>(renderingRule);

	oglRenderingRule->SetUniform("u_projection", projection);
	oglRenderingRule->SetUniform("u_view", view);
}

Camera3D& OGLCamera3DParameter::Camera()
{
	return m_camera;
}
