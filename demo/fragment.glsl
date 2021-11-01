#version 330

in vec3 o_Position;
in vec3 o_Normal;
in vec2 o_UV;

out vec4 o_Color;

void main() {
    o_Color = vec4(o_UV, 0.5, 1);
}
