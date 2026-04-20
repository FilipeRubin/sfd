#include "ogl-mesh-3d.h"
#include <ogl.h>
#include <cstring>

OGLMesh3D::OGLMesh3D(const Vertex3D* vertices, size_t verticesCount, const unsigned int* indices, size_t indicesCount) :
	m_vbo(0U), m_vao(0U), m_ebo(0U),
	m_indicesCount(0U),
	m_cachedVertices(nullptr), m_cachedVerticesSize(0ULL),
	m_cachedIndices(nullptr), m_cachedIndicesSize(0ULL)
{
	m_cachedVertices = new Vertex3D[verticesCount];
	m_cachedIndices = new unsigned int[indicesCount];

	m_cachedVerticesSize = verticesCount * sizeof(Vertex3D);
	m_cachedIndicesSize = indicesCount * sizeof(unsigned int);

	std::memcpy(m_cachedVertices, vertices, m_cachedVerticesSize);
	std::memcpy(m_cachedIndices, indices, m_cachedIndicesSize);

	m_indicesCount = indicesCount;
}

void OGLMesh3D::Draw()
{
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, NULL);
}

void OGLMesh3D::Create()
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_cachedVerticesSize, m_cachedVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0U, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
	glVertexAttribPointer(1U, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)12);
	glVertexAttribPointer(2U, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)24);
	glEnableVertexAttribArray(0U);
	glEnableVertexAttribArray(1U);
	glEnableVertexAttribArray(2U);

	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_cachedIndicesSize, m_cachedIndices, GL_STATIC_DRAW);

	ClearCachedData();
}

void OGLMesh3D::Destroy()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_ebo);

	m_indicesCount = 0U;

	ClearCachedData();
}

void OGLMesh3D::ClearCachedData()
{
	delete[] m_cachedVertices;
	delete[] m_cachedIndices;
	m_cachedVertices = nullptr;
	m_cachedIndices = nullptr;
	m_cachedVerticesSize = 0ULL;
	m_cachedIndicesSize = 0ULL;
}
