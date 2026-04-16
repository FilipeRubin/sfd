#pragma once
#include <rendering/i-mesh-3d.h>
#include "i-renderer-managed.h"

class OGLMesh3D : public IMesh3D, public IRendererManaged
{
public:
	OGLMesh3D(const float* vertices, size_t verticesSize, const unsigned int* indices, size_t indicesSize);
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
