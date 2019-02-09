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

            //------------------
            // RENDERING METHODS
            //------------------

            /**
             * Clears the rendering environment and sets the background to the
             * provided colors.
             *
             * \param r
             *     Red value in range [0.0, 1.0].
             * \param g
             *     Green value in range [0.0, 1.0].
             * \param b
             *     Blue value in range [0.0, 1.0].
             * \param a
             *     Alpha value in range [0.0, 1.0].
             **/
            void background(float r, float g, float b, float a = 1.0f);

            /**
             * Sets the color for any future model renders.
             *
             * \param r
             *     Red value in range [0.0, 1.0].
             * \param g
             *     Green value in range [0.0, 1.0].
             * \param b
             *     Blue value in range [0.0, 1.0].
             * \param a
             *     Alpha value in range [0.0, 1.0].
             **/
            void color(float r, float g, float b, float a = 1.0f);

            /**
             * Draws a rectangle.
             *
             * \param x
             *     X-coordinate of the rectangle center.
             * \param y
             *     Y-coordinate of the rectangle center.
             * \param w
             *     Width of the rectangle.
             * \param h
             *     Height of the rectangle.
             **/
            void rect(float x, float y, float w, float h);

            /**
             * Draws a square.
             *
             * \param x
             *     X-coordinate of the square center.
             * \param y
             *     Y-coordinate of the square center.
             * \param e
             *     Extent (width and height) of the square.
             **/
            void square(float x, float y, float e);

            /**
             * Stops the execution of the sketch.
             *
             * \note
             *     This does not immediately stop but will stop after the
             *     current iteration of the rendering loop.
             **/
            void stop();

            //--------------------
            // VIEW/CAMERA METHODS
            //--------------------

            /**
             * Creates an orthographic view of the rendering environment.
             * This is the default view mode when starting the sketch and is
             * the same as
             * ortho(-width()/2, width()/2, -height()/2, height()/2).
             **/
            void ortho();

            /**
             * Creates an orthographic view of the rendering environment.
             *
             * \param l
             *     The minimum (left) x-coordinate visible.
             * \param r
             *     The maximum (right) x-coordinate visible.
             * \param b
             *     The minimum (bottom) y-coordinate visible.
             * \param t
             *     The maximum (top) y-coordinate visible.
             **/
            void ortho(float l, float r, float b, float t);

            /**
             * Creates an orthographic view of the rendering environment.
             *
             * \param l
             *     The minimum (left) x-coordinate visible.
             * \param r
             *     The maximum (right) x-coordinate visible.
             * \param b
             *     The minimum (bottom) y-coordinate visible.
             * \param t
             *     The maximum (top) y-coordinate visible.
             * \param n
             *     The minimum (nearest) z-coordinate visible.
             * \param f
             *     The maximum (farthest) z-coordinate visible.
             **/
            void ortho(float l, float r, float b, float t, float n, float f);

            //----------
            // ACCESSORS
            //----------

            /**
             * Returns the height of the view port in pixels.
             **/
            unsigned int height() const;

            /**
             * Returns the width of the view port in pixels.
             **/
            unsigned int width() const;

        private:

            core::SketchImpl* _pimpl;

    };

};

#endif
