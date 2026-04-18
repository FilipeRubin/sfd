static const char* redVertexShaderSource = R"(
#version 460 core

layout(location=0) in vec3 v_in_pos;
layout(location=1) in vec3 v_in_nor;
layout(location=2) in vec2 v_in_uv;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
	gl_Position = u_projection * u_view * u_model * vec4(v_in_pos, 1.0);
}
)";

static const char* redFragmentShaderSource = R"(
#version 460 core

out vec4 f_color;

void main()
{
	f_color = vec4(1.0, 0.0, 0.0, 1.0);
}
)";
