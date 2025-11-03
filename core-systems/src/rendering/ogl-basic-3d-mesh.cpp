#include "ogl-basic-3d-mesh.h"
#include <ogl.h>
#include <cstring>

OGLBasic3DMesh::OGLBasic3DMesh(const float* vertices, size_t verticesSize, const unsigned int* indices, size_t indicesSize) :
	m_vbo(0U), m_vao(0U), m_ebo(0U),
	m_indicesCount(0U),
	m_cachedVertices(nullptr), m_cachedVerticesSize(0ULL),
	m_cachedIndices(nullptr), m_cachedIndicesSize(0ULL)
{
	m_cachedVertices = new float[verticesSize];
	m_cachedIndices = new unsigned int[indicesSize];

	std::memcpy(m_cachedVertices, vertices, verticesSize);
	std::memcpy(m_cachedIndices, indices, indicesSize);

	m_cachedVerticesSize = verticesSize;
	m_cachedIndicesSize = indicesSize;

	m_indicesCount = indicesSize / sizeof(unsigned int);
}

void OGLBasic3DMesh::Draw()
{
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, NULL);
}

void OGLBasic3DMesh::Create()
{
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_cachedVerticesSize, m_cachedVertices, GL_STATIC_DRAW);
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glVertexAttribPointer(0U, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
	glVertexAttribPointer(1U, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(0U);
	glEnableVertexAttribArray(1U);
	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_cachedIndicesSize, m_cachedIndices, GL_STATIC_DRAW);

	ClearCachedData();
}

void OGLBasic3DMesh::Destroy()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_ebo);

	m_indicesCount = 0U;

	ClearCachedData();
}

void OGLBasic3DMesh::ClearCachedData()
{
	delete[] m_cachedVertices;
	delete[] m_cachedIndices;
	m_cachedVertices = nullptr;
	m_cachedIndices = nullptr;
	m_cachedVerticesSize = 0ULL;
	m_cachedIndicesSize = 0ULL;
}
