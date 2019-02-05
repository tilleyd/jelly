#ifndef _GELI_RENDERER_H_
#define _GELI_RENDERER_H_

#include <GL/glew.h>

namespace geli
{

    /**
     * Renders objects to the frame buffer.
     *
     * \author
     *     Duncan Tilley
     **/
    class Renderer
    {

        public:

            Renderer(const Renderer&) = delete;
            Renderer& operator=(const Renderer&) = delete;

            /**
             * Creates the shaders used for rendering.
             **/
            Renderer();

            /**
             * Clears all resources used by the renderer.
             **/
            ~Renderer();

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
