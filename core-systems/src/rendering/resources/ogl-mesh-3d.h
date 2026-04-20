#pragma once
#include <rendering/resources/i-mesh-3d.h>
#include <rendering/i-renderer-managed.h>
#include <types/vertex-3d.h>

class OGLMesh3D : public IMesh3D, public IRendererManaged
{
public:
	OGLMesh3D(const Vertex3D* vertices, size_t verticesCount, const unsigned int* indices, size_t indicesCount);
	void Draw() override;
	void Create() override;
	void Destroy() override;
private:
	unsigned int m_vbo;
	unsigned int m_vao;
	unsigned int m_ebo;
	unsigned int m_indicesCount;

	Vertex3D* m_cachedVertices;
	size_t m_cachedVerticesSize;
	unsigned int* m_cachedIndices;
	size_t m_cachedIndicesSize;

	void ClearCachedData();
};
