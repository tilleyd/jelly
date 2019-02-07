#ifndef _GELI_CORE_H_
#define _GELI_CORE_H_

#include <geli/renderer.h>
#include <geli/sketch.h>
#include <geli/window.h>

namespace geli
{

    /**
     * Contains the core functionality of geli.
     *
     * Core is used to set up the geli rendering environment and to provide a
     * sketch to execute.
     *
     * \author
     *     Duncan Tilley
     **/
    class Core
    {

        public:

            Core(const Core&) = delete;
            Core& operator=(const Core&) = delete;

            /**
             * Initializes the geli core.
             **/
            Core();

            /**
             * Clears resources used by geli core.
             **/
            ~Core();

            /**
             * Creates the rendering environment and starts execution of the
             * provided sketch. After execution (see stop()), the rendering
             * environment is cleared again.
             *
             * \param sketch
             *     The sketch to be executed.
             * \param width
             *     The width of the rendering window in pixels.
             * \param height
             *     The height of the rendering window in pixels.
             *
             * \throws
             *     `const char*` on various failures of the environment setup.
             **/
            void execute(Sketch& sketch,
                         unsigned int width,
                         unsigned int height);

            /**
             * Stops the execution (see execute()) of a sketch.
             **/
            void stop();

        private:

            Window*   _window;
            Renderer* _renderer;
            bool      _executing;

    };

};

#endif
