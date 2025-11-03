#include "ogl-basic-3d-rendering-rule.h"
#include <ogl.h>

static const char* vertexShaderSource = R"(
#version 460 core

layout(location=0) in vec3 v_in_pos;
layout(location=1) in vec3 v_in_col;

out vec3 v_out_col;

uniform mat4 u_projection;
uniform mat4 u_model;

void main()
{
	gl_Position = u_projection * u_model * vec4(v_in_pos, 1.0);
	v_out_col = v_in_col;
}
)";

static const char* fragmentShaderSource = R"(
#version 460 core

in vec3 v_out_col;

out vec4 f_color;

void main()
{
	f_color = vec4(v_out_col, 1.0);
}
)";

OGLBasic3DRenderingRule::OGLBasic3DRenderingRule() :
	m_program(0U),
	m_projectionUniform(0),
	m_modelUniform(0)
{
}

void OGLBasic3DRenderingRule::Bind() const
{
	glUseProgram(m_program);
}

void OGLBasic3DRenderingRule::SetProjection(const Matrix4x4& projection)
{
	glUniformMatrix4fv(m_projectionUniform, 1, GL_FALSE, projection.Data());
}

void OGLBasic3DRenderingRule::SetModel(const Matrix4x4& model)
{
	glUniformMatrix4fv(m_modelUniform, 1, GL_FALSE, model.Data());
}

void OGLBasic3DRenderingRule::Create()
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

	m_projectionUniform = glGetUniformLocation(m_program, "u_projection");
	m_modelUniform = glGetUniformLocation(m_program, "u_model");
}

void OGLBasic3DRenderingRule::Destroy()
{
	glDeleteProgram(m_program);

	m_program = 0U;
	m_projectionUniform = 0;
	m_modelUniform = 0;
}
