#ifndef _GELI_CORE_WINDOW_H_
#define _GELI_CORE_WINDOW_H_

#include <SDL2/SDL.h>

namespace geli
{

    namespace core
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

                /**
                 * Returns the height of the window in pixels.
                 **/
                unsigned int getHeight() const
                {
                    return _height;
                }

                /**
                 * Returns the width of the window in pixels.
                 **/
                unsigned int getWidth() const
                {
                    return _width;
                }

            private:

                SDL_Window*  _window;
                unsigned int _width;
                unsigned int _height;

        };

    };

};

#endif
