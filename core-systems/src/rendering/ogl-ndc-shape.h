#pragma once
#include <rendering/i-ndc-shape.h>

class OGLNDCShape : public INDCShape
{
public:
	OGLNDCShape(float* vertices, size_t length);
	~OGLNDCShape();
	void Draw() override;
private:
	unsigned int m_vbo;
	unsigned int m_vao;
	unsigned int m_verticeCount;
};