#include <geli/shader.hpp>

#include <stdexcept>

#include <GL/glew.h>

using namespace geli;

Shader::Shader(const std::string& vs, const std::string& fs) :
    _shader(0)
{
    // compile the shaders
    GLuint vert = _compile_shader(vs.c_str(), GL_VERTEX_SHADER);
    GLuint frag = _compile_shader(fs.c_str(), GL_FRAGMENT_SHADER);
    // and link
    _shader = _link_program(vert, frag);
}

Shader::~Shader()
{
    if (_shader) {
        glDeleteProgram(_shader);
    }
}

void Shader::use() const
{
    glUseProgram(_shader);
}

unsigned int Shader::get_uniform_handle(const std::string& u)
{
    try {
        return _uniformCache.at(u);
    } catch (...) {
        // not cached yet, find it
        unsigned int h = glGetUniformLocation(_shader, u.c_str());
        _uniformCache[u] = h;
        return h;
    }
}

void Shader::set_uniform(const std::string& u, int i)
{
    set_uniform(get_uniform_handle(u), i);
}

void Shader::set_uniform(unsigned int u, int i)
{
    glUniform1i(u, i);
}

void Shader::set_uniform(const std::string& u, const Vec2f& v)
{
    set_uniform(get_uniform_handle(u), v);
}

void Shader::set_uniform(unsigned int u, const Vec2f& v)
{
    glUniform2fv(u, 1, v.data());
}

void Shader::set_uniform(const std::string& u, const Vec3f& v)
{
    set_uniform(get_uniform_handle(u), v);
}

void Shader::set_uniform(unsigned int u, const Vec3f& v)
{
    glUniform3fv(u, 1, v.data());
}

void Shader::set_uniform(const std::string& u, const Mat4f& m)
{
    set_uniform(get_uniform_handle(u), m);
}

void Shader::set_uniform(unsigned int u, const Mat4f& m)
{
    glUniformMatrix4fv(u, 1, GL_FALSE, m.data());
}

unsigned int Shader::_link_program(unsigned int vert, unsigned int frag)
{
    GLuint program = glCreateProgram();
    // link the program and get the result
    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);
    GLint result = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &result);

    // clean up the shaders before possibly throwing an exception
    glDetachShader(program, vert);
    glDetachShader(program, frag);
    glDeleteShader(vert);
    glDeleteShader(frag);

    if (result == GL_FALSE) {
        throw std::runtime_error("failed to link vertex and fragment shaders");
    }
    return program;
}

unsigned int Shader::_compile_shader(const char* glsl, unsigned int type)
{
    GLuint shader = glCreateShader(type);
    // compile the shader
    glShaderSource(shader, 1, &glsl, nullptr);
    glCompileShader(shader);
    // check the results
    GLint result = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        glDeleteShader(shader);
        throw std::runtime_error("failed to compile shader");
    }
    return shader;
}
