#ifndef _GELI_WINDOW_H_
#define _GELI_WINDOW_H_

#include <SDL2/SDL.h>

namespace geli
{

    /**
     * Encapsulates a window and the geli rendering environment.
     *
     * \warn
     *     Do not attempt to create 2 windows as that may lead to unexpected
     *     results.
     *
     * \author
     *     Duncan Tilley
     **/
    class Window
    {

        public:

            Window() = delete;
            Window(const Window&) = delete;
            Window& operator=(const Window&) = delete;

            /**
             * Creates a window with the given width and height in pixels.
             *
             * \param width
             *     The window width in pixels.
             * \param height
             *     The window height in pixels.
             *
             * \throws
             *     `const char*` when a subsystem fails to initialise.
             **/
            Window(unsigned int width, unsigned int height);

            /**
             * Closes the window and clears memory used by the rendering
             * environment.
             **/
            ~Window();

            /**
             * Swaps the frame buffers to display the rendered image.
             **/
            void swapBuffers() const;

        private:

            SDL_Window* _window;

    };

};

#endif
