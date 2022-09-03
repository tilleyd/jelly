#include <jelly/sketch.hpp>

using namespace jelly;

Sketch::Sketch() :
    CanvasMixin(this),
    KeyboardMixin(this),
    MouseMixin(this)
{}

void Sketch::run() {
    _window = std::make_shared<Window>("Jelly", 640, 480);

    _window->set_on_create([this](Window& w, Context& c) {
        // first initialize mixins that require it
        this->MouseMixin::init();
        this->KeyboardMixin::init();

        this->init();
    });

    _window->set_on_draw([this](Window& w, Context& c, double d) {
        this->tick(d);
        this->draw();
    });

    _window->create_windowed();
}
