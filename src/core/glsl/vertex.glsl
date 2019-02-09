#version 330 core

layout(location = 0) in vec3 a_VertexPosition;

uniform mat4 u_VMatrix;
uniform mat4 u_PMatrix;

void main()
{
    gl_Position = u_PMatrix * u_VMatrix * vec4(a_VertexPosition, 1.0);
}
