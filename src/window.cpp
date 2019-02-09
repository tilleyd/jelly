#include <geli/window.h>

#include <GL/glew.h>

using geli::Window;

Window::Window(unsigned int width, unsigned int height) :
    _window(nullptr)
{
    // create the SDL window
    _window = SDL_CreateWindow("geli window",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               width,
                               height,
                               SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!_window) {
        throw "failed to create window";
    }
    // set up OpenGL
    SDL_GLContext gl = SDL_GL_CreateContext(_window);
    if (!gl) {
        throw "failed to create OpenGL context";
    }
    if (glewInit() != GLEW_OK) {
        throw "failed to initialise GLEW";
    }
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);
    // enable V-Sync
    if (SDL_GL_SetSwapInterval(1) < 0) {
        throw "failed to enable V-Sync";
    }
}

Window::~Window()
{
    if (_window) {
        SDL_DestroyWindow(_window);
    }
}

void Window::swapBuffers() const
{
    SDL_GL_SwapWindow(_window);
}
