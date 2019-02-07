#include <geli/core.h>

using namespace geli;

Core::Core() :
    _window(nullptr),
    _renderer(nullptr),
    _executing(false)
{}

Core::~Core()
{
    if (_renderer) {
        delete _renderer;
    }
    if (_window) {
        delete _window;
    }
}

void Core::execute(Sketch& sketch, unsigned int width, unsigned int height)
{
    // set up the environment
    _window = new Window(width, height);
    _renderer = new Renderer();
    _executing = true;

    sketch.init();
    while (_executing) {
        SDL_Event e;
        // poll SDL events
        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT:
                    stop();
                    break;
            }
        }
        sketch.draw();
        _window->swapBuffers();
    }
}

void Core::stop()
{
    _executing = false;
}
