#pragma once
#include "i-bindable.h"
#include "i-renderer-managed.h"
#include <rendering/i-lambert-rendering-rule.h>

class OGLLambertRenderingRule : public ILambertRenderingRule, public IBindable, public IRendererManaged
{
public:
	void SetAmbientLight(const Color& color) override;
	void SetModel(const Matrix4x4& model) override;
	void SetView(const Matrix4x4& view) override;
	void SetProjection(const Matrix4x4& projection) override;
	void SetTexture(ITexture2D* texture) override;
	void Bind() const override;
	void Create() override;
	void Destroy() override;
private:
	unsigned int m_program;
	int m_ambientLightUniform;
	int m_modelUniform;
	int m_viewUniform;
	int m_projectionUniform;
};
