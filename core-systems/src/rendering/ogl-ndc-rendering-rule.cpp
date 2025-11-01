#include "ogl-ndc-rendering-rule.h"
#include <ogl.h>

static const char* vertexShaderSource =
R"(
#version 460 core

layout(location=0) in vec2 v_in_pos;

void main()
{
	gl_Position = vec4(v_in_pos, 0.0, 1.0);
}
)";

static const char* fragmentShaderSource =
R"(
#version 460 core

uniform vec3 u_color;

out vec4 f_color;

void main()
{
	f_color = vec4(u_color, 1.0);
}
)";

OGLNCDRenderingRule::OGLNCDRenderingRule() :
	m_program(0U),
	m_colorUniform(0),
	m_vbo(0U),
	m_vao(0U)
{
	m_program = glCreateProgram();
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vs, 1, &vertexShaderSource, nullptr);
	glShaderSource(fs, 1, &fragmentShaderSource, nullptr);
	glCompileShader(vs);
	glCompileShader(fs);
	glAttachShader(m_program, vs);
	glAttachShader(m_program, fs);
	glLinkProgram(m_program);
	glDeleteShader(vs);
	glDeleteShader(fs);

	m_colorUniform = glGetUniformLocation(m_program, "u_color");

	float triangle[] = {
		0.5f, -0.5f,
		0.0f, 0.5f,
		-0.5f, -0.5f
	};

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glVertexAttribPointer(0U, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2U, (void*)0);
	glEnableVertexAttribArray(0U);
}

OGLNCDRenderingRule::~OGLNCDRenderingRule()
{
	glDeleteProgram(m_program);
	m_program = 0U;
	m_colorUniform = 0;

	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
}

void OGLNCDRenderingRule::SetColor(float r, float g, float b)
{
	glUseProgram(m_program);
	glUniform3f(m_colorUniform, r, g, b);
}

void OGLNCDRenderingRule::Bind() const
{
	glUseProgram(m_program);

	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
