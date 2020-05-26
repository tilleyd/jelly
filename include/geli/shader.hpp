#ifndef _GELI_SHADER_HPP_
#define _GELI_SHADER_HPP_

#include <string>
#include <map>
#include <memory>

#include <geli/math.hpp>
#include <geli/texture.hpp>

namespace geli
{

/**
 * Allows creation and use of a GLSL shader program.
 *
 * \warn
 *     The window must be created before attempting to create a Shader.
 */
class Shader
{

public:

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    /**
     * Creates and returns an instance of the predefined single-pass shader.
     */
    static std::shared_ptr<Shader> create_single_pass_shader();

    /**
     * Creates and returns an isntance of the predefined bloom shader.
     */
    static std::shared_ptr<Shader> create_bloom_shader();

    /**
     * Creates and returns an instance of the predefined final post-processing
     * shader.
     */
    static std::shared_ptr<Shader> create_post_shader();

    /**
     * Creates an empty shader.
     */
    Shader();

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
     * Compiles and attaches a vertex shader to this program.
     *
     * \param s
     *     The GLSL source code of the vertex shader.
     *
     * \throw std::runtime error if compilation failed.
     */
    void add_vertex_shader(const std::string& s);

    /**
     * Reads the vertex shader source code from a file and compiles and
     * attaches the shader to this program.
     *
     * \param fp
     *     The file path to a GLSL source file.
     *
     * \throw std::runtime_error if compilation failed or the file could not
     *     be read.
     */
    void add_vertex_shader_file(const std::string& fp);

    /**
     * Compiles and attaches a fragment shader to this program.
     *
     * \param s
     *     The GLSL source code of the fragment shader.
     *
     * \throw std::runtime error if compilation failed.
     */
    void add_fragment_shader(const std::string& s);

    /**
     * Reads the fragment shader source code from a file and compiles and
     * attaches the shader to this program.
     *
     * \param fp
     *     The file path to a GLSL source file.
     *
     * \throw std::runtime_error if compilation failed or the file could not
     *     be read.
     */
    void add_fragment_shader_file(const std::string& fp);

    /**
     * Links all added shaders. If successful, the shader program is ready
     * to use.
     */
    void link_shaders();

    /**
     * Sets the shader as the active shader.
     */
    void use() const;

    /**
     * Returns the handle to the uniform.
     *
     * \param u
     *     The name of the shader uniform.
     */
    unsigned int get_uniform_handle(const std::string& u);

    void set_uniform(const std::string& u, int);

    void set_uniform(unsigned int u, int);

    void set_uniform(const std::string& u, float);

    void set_uniform(unsigned int u, float);

    void set_uniform(const std::string& u, const Vec2f&);

    void set_uniform(unsigned int u, const Vec2f&);

    void set_uniform(const std::string& u, const Vec3f&);

    void set_uniform(unsigned int u, const Vec3f&);

    void set_uniform(const std::string& u, const Mat3f&);

    void set_uniform(unsigned int u, const Mat3f&);

    void set_uniform(const std::string& u, const Mat4f&);

    void set_uniform(unsigned int u, const Mat4f&);

    /**
     * Returns a handle to the OpenGL shader program.
     */
    unsigned int get_handle() const
    {
        return _shader;
    }

private:

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
    static unsigned int _link_program(unsigned int vert, unsigned int frag);

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
    static unsigned int _compile_shader(const char* glsl, unsigned int type);

    unsigned int                        _shader, _vShader, _fShader;
    std::map<std::string, unsigned int> _uniformCache;

};

};

#endif
