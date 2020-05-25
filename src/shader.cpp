#include <geli/shader.hpp>

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <streambuf>

#include <GL/glew.h>

using namespace geli;

Shader::Shader() :
    _shader(0),
    _vShader(0),
    _fShader(0)
{}

Shader::~Shader()
{
    if (_shader) {
        glDeleteProgram(_shader);
    }
}

void Shader::add_vertex_shader(const std::string& glsl)
{
    _vShader = _compile_shader(glsl.c_str(), GL_VERTEX_SHADER);
}

void Shader::add_vertex_shader_file(const std::string& fp)
{
    std::ifstream file(fp);
    if (file.good()) {
        std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        add_vertex_shader(contents);
        file.close();
    } else {
        throw std::runtime_error("could not open '" + fp + "'");
    }
}

void Shader::add_fragment_shader(const std::string& glsl)
{
    _fShader = _compile_shader(glsl.c_str(), GL_FRAGMENT_SHADER);
}

void Shader::add_fragment_shader_file(const std::string& fp)
{
    std::ifstream file(fp);
    if (file.good()) {
        std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        add_fragment_shader(contents);
        file.close();
    } else {
        throw std::runtime_error("could not open '" + fp + "'");
    }
}

void Shader::link_shaders()
{
    _shader = _link_program(_vShader, _fShader);
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
        int h = glGetUniformLocation(_shader, u.c_str());
        if (h < 0) {
            std::cerr << "Warning: uniform " << u << " not found" << std::endl;
        }
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

void Shader::set_uniform(const std::string& u, float f)
{
    set_uniform(get_uniform_handle(u), f);
}

void Shader::set_uniform(unsigned int u, float f)
{
    glUniform1f(u, f);
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

void Shader::set_uniform(const std::string& u, const Mat3f& m)
{
    set_uniform(get_uniform_handle(u), m);
}

void Shader::set_uniform(unsigned int u, const Mat3f& m)
{
    glUniformMatrix3fv(u, 1, GL_FALSE, m.data());
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
        char log[512] = {};
        glGetProgramInfoLog(program, 512, NULL, log);
        std::cerr << "==========================" << std::endl;
        std::cerr << "GLSL Shader linking failed" << std::endl << log;
        std::cerr << "==========================" << std::endl;
        glDeleteProgram(program);
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
        char log[512] = {};
        glGetShaderInfoLog(shader, 512, NULL, log);
        std::cerr << "==============================" << std::endl;
        std::cerr << "GLSL Shader compilation failed" << std::endl << log;
        std::cerr << "==============================" << std::endl;
        glDeleteShader(shader);
        throw std::runtime_error("failed to compile shader");
    }
    return shader;
}
