#version 330 core

layout(location = 0) in vec3 a_VertexPosition;

uniform mat4 u_MMatrix;
uniform mat4 u_VMatrix;
uniform mat4 u_PMatrix;

void main()
{
    vec4 WorldPosition = u_MMatrix * vec4(a_VertexPosition, 1.0);
    gl_Position = u_PMatrix * u_VMatrix * WorldPosition;
}
