#ifndef _GELI_SKETCH_H_
#define _GELI_SKETCH_H_

namespace geli
{

    namespace core
    {
        class SketchImpl;
    };

    /**
     * Interface for sketch classes that create and execute within the geli
     * rendering environment.
     *
     * The sketch presents various virtual methods that can be overridden by
     * your own sketches and have plenty protected methods that can be called to
     * access the geli functionality.
     *
     * The internal implementation classes are hidden via the PIMPL principle.
     *
     * \author
     *     Duncan Tilley
     **/
    class Sketch
    {

        public:

            Sketch& operator=(const Sketch&) = delete;

            /**
             * Sets up the geli environment.
             *
             * \throws
             *     `const char*` on any setup failure.
             **/
            Sketch();

            /**
             * Clears the resources used by the geli environment.
             **/
            virtual ~Sketch();

            /**
             * Starts the execution of the sketch. setup() is called first,
             * whereafter draw() is called repeatedly until stop() is called.
             *
             * \param width
             *     The width of the window in pixels.
             * \param height
             *     The height of the window in pixels.
             *
             * \throws
             *     'const char*' on any setup failure.
             **/
            void execute(unsigned int width, unsigned int height);

        protected:

            friend class core::SketchImpl;

            //---------------------
            // PURE VIRTUAL METHODS
            //---------------------

            /**
             * Called when the sketch is first run.
             **/
            virtual void setup() = 0;

            /**
             * Called on every iteration of the rendering loop.
             **/
            virtual void draw() = 0;

            //--------------------
            // OVERRIDABLE METHODS
            //--------------------

            //-------------
            // GELI METHODS
            //-------------

            /**
             * Draws a rectangle.
             **/
            void rect();

            /**
             * Stops the execution of the sketch.
             *
             * \note
             *     This does not immediately stop but will stop after the
             *     current iteration of the rendering loop.
             **/
            void stop();

        private:

            core::SketchImpl* _pimpl;

    };

};

#endif
