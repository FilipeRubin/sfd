#include <containers/mesh-data.h>
#include <cstring>

MeshData::MeshData() :
	m_vertices(nullptr),
	m_indices(nullptr)
{
}

MeshData::MeshData(MeshData&& other) noexcept :
	m_vertices(std::move(other.m_vertices)),
	m_indices(std::move(other.m_indices))
{
}

MeshData& MeshData::operator=(MeshData&& other) noexcept
{
	if (&other != this)
	{
		m_vertices = std::move(other.m_vertices);
		m_indices = std::move(other.m_indices);
	}

	return *this;
}

void MeshData::SetVertices(Shared<FixedArray<Vertex3D>> vertices)
{
	m_vertices = vertices;
}

void MeshData::SetIndices(Shared<FixedArray<unsigned int>> indices)
{
	m_indices = indices;
}

Shared<FixedArray<Vertex3D>> MeshData::GetVertices() const
{
	return m_vertices;
}

Shared<FixedArray<unsigned int>> MeshData::GetIndices() const
{
	return m_indices;
}
