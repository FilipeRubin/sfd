#pragma once
#include <rendering/i-drawable.h>

class OGLNDCMesh : public IDrawable
{
public:
	OGLNDCMesh(float* data, size_t dataLength);
	~OGLNDCMesh();
	void Draw() const override;
private:
	unsigned int m_vbo;
	unsigned int m_vao;
};
