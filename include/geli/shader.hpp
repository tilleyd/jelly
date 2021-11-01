#ifndef _GELI_SHADER_HPP_
#define _GELI_SHADER_HPP_

#include <string>
#include <map>
#include <memory>

#include <geli/math.hpp>
#include <geli/texture.hpp>

namespace geli {

class Context;

/**
 * Allows creation and use of a GLSL shader program.
 *
 * \warn
 *     The window must be created before attempting to create a Shader.
 */
class Shader {

public:

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;
    Shader() = delete;

    /**
     * Creates a shader from the given GLSL vertex and fragment shader code.
     *
     * \param vs
     *     The complete vertex shader code.
     * \param fs
     *     The complete fragment shader code.
     *
     * \throw std::runtime_error if the shader compilation failed.
     */
    Shader(const std::string& vs, const std::string& fs);

    /**
     * Clears all resources used by the shader.
     */
    ~Shader();

    /**
     * Returns the handle to the uniform.
     *
     * \param u
     *     The name of the shader uniform.
     */
    unsigned int get_uniform_handle(const std::string& u);

    void set_uniform_int(const std::string& u, int);

    void set_uniform_int(unsigned int u, int);

    void set_uniform_float(const std::string& u, float);

    void set_uniform_float(unsigned int u, float);

    void set_uniform_vec2(const std::string& u, const Vec2&);

    void set_uniform_vec2(unsigned int u, const Vec2&);

    void set_uniform_vec3(const std::string& u, const Vec3&);

    void set_uniform_vec3(unsigned int u, const Vec3&);

    void set_uniform_vec4(const std::string& u, const Vec4&);

    void set_uniform_vec4(unsigned int u, const Vec4&);

    void set_uniform_mat3(const std::string& u, const Mat3&);

    void set_uniform_mat3(unsigned int u, const Mat3&);

    void set_uniform_mat4(const std::string& u, const Mat4&);

    void set_uniform_mat4(unsigned int u, const Mat4&);

    void set_uniform_sampler(const std::string& u, const Texture*);

    void set_uniform_sampler(unsigned int u, const Texture*);

    bool is_active() const {
        return _activeContext != nullptr;
    }

    /**
     * Returns a handle to the OpenGL shader program.
     */
    unsigned int get_gl_handle() const {
        return _programHandle;
    }

private:

    friend class Context;

    void _activate(Context*);
    void _deactivate();

    unsigned int _programHandle, _vertexShaderHandle, _fragmentShaderHandle;
    std::map<std::string, unsigned int> _uniformNameMap;

    std::map<unsigned int, int> _intUniformCache;
    std::map<unsigned int, float> _floatUniformCache;
    std::map<unsigned int, Vec2> _vec2UniformCache;
    std::map<unsigned int, Vec3> _vec3UniformCache;
    std::map<unsigned int, Vec4> _vec4UniformCache;
    std::map<unsigned int, Mat3> _mat3UniformCache;
    std::map<unsigned int, Mat4> _mat4UniformCache;
    std::map<unsigned int, const Texture*> _samplerUniformCache;

    Context* _activeContext;

};

};

#endif
