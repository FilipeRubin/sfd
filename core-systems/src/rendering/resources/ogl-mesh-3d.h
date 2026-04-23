#pragma once
#include <containers/fixed-array.h>
#include <rendering/resources/i-mesh-3d.h>
#include <rendering/i-renderer-managed.h>
#include <types/vertex-3d.h>
#include <utils/shared.h>

class OGLMesh3D : public IMesh3D, public IRendererManaged
{
public:
	OGLMesh3D(Shared<FixedArray<Vertex3D>> vertices, Shared<FixedArray<unsigned int>> indices);
	void Draw() override;
	void Create() override;
	void Destroy() override;
private:
	unsigned int m_vbo;
	unsigned int m_vao;
	unsigned int m_ebo;
	unsigned int m_indicesCount;

	Shared<FixedArray<Vertex3D>> m_vertices;
	Shared<FixedArray<unsigned int>> m_indices;
};
