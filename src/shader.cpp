#include <geli/shader.h>

#include <geli/glsl.h>

using namespace geli;

Shader::Shader() :
    _shader(0)
{
    GLuint vert = compileShader(geli::SHADER_VERTEX, GL_VERTEX_SHADER);
    GLuint frag = compileShader(geli::SHADER_FRAGMENT, GL_FRAGMENT_SHADER);
    _shader = linkProgram(vert, frag);
    glUseProgram(_shader);
}

Shader::~Shader()
{
    if (_shader) {
        glDeleteProgram(_shader);
    }
}

GLuint Shader::linkProgram(GLuint vert, GLuint frag) const
{
    GLuint program = glCreateProgram();
    // link the program
    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);
    // check the results
    GLint result = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        throw "failed to link shaders";
    }
    glDetachShader(program, vert);
    glDetachShader(program, frag);
    glDeleteShader(vert);
    glDeleteShader(frag);
    return program;
}

GLuint Shader::compileShader(const char* glsl, GLenum type) const
{
    GLuint shader = glCreateShader(type);
    // compile the shader
    glShaderSource(shader, 1, &glsl, nullptr);
    glCompileShader(shader);
    // check the results
    GLint result = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        throw "failed to compile shader";
    }
    return shader;
}
