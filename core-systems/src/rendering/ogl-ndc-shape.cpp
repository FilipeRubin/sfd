#include "ogl-ndc-shape.h"
#include <ogl.h>
#include <cstring>

OGLNDCShape::OGLNDCShape(float* vertices, size_t length) :
	m_vbo(0U),
	m_vao(0U),
	m_verticeCount(0U),
	m_cachedVertices(nullptr),
	m_cachedLength(0U)
{
	m_cachedVertices = new float[length];
	std::memcpy(m_cachedVertices, vertices, length);
	m_cachedLength = length;
}

void OGLNDCShape::Create()
{
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_cachedLength, m_cachedVertices, GL_STATIC_DRAW);
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glVertexAttribPointer(0U, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
	glEnableVertexAttribArray(0U);

	m_verticeCount = unsigned int(m_cachedLength / (sizeof(float) * 2ULL));

	delete[] m_cachedVertices;
	m_cachedVertices = nullptr;
	m_cachedLength = 0U;
}

void OGLNDCShape::Destroy()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);

	delete[] m_cachedVertices;
	m_cachedVertices = nullptr;
	m_cachedLength = 0U;
}

void OGLNDCShape::Draw()
{
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, m_verticeCount);
}
