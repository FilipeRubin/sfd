#include <containers/mesh-data.h>
#include <cstring>

MeshData::MeshData() :
	m_vertices(nullptr),
	m_verticeCount(0ULL),
	m_indices(nullptr),
	m_indiceCount(0ULL)
{
}

MeshData::MeshData(MeshData&& other) noexcept :
	m_vertices(other.m_vertices),
	m_verticeCount(other.m_verticeCount),
	m_indices(other.m_indices),
	m_indiceCount(other.m_indiceCount)
{
	other.m_vertices = nullptr;
	other.m_verticeCount = 0ULL;
	other.m_indices = nullptr;
	other.m_indiceCount = 0ULL;
}

MeshData& MeshData::operator=(MeshData&& other) noexcept
{
	if (&other != this)
	{
		delete[] m_vertices;
		delete[] m_indices;

		m_vertices = other.m_vertices;
		m_verticeCount = other.m_verticeCount;
		m_indices = other.m_indices;
		m_indiceCount = other.m_indiceCount;

		other.m_vertices = nullptr;
		other.m_verticeCount = 0ULL;
		other.m_indices = nullptr;
		other.m_indiceCount = 0ULL;
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
	m_verticeCount = count;
}

void MeshData::SetIndices(const unsigned int* indices, size_t count)
{
	delete[] m_indices;

	m_indices = new unsigned int[count];
	std::memcpy(m_indices, indices, count * sizeof(unsigned int));
	m_indiceCount = count;
}

const Vertex3D* MeshData::GetVertices() const
{
	return m_vertices;
}

size_t MeshData::GetVerticeCount() const
{
	return m_verticeCount;
}

const unsigned int* MeshData::GetIndices() const
{
	return m_indices;
}

size_t MeshData::GetIndiceCount() const
{
	return m_indiceCount;
}
