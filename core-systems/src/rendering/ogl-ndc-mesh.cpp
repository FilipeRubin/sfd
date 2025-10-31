#include "ogl-ndc-mesh.h"
#include <ogl.h>

OGLNDCMesh::OGLNDCMesh(float* data, size_t dataLength) :
	m_vbo(0U),
	m_vao(0U)
{
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, dataLength, data, GL_STATIC_DRAW);
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glVertexAttribPointer(0U, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const GLvoid*)0);
	glEnableVertexAttribArray(0U);
}

OGLNDCMesh::~OGLNDCMesh()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
}

void OGLNDCMesh::Draw() const
{
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
