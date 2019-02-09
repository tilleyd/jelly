#ifndef _GELI_MODEL_H_
#define _GELI_MODEL_H_

#include <GL/glew.h>

namespace geli
{

    /**
     * Represents a renderable model's geometry containing a VBO, EBO and VAO.
     *
     * \author
     *     Duncan Tilley
     **/
    class Model
    {

        public:

            Model() = delete;
            Model(const Model&) = delete;
            Model& operator=(const Model&) = delete;

            /**
             * Creates a model from the given vertex array.
             *
             * \param vert
             *     The array of vertices. The vertex array must be in the format
             *     { x1, y1, z1 ... xn, yn, zn}.
             * \param n
             *     The number of vertices, *not* the number of elements in the
             *     array (length of vert is assumed to be 3 * n).
             * \param mode
             *     The OpenGL rendering mode used to render the vertices such
             *     as GL_POINTS, GL_LINE_STRIP, GL_TRIANGLES, etc.
             **/
            Model(const float vert[],
                  unsigned int n,
                  unsigned int mode = GL_TRIANGLES);

            /**
             * Clears resources used by the model.
             **/
            ~Model();

            /**
             * Renders the model to the frame buffer.
             **/
            void render() const;

            /**
             * Returns a handle to the OpenGL VBO.
             **/
            unsigned int getVbo() const
            {
                return _vbo;
            }

            /**
             * Returns a handle to the OpenGL VAO.
             **/
            unsigned int getVao() const
            {
                return _vao;
            }

        private:

            unsigned int _numVertices;
            unsigned int _vbo;
            unsigned int _vao;
            unsigned int _renderMode;

    };

};

#endif
