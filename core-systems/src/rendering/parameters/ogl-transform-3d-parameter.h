#pragma once
#include <rendering/parameters/i-transform-3d-parameter.h>

class OGLTransform3DParameter : public ITransform3DParameter
{
public:
	void Bind(IRenderingRule* renderingRule) override;
	Transform3D& Transform() override;
private:
	Transform3D m_transform;
};
