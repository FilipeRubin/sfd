#pragma once
#include <rendering/i-basic-3d-mesh.h>
#include "i-renderer-managed.h"

class OGLBasic3DMesh : public IBasic3DMesh, public IRendererManaged
{
public:
	OGLBasic3DMesh(const float* vertices, size_t verticesSize, const unsigned int* indices, size_t indicesSize);
	void Draw() override;
	void Create() override;
	void Destroy() override;
private:
	unsigned int m_vbo;
	unsigned int m_vao;
	unsigned int m_ebo;
	unsigned int m_indicesCount;

	float* m_cachedVertices;
	size_t m_cachedVerticesSize;
	unsigned int* m_cachedIndices;
	size_t m_cachedIndicesSize;

	void ClearCachedData();
};
