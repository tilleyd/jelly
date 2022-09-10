#ifndef _JELLY_SKETCH_HPP_
#define _JELLY_SKETCH_HPP_

#include <memory>

#include <jelly/window.hpp>
#include <jelly/mixins.hpp>

namespace jelly {

/**
 * Defines the abstract sketch class that serves as an entrypoint to access
 * graphics primitives.
 */
class Sketch :
    public CanvasMixin,
    public KeyboardMixin,
    public MouseMixin
{

public:

    Sketch(const Sketch&) = delete;
    Sketch& operator=(const Sketch&) = delete;

    Sketch();
    virtual ~Sketch() = default;

    virtual void init() {};

    virtual void tick(double delta) {};

    virtual void draw() {};

    virtual void on_key_type(int key, int scancode, int modifiers) {}

    virtual void on_key_press(int key, int scancode, int modifiers) {}

    virtual void on_key_release(int key, int scancode, int modifiers) {}

    virtual void on_mouse_press(int button, int modifiers) {}

    virtual void on_mouse_release(int button, int modifiers) {}

    virtual void on_mouse_move(const Vec2& position, const Vec2& from) {}

    virtual void on_mouse_drag(int button, const Vec2& position, const Vec2& from) {}

    virtual bool on_close() { return true; }

    virtual void on_exit() {}

    /**
     * Blocking call that will start the sketch. Your main function only needs
     * to create your sketch and call its run method.
     */
    void run();

    Window& jelly_window() const
    {
        if (_window == nullptr) {
            throw std::runtime_error("Window not available");
        }
        return *_window;
    }

    Context& jelly_context() const
    {
        return jelly_window().get_context();
    }

private:

    std::shared_ptr<Window> _window;

};

}

#endif
