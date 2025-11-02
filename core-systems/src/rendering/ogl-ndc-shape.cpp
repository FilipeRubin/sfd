#include "ogl-ndc-shape.h"
#include <ogl.h>

OGLNDCShape::OGLNDCShape(float* vertices, size_t length) :
	m_vbo(0U),
	m_vao(0U),
	m_verticeCount(0U)
{
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, length, vertices, GL_STATIC_DRAW);
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glVertexAttribPointer(0U, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
	glEnableVertexAttribArray(0U);

	m_verticeCount = length / (sizeof(float) * 2);
}

OGLNDCShape::~OGLNDCShape()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
}

void OGLNDCShape::Draw()
{
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, m_verticeCount);
}
