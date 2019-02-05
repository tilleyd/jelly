#version 330 core

layout(location = 0) in vec3 vertexPosition;

uniform mat4 mMatrix;
uniform mat4 pMatrix;

void main()
{
    gl_Position = pMatrix * mMatrix * vec4(vertexPosition, 1.0);
}
