#pragma once
#include <rendering/i-ndc-rendering-rule.h>

class OGLNCDRenderingRule final : public INDCRenderingRule
{
public:
	OGLNCDRenderingRule();
	~OGLNCDRenderingRule();
	void SetColor(float r, float g, float b) override;
	void Bind() const override;
private:
	unsigned int m_program;
	int m_colorUniform;

	// PROVISORY - FOR TESTS ONLY
	unsigned int m_vbo;
	unsigned int m_vao;
};