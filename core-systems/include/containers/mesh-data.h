#pragma once
#include "fixed-array.h"
#include <types/vertex-3d.h>
#include <utils/shared.h>

class MeshData final
{
public:
	MeshData();
	MeshData(const MeshData& other) = delete;
	MeshData(MeshData&& other) noexcept;
	MeshData& operator=(const MeshData& other) = delete;
	MeshData& operator=(MeshData&& other) noexcept;
	void SetVertices(Shared<FixedArray<Vertex3D>> vertices);
	void SetIndices(Shared<FixedArray<unsigned int>> indices);
	Shared<FixedArray<Vertex3D>> GetVertices() const;
	Shared<FixedArray<unsigned int>> GetIndices() const;
private:
	Shared<FixedArray<Vertex3D>> m_vertices;
	Shared<FixedArray<unsigned int>> m_indices;
};
