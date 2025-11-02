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

OGLNDCRenderingRule::OGLNDCRenderingRule() :
	m_program(0U),
	m_colorUniform(0)
{
}

void OGLNDCRenderingRule::Create()
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
}

void OGLNDCRenderingRule::Destroy()
{
	glDeleteProgram(m_program);
	m_program = 0U;
	m_colorUniform = 0;
}

void OGLNDCRenderingRule::SetColor(float r, float g, float b)
{
	glUniform3f(m_colorUniform, r, g, b);
}

void OGLNDCRenderingRule::Bind() const
{
	glUseProgram(m_program);
}
