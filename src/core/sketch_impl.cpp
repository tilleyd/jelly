#include <geli/core/sketch_impl.h>

#include <geli/sketch.h>
#include <geli/core/window.h>
#include <geli/core/shader.h>
#include <geli/core/renderer.h>
#include <geli/core/view.h>

using namespace geli::core;

SketchImpl::SketchImpl() :
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

SketchImpl::~SketchImpl()
{
    SDL_Quit();
}

void SketchImpl::execute(Sketch& sketch,
                         unsigned int width,
                         unsigned int height)
{
    // set up the environment
    _window.reset(new Window(width, height));
    _shader.reset(new Shader);
    _renderer.reset(new Renderer(*_shader));
    _view.reset(new View(*_shader));
    ortho();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _executing = true;
    sketch.setup();
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

        sketch.draw();
        _window->swapBuffers();

    }
}

void SketchImpl::background(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SketchImpl::circle(float x, float y, float d)
{
    ellipse(x, y, d, d);
}

void SketchImpl::color(float r, float g, float b, float a)
{
    _shader->setColor(r, g, b, a);
}

void SketchImpl::ellipse(float x, float y, float w, float h)
{
    _renderer->resetTransform();
    _renderer->translateTransform(x, y, 0.0f);
    _renderer->scaleTransform(w, h, 1.0f);
    _renderer->renderCircle();
}

void SketchImpl::line(float x1, float y1, float x2, float y2)
{
    _renderer->resetTransform();
    _renderer->translateTransform(x1, y1, 0.0f);
    _renderer->renderLine(x2 - x1, y2 - y1, 0.0f);
}

void SketchImpl::rect(float x, float y, float w, float h)
{
    _renderer->resetTransform();
    _renderer->translateTransform(x, y, 0.0f);
    _renderer->scaleTransform(w, h, 1.0f);
    _renderer->renderSquare();
}

void SketchImpl::stop()
{
    _executing = false;
}

void SketchImpl::ortho()
{
    float r = width() * 0.5f;
    float t = height() * 0.5f;
    ortho(-r, r, -t, t, -1.0f, 1.0f);
}

void SketchImpl::ortho(float l, float r, float b, float t, float n, float f)
{
    _view->orthographic(l, r, b, t, n, f);
}

unsigned int SketchImpl::height() const
{
    return _window->getHeight();
}

unsigned int SketchImpl::width() const
{
    return _window->getWidth();
}
