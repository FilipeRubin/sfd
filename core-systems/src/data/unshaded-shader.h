static const char* unshadedVertexShaderSource = R"(
#version 460 core

layout(location=0) in vec3 v_in_pos;
layout(location=1) in vec3 v_in_nor;
layout(location=2) in vec2 v_in_uv;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec2 v_out_uv;

void main()
{
	v_out_uv = v_in_uv;
	gl_Position = u_projection * u_view * u_model * vec4(v_in_pos, 1.0);
}
)";

static const char* unshadedFragmentShaderSource = R"(
#version 460 core

in vec2 v_out_uv;

out vec4 f_color;

uniform sampler2D u_texture;

void main()
{
	f_color = texture(u_texture, v_out_uv);
}
)";
