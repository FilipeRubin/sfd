#pragma once
#include "i-renderer-managed.h"
#include <rendering/i-lambert-rendering-rule.h>

class OGLLambertRenderingRule : public ILambertRenderingRule, public IRendererManaged
{
public:
	void Bind() const override;
	void SetModel(const Matrix4x4& model) override;
	void SetView(const Matrix4x4& view) override;
	void SetProjection(const Matrix4x4& projection) override;
	void SetTexture(ITexture2D* texture) override;
	void Create() override;
	void Destroy() override;
private:
	unsigned int m_program;
	int m_modelUniform;
	int m_viewUniform;
	int m_projectionUniform;
};
