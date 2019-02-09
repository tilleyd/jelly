#ifndef _GELI_RENDERER_H_
#define _GELI_RENDERER_H_

#include <geli/model.h>
#include <memory>

namespace geli
{

    class Model;

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
             **/
            Renderer();

            /**
             * Draws a square with the current render state.
             **/
            void renderSquare() const;

        private:

            /**
             * Creates the cached square model used for rectangles.
             **/
            void initSquare();

            /**
             * Creates the cached triangle model.
             **/
            void initTriangle();

            /**
             * Creates the cached circle model used for ellipses.
             **/
            void initCircle();

            // cached primitives
            std::unique_ptr<Model> _square;

    };

};

#endif
