#pragma once
#include "i-renderer-managed.h"
#include <rendering/i-basic-3d-rendering-rule.h>

class OGLBasic3DRenderingRule : public IBasic3DRenderingRule, public IRendererManaged
{
public:
	OGLBasic3DRenderingRule();
	void Bind() const override;
	void SetProjection(const Matrix4x4& projection) override;
	void SetModel(const Matrix4x4& model) override;
	void Create() override;
	void Destroy() override;
private:
	unsigned int m_program;
	int m_projectionUniform;
	int m_modelUniform;
};