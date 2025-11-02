#pragma once
#include <rendering/i-ndc-rendering-rule.h>

class OGLNDCRenderingRule final : public INDCRenderingRule
{
public:
	OGLNDCRenderingRule();
	~OGLNDCRenderingRule();
	void SetColor(float r, float g, float b) override;
	void Bind() const override;
private:
	unsigned int m_program;
	int m_colorUniform;
};