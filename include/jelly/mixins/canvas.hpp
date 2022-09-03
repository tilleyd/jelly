#ifndef _JELLY_MIXINS_CANVAS_HPP_
#define _JELLY_MIXINS_CANVAS_HPP_

#include <memory>

#include <jelly/math/vec2.hpp>

namespace jelly
{

class Sketch;
class Window;

/**
 * Sketch mixin that provides methods to access and configure the canvas,
 * display, and window.
 */
class CanvasMixin
{

public:

    virtual ~CanvasMixin() = default;

protected:

    CanvasMixin(Sketch* sketch): _sketch(sketch) {};

    /**
     * Get the current width of the window.
     */
    int window_width() const;

    /**
     * Get the current height of the window.
     */
    int window_height() const;

    /**
     * Get the current size of the window as a floating point vector.
     */
    Vec2 window_size() const;

private:

    Sketch* _sketch;

    std::shared_ptr<Window> _try_get_window() const;

};

}

#endif
