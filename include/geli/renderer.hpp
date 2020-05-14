#ifndef _GELI_CORE_RENDERER_H_
#define _GELI_CORE_RENDERER_H_

#include <geli/core/model.h>
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

namespace geli
{

    namespace core
    {

        class Shader;

        /**
         * Renders objects to the frame buffer.
         *
         * Models are cached in the renderer and are then rendered with a model
         * matrix for transformations.
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
                 * Creates the primitive models.
                 *
                 * The models used for rectangles, triangles and ellipses are
                 * created and cached for reuse.
                 *
                 * \param shader
                 *     The Shader used in the current environment.
                 **/
                Renderer(Shader&);

                /**
                 * Clears resources used by the renderer.
                 **/
                ~Renderer();

                /**
                 * Sets the model matrix to the identity matrix.
                 **/
                void resetTransform();

                /**
                 * Translates the model matrix by the given offset.
                 *
                 * \param x
                 *     Translation distance on the x-axis.
                 * \param y
                 *     Translation distance on the y-axis.
                 * \param z
                 *     Translation distance on the z-axis.
                 **/
                void translateTransform(float x, float y, float z);

                /**
                 * Scales the model matrix by the given factor.
                 *
                 * \param x
                 *     Scale factor for the x-axis.
                 * \param y
                 *     Scale factor for the y-axis.
                 * \param z
                 *     Scale factor for the z-axis.
                 **/
                void scaleTransform(float x, float y, float z);

                /**
                 * Draws a square with the current transformation.
                 **/
                void renderSquare() const;

                /**
                 * Draws a circle with the current transformation.
                 **/
                void renderCircle() const;

                /**
                 * Draws a line from the origin to the given point with the
                 * current transformation.
                 **/
                void renderLine(float x, float y, float z) const;

            private:

                /**
                 * Creates the cached square model used for rectangles.
                 **/
                void initSquare();

                /**
                 * Creates the cached circle model used for ellipses.
                 **/
                void initCircle();

                /**
                 * Creates the dynamic data buffer for lines.
                 **/
                void initLine();

                Shader&                _shader;
                glm::mat4              _mMatrix;
                std::unique_ptr<Model> _square;
                std::unique_ptr<Model> _circle;
                GLuint                 _lineVbo, _lineVao;

        };

    };

};

#endif
