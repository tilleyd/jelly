#ifndef _GELI_CORE_SHADER_H_
#define _GELI_CORE_SHADER_H_

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

namespace geli
{

    namespace core
    {

        /**
         * Allows interaction with the OpenGL shader program.
         *
         * The shaders are compiled and linked, with a handle to the linked
         * program being kept by the object. The shader object also allows
         * interaction with the uniforms of the shader.
         *
         * \warn
         *     The Window must be created before attempting to create the
         *     Shader.
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
                 * Creates the shaders used for rendering and gets the uniform
                 * handles.
                 **/
                Shader();

                /**
                 * Clears all resources used by the renderer.
                 **/
                ~Shader();

                /**
                 * Sets the u_MMatrix shader uniform.
                 *
                 * \param mm
                 *     The mat4 representing the model matrix.
                 **/
                void setMMatrix(const glm::mat4& mm);

                /**
                 * Sets the u_VMatrix shader uniform.
                 *
                 * \param vm
                 *     The mat4 representing the view matrix.
                 **/
                void setVMatrix(const glm::mat4& vm);

                /**
                 * Sets the u_PMatrix shader uniform.
                 *
                 * \param pm
                 *     The mat4 representing the projection matrix.
                 **/
                void setPMatrix(const glm::mat4& pm);

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

                GLuint _mMatrixUniform;
                GLuint _vMatrixUniform;
                GLuint _pMatrixUniform;

        };

    };

};

#endif
