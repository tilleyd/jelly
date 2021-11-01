#version 330

in vec3 o_Position;
in vec3 o_Normal;
in vec2 o_UV;

uniform sampler2D u_TexDiffuse;

out vec4 o_Color;

void main() {
    o_Color = texture(u_TexDiffuse, o_UV);
}
