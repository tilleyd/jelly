#include <jelly/gl/shader.hpp>

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <streambuf>

#include <GL/glew.h>

#include <jelly/gl/context.hpp>

namespace {


/**
 * Compiles the given GLSL code as the specified type of shader.
 *
 * \param glsl
 *     Shader source code.
 * \param type
 *     The shader type constant.
 *
 * \return
 *     A handle to the compiled shader.
 *
 * \throws
 *     std::runtime_error if compilation failed.
 */
unsigned int compile_shader(const char* glsl, unsigned int type) {
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


/**
 * Links the vertex and fragment shaders.
 *
 * \param v
 *     A handle to the compiled vertex shader.
 * \param f
 *     A handle to the compiled fragment shader.
 *
 * \return
 *     A handle to the linked shader program.
 *
 * \throws
 *     std::runtime_error if linking failed.
 */
unsigned int link_program(unsigned int vert, unsigned int frag) {
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


}


namespace jelly {


Shader::Shader(const std::string& vs, const std::string& fs) {
    _vertexShaderHandle = compile_shader(vs.c_str(), GL_VERTEX_SHADER);
    _fragmentShaderHandle = compile_shader(fs.c_str(), GL_FRAGMENT_SHADER);
    _programHandle = link_program(_vertexShaderHandle, _fragmentShaderHandle);

    _activeContext = nullptr;
}


Shader::~Shader() {
    if (_programHandle) {
        glDeleteProgram(_programHandle);
    }
}


unsigned int Shader::get_uniform_handle(const std::string& u) {
    try {
        return _uniformNameMap.at(u);
    } catch (...) {
        // not cached yet, find it
        int h = glGetUniformLocation(_programHandle, u.c_str());
        if (h < 0) {
            std::cerr << "Warning: uniform " << u << " not found" << std::endl;
        }
        _uniformNameMap[u] = h;
        return h;
    }
}


void Shader::set_uniform_int(const std::string& u, int i) {
    set_uniform_int(get_uniform_handle(u), i);
}


void Shader::set_uniform_int(unsigned int u, int i) {
    _intUniformCache[u] = i;
    if (is_active()) {
        glUniform1i(u, i);
    }
}


void Shader::set_uniform_float(const std::string& u, float f) {
    set_uniform_float(get_uniform_handle(u), f);
}


void Shader::set_uniform_float(unsigned int u, float f) {
    _floatUniformCache[u] = f;
    if (is_active()) {
        glUniform1f(u, f);
    }
}


void Shader::set_uniform_vec2(const std::string& u, const Vec2& v) {
    set_uniform_vec2(get_uniform_handle(u), v);
}


void Shader::set_uniform_vec2(unsigned int u, const Vec2& v) {
    _vec2UniformCache[u] = v;
    if (is_active()) {
        glUniform2fv(u, 1, v.data());
    }
}


void Shader::set_uniform_vec3(const std::string& u, const Vec3& v) {
    set_uniform_vec3(get_uniform_handle(u), v);
}


void Shader::set_uniform_vec3(unsigned int u, const Vec3& v) {
    _vec3UniformCache[u] = v;
    if (is_active()) {
        glUniform3fv(u, 1, v.data());
    }
}


void Shader::set_uniform_vec4(const std::string& u, const Vec4& v) {
    set_uniform_vec4(get_uniform_handle(u), v);
}


void Shader::set_uniform_vec4(unsigned int u, const Vec4& v) {
    _vec4UniformCache[u] = v;
    if (is_active()) {
        glUniform4fv(u, 1, v.data());
    }
}


void Shader::set_uniform_mat3(const std::string& u, const Mat3& m) {
    set_uniform_mat3(get_uniform_handle(u), m);
}


void Shader::set_uniform_mat3(unsigned int u, const Mat3& m) {
    _mat3UniformCache[u] = m;
    if (is_active()) {
        glUniformMatrix3fv(u, 1, GL_FALSE, m.data());
    }
}


void Shader::set_uniform_mat4(const std::string& u, const Mat4& m) {
    set_uniform_mat4(get_uniform_handle(u), m);
}


void Shader::set_uniform_mat4(unsigned int u, const Mat4& m) {
    _mat4UniformCache[u] = m;
    if (is_active()) {
        glUniformMatrix4fv(u, 1, GL_FALSE, m.data());
    }
}


void Shader::set_uniform_sampler(const std::string& u, const Texture& tex) {
    set_uniform_sampler(get_uniform_handle(u), tex);
}


void Shader::set_uniform_sampler(unsigned int u, const Texture& tex) {
    _samplerUniformCache[u] = &tex;

    if (is_active()) {
        unsigned int bindIndex;
        try {
            bindIndex = _samplerBindingLocations.at(u);
        } catch (...) {
            bindIndex = _samplerUniformCache.size() - 1;
            _samplerBindingLocations[u] = bindIndex;
        }
        _activeContext->bind_texture(tex, bindIndex);
        glUniform1i(u, bindIndex);
    }
}


void Shader::_activate(Context* c) {
    glUseProgram(_programHandle);
    _activeContext = c;

    // Apply the shader uniforms
    for (auto& pair : _intUniformCache) {
        glUniform1i(pair.first, pair.second);
    }
    for (auto& pair : _floatUniformCache) {
        glUniform1f(pair.first, pair.second);
    }
    for (auto& pair : _vec2UniformCache) {
        glUniform2fv(pair.first, 1, pair.second.data());
    }
    for (auto& pair : _vec3UniformCache) {
        glUniform3fv(pair.first, 1, pair.second.data());
    }
    for (auto& pair : _vec4UniformCache) {
        glUniform4fv(pair.first, 1, pair.second.data());
    }
    for (auto& pair : _mat3UniformCache) {
        glUniformMatrix3fv(pair.first, 1, GL_FALSE, pair.second.data());
    }
    for (auto& pair : _mat4UniformCache) {
        glUniformMatrix4fv(pair.first, 1, GL_FALSE, pair.second.data());
    }

    unsigned int i = 0;
    for (auto& pair : _samplerUniformCache) {
        c->bind_texture(*pair.second, i);
        glUniform1i(pair.first, i);
        _samplerBindingLocations[pair.first] = i;
        i += 1;
    }
}


void Shader::_deactivate() {
    _activeContext = nullptr;
}


}
