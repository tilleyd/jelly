#ifndef _GELI_SHADER_HPP_
#define _GELI_SHADER_HPP_

#include <string>
#include <map>
#include <memory>

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

    Shader() = delete;
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    /**
     * Returns the default shader.
     */
    static std::shared_ptr<Shader> default_shader();

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
     * Sets the shader as the active shader.
     */
    void use() const;

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

    unsigned int                        _shader;
    std::map<std::string, unsigned int> _uniformCache;

    static std::shared_ptr<Shader> _defaultShader;

};

};

#endif
