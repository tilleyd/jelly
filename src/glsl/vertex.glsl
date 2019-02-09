#version 330 core

layout(location = 0) in vec3 a_vertexPosition;

//uniform mat4 mMatrix;
//uniform mat4 pMatrix;

void main()
{
    //gl_Position = pMatrix * mMatrix * vec4(a_vertexPosition, 1.0);
    gl_Position = vec4(a_vertexPosition, 1.0);
}
