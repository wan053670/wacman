#version 450 core
/* Input attributes */
layout(location = 0) in vec2 vs_uv;
layout(location = 1) in vec3 vs_col;

/* Uniforms */
layout(location = 0) uniform sampler2D sprite;

/* Output attributes */
layout(location = 0) out vec4 fs_color;

void main()
{
    fs_color = vec4(vs_col, 1.) * texture(sprite, vs_uv);
}