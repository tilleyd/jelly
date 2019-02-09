#include <geli/core/shader.h>

#include <geli/core/glsl.h>

using namespace geli::core;

Shader::Shader() :
    _shader(0)
{
    // create shader program
    GLuint vert = compileShader(geli::core::SHADER_VERTEX,
                                GL_VERTEX_SHADER);
    GLuint frag = compileShader(geli::core::SHADER_FRAGMENT,
                                GL_FRAGMENT_SHADER);
    _shader = linkProgram(vert, frag);
    glUseProgram(_shader);

    // get shader uniforms
    _mMatrixUniform = glGetUniformLocation(_shader, "u_MMatrix");
    _vMatrixUniform = glGetUniformLocation(_shader, "u_VMatrix");
    _pMatrixUniform = glGetUniformLocation(_shader, "u_PMatrix");
}

Shader::~Shader()
{
    if (_shader) {
        glDeleteProgram(_shader);
    }
}

void Shader::setMMatrix(const glm::mat4& mm)
{
    glUniformMatrix4fv(_mMatrixUniform, 1, GL_FALSE, &mm[0][0]);
}

void Shader::setVMatrix(const glm::mat4& vm)
{
    glUniformMatrix4fv(_vMatrixUniform, 1, GL_FALSE, &vm[0][0]);
}

void Shader::setPMatrix(const glm::mat4& pm)
{
    glUniformMatrix4fv(_pMatrixUniform, 1, GL_FALSE, &pm[0][0]);
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
