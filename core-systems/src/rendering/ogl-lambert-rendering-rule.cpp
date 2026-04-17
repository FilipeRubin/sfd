#include "ogl-lambert-rendering-rule.h"
#include "ogl-texture-2d.h"
#include <ogl.h>
#include <types/color.h>

static const char* vertexShaderSource = R"(
#version 460 core

layout(location=0) in vec3 v_in_pos;
layout(location=1) in vec3 v_in_nor;
layout(location=2) in vec2 v_in_uv;

out vec2 v_out_uv;
out vec3 v_out_nor;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
	gl_Position = u_projection * u_view * u_model * vec4(v_in_pos, 1.0);
	v_out_uv = v_in_uv;
	v_out_nor = mat3(transpose(inverse(u_model))) * v_in_nor;
}
)";

static const char* fragmentShaderSource = R"(
#version 460 core

in vec2 v_out_uv;
in vec3 v_out_nor;

out vec4 f_color;

uniform sampler2D u_texture;
uniform vec4 u_ambientLight;
uniform vec4 u_directionalLightDiffuse;
uniform vec3 u_directionalLightDirection;

void main()
{
	float directionalLightAmount = max(dot(normalize(v_out_nor), normalize(-u_directionalLightDirection)), 0.0);
	vec3 directionalLightColor = u_directionalLightDiffuse.rgb * directionalLightAmount;
	vec3 lightColor = max(u_ambientLight.rgb, directionalLightColor);
	f_color = texture(u_texture, v_out_uv) * vec4(lightColor, 1.0);
}
)";

void OGLLambertRenderingRule::SetDirectionalLight(const DirectionalLight& directionalLight)
{
	glUniform4fv(m_ambientLightUniform, 1, reinterpret_cast<const GLfloat*>(&directionalLight.ambient));
	glUniform4fv(m_directionalLightDiffuseUniform, 1, reinterpret_cast<const GLfloat*>(&directionalLight.diffuse));
	glUniform3fv(m_directionalLightDirectionUniform, 1, reinterpret_cast<const GLfloat*>(&directionalLight.direction));
}

void OGLLambertRenderingRule::SetModel(const Matrix4x4& model)
{
	glUniformMatrix4fv(m_modelUniform, 1, GL_FALSE, model.Data());
}

void OGLLambertRenderingRule::SetView(const Matrix4x4& view)
{
	glUniformMatrix4fv(m_viewUniform, 1, GL_FALSE, view.Data());
}

void OGLLambertRenderingRule::SetProjection(const Matrix4x4& projection)
{
	glUniformMatrix4fv(m_projectionUniform, 1, GL_FALSE, projection.Data());
}

void OGLLambertRenderingRule::SetTexture(ITexture2D* texture)
{
	dynamic_cast<OGLTexture2D*>(texture)->Bind();
}

void OGLLambertRenderingRule::Bind() const
{
	glUseProgram(m_program);
}

void OGLLambertRenderingRule::Create()
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

	m_ambientLightUniform = glGetUniformLocation(m_program, "u_ambientLight");
	m_directionalLightDiffuseUniform = glGetUniformLocation(m_program, "u_directionalLightDiffuse");
	m_directionalLightDirectionUniform = glGetUniformLocation(m_program, "u_directionalLightDirection");
	m_modelUniform = glGetUniformLocation(m_program, "u_model");
	m_viewUniform = glGetUniformLocation(m_program, "u_view");
	m_projectionUniform = glGetUniformLocation(m_program, "u_projection");
}

void OGLLambertRenderingRule::Destroy()
{
	glDeleteProgram(m_program);

	m_program = 0U;
	m_ambientLightUniform = -1;
	m_directionalLightDiffuseUniform = -1;
	m_directionalLightDirectionUniform = -1;
	m_modelUniform = -1;
	m_viewUniform = -1;
	m_projectionUniform = -1;
}
