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
	size_t GetVerticesCount() const;
	const unsigned int* GetIndices() const;
	size_t GetIndicesCount() const;
private:
	Vertex3D* m_vertices;
	size_t m_verticesCount;
	unsigned int* m_indices;
	size_t m_indicesCount;
};
