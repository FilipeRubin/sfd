#include "ogl-transform-3d-parameter.h"
#include <rendering/resources/ogl-rendering-rule.h>

void OGLTransform3DParameter::Bind(IRenderingRule* renderingRule)
{
	OGLRenderingRule* oglRenderingRule = dynamic_cast<OGLRenderingRule*>(renderingRule);

	Matrix4x4 model =
		Matrix4x4::Translation(m_transform.position) *
		Matrix4x4::RotationZ(m_transform.rotation.z) *
		Matrix4x4::RotationY(m_transform.rotation.y) *
		Matrix4x4::RotationX(m_transform.rotation.x) *
		Matrix4x4::Scaling(m_transform.scale);

	oglRenderingRule->SetUniform("u_model", model);
}

Transform3D& OGLTransform3DParameter::Transform()
{
	return m_transform;
}
