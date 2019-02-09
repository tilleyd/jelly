#include <geli/core.h>
#include <geli/window.h>
#include <geli/shader.h>
#include <geli/renderer.h>

using namespace geli;

Core::Core() :
    _executing(false)
{
    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw "failed to initialize SDL";
    }
    // use OpenGL 330 Core
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
}

Core::~Core()
{
    SDL_Quit();
}

void Core::execute(Sketch& sketch, unsigned int width, unsigned int height)
{
    // set up the environment
    Window window(width, height);
    Shader shader;
    Renderer renderer;

    _executing = true;
    sketch.init();
    while (_executing) {

        // poll SDL events
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT:
                    stop();
                    break;
            }
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        sketch.draw(renderer);
        window.swapBuffers();

    }
}

void Core::stop()
{
    _executing = false;
}
