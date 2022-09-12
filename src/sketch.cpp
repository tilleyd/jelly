#include <jelly/sketch.hpp>

using namespace jelly;

Sketch::Sketch() :
    CanvasMixin(this),
    KeyboardMixin(this),
    MouseMixin(this),
    Render2DMixin(this)
{}

void Sketch::run() {
    _window = std::make_shared<Window>("Jelly", 640, 480);

    _window->set_on_create([this](Window& w, Context& c) {
        // first initialize mixins that require it
        this->MouseMixin::init();
        this->KeyboardMixin::init();
        this->Render2DMixin::init();

        // set the projection to orthographic by default
        Vec2 size = w.get_size();
        this->_projection = Mat4::orthographic(
            0.0f, size.x(), 0.0f, size.y(), -1.0f, 1.0f
        );

        this->init();
    });

    _window->set_on_draw([this](Window& w, Context& c, double d) {
        this->tick(d);
        this->draw();
    });

    _window->create_windowed();
}
