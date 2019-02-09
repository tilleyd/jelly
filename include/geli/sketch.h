#ifndef _GELI_SKETCH_H_
#define _GELI_SKETCH_H_

namespace geli
{

    class Renderer;

    /**
     * Interface for sketch classes that are executable by the geli rendering
     * environment.
     *
     * \author
     *     Duncan Tilley
     **/
    class Sketch
    {

        public:

            /**
             * Called when the sketch is first run.
             **/
            virtual void init() = 0;

            /**
             * Called on every iteration of the rendering loop.
             *
             * \param r
             *     The renderer that can be used to access rendering functions.
             **/
            virtual void draw(const Renderer& r) = 0;

    };

};

#endif
