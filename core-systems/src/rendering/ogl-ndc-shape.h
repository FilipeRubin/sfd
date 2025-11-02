#pragma once
#include <rendering/i-ndc-shape.h>
#include <rendering/i-renderer-managed.h>

class OGLNDCShape : public INDCShape, public IRendererManaged
{
public:
	OGLNDCShape(float* vertices, size_t length);
	void Create() override;
	void Destroy() override;
	void Draw() override;
private:
	unsigned int m_vbo;
	unsigned int m_vao;
	unsigned int m_verticeCount;
	
	float* m_cachedVertices;
	size_t m_cachedLength;
};