#include <containers/mesh-data.h>
#include <cstring>

MeshData::MeshData() :
	m_vertices(nullptr),
	m_verticesCount(0ULL),
	m_indices(nullptr),
	m_indicesCount(0ULL)
{
}

MeshData::MeshData(MeshData&& other) noexcept :
	m_vertices(other.m_vertices),
	m_verticesCount(other.m_verticesCount),
	m_indices(other.m_indices),
	m_indicesCount(other.m_indicesCount)
{
	if (&other != this)
	{
		delete[] m_vertices;
		delete[] m_indices;

		other.m_vertices = nullptr;
		other.m_verticesCount = 0ULL;
		other.m_indices = nullptr;
		other.m_indicesCount = 0ULL;
	}
}

MeshData& MeshData::operator=(MeshData&& other) noexcept
{
	if (&other != this)
	{
		delete[] m_vertices;
		delete[] m_indices;

		m_vertices = other.m_vertices;
		m_verticesCount = other.m_verticesCount;
		m_indices = other.m_indices;
		m_indicesCount = other.m_indicesCount;

		other.m_vertices = nullptr;
		other.m_verticesCount = 0ULL;
		other.m_indices = nullptr;
		other.m_indicesCount = 0ULL;
	}

	return *this;
}

MeshData::~MeshData()
{
	delete[] m_vertices;
	delete[] m_indices;
}

void MeshData::SetVertices(const Vertex3D* vertices, size_t count)
{
	delete[] m_vertices;

	m_vertices = new Vertex3D[count];
	std::memcpy(m_vertices, vertices, count * sizeof(Vertex3D));
	m_verticesCount = count;
}

void MeshData::SetIndices(const unsigned int* indices, size_t count)
{
	delete[] m_indices;

	m_indices = new unsigned int[count];
	std::memcpy(m_indices, indices, count * sizeof(unsigned int));
	m_indicesCount = count;
}

const Vertex3D* MeshData::GetVertices() const
{
	return m_vertices;
}

size_t MeshData::GetVerticesCount() const
{
	return m_verticesCount;
}

const unsigned int* MeshData::GetIndices() const
{
	return m_indices;
}

size_t MeshData::GetIndicesCount() const
{
	return m_indicesCount;
}
