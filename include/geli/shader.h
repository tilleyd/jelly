#ifndef _GELI_SHADER_H_
#define _GELI_SHADER_H_

#include <GL/glew.h>

namespace geli
{

    /**
     * Compiles OpenGL shaders and keeps a handle to the linked program.
     *
     * \warn
     *     The Window must be created before attempting to create the Shader.
     *
     * \author
     *     Duncan Tilley
     **/
    class Shader
    {

        public:

            Shader(const Shader&) = delete;
            Shader& operator=(const Shader&) = delete;

            /**
             * Creates the shaders used for rendering.
             **/
            Shader();

            /**
             * Clears all resources used by the renderer.
             **/
            ~Shader();

        private:

            /**
             * Links the vertex and fragment shaders.
             *
             * \param vert
             *     A handle to the compiled OpenGL vertex shader.
             * \param frag
             *     A handle to the compiled OpenGL fragment shader.
             *
             * \return
             *     A handle to the linked OpenGL shader program.
             *
             * \throws
             *     `const char*` when the linking fails.
             **/
            GLuint linkProgram(GLuint vert, GLuint frag) const;

            /**
             * Compiles the given GLSL code as the specified type of shader.
             *
             * \param glsl
             *     Shader source code.
             * \param type
             *     The shader type constant.
             *
             * \return
             *     A handle to the compiled OpenGL shader.
             *
             * \throws
             *     `const char*` when the compilation fails.
             **/
            GLuint compileShader(const char* glsl, GLenum type) const;

            GLuint _shader;

    };

};

#endif
