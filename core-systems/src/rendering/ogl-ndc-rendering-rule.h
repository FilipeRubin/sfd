#pragma once
#include <rendering/i-ndc-rendering-rule.h>
#include <rendering/i-renderer-managed.h>

class OGLNDCRenderingRule final : public INDCRenderingRule, public IRendererManaged
{
public:
	OGLNDCRenderingRule();
	void Create() override;
	void Destroy() override;
	void SetColor(float r, float g, float b) override;
	void Bind() const override;
private:
	unsigned int m_program;
	int m_colorUniform;
};