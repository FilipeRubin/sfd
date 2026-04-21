#pragma once
#include <types/vertex-3d.h>

class MeshData final
{
public:
	MeshData();
	MeshData(const MeshData& other) = delete;
	MeshData(MeshData&& other) noexcept;
	MeshData& operator=(const MeshData& other) = delete;
	MeshData& operator=(MeshData&& other) noexcept;
	~MeshData();
	void SetVertices(const Vertex3D* vertices, size_t count);
	void SetIndices(const unsigned int* indices, size_t count);
	const Vertex3D* GetVertices() const;
	size_t GetVerticeCount() const;
	const unsigned int* GetIndices() const;
	size_t GetIndiceCount() const;
private:
	Vertex3D* m_vertices;
	size_t m_verticeCount;
	unsigned int* m_indices;
	size_t m_indiceCount;
};
