#version 330

layout (location = 0) in vec3 v_Position;
layout (location = 1) in vec3 v_Normal;
layout (location = 2) in vec2 v_UV;

out vec3 o_Normal;
out vec2 o_UV;

void main() {
    gl_Position = vec4(v_Position, 1.0);
    o_Normal = v_Normal;
    o_UV = v_UV;
}
