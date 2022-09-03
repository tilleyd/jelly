#ifndef _JELLY_MIXINS_MOUSE_HPP_
#define _JELLY_MIXINS_MOUSE_HPP_

#include <map>

#include <jelly/math/vec2.hpp>

namespace jelly
{

class Sketch;

/**
 * Sketch mixin that provides queryable mouse state.
 */
class MouseMixin
{

public:

    virtual ~MouseMixin() = default;

protected:

    MouseMixin(Sketch* sketch): _sketch(sketch) {};

    /**
     * Initializes the mouse state and registers the window event callbacks.
     * Should only be called by the Sketch base class.
     */
    void init();

    /**
     * Returns the mouse position in the window pixel space.
     */
    Vec2 mouse_position() const { return _mouse_position; };

    /**
     * Returns true if the provided button is held.
     *
     * \param button
     *     A GLFW mouse button, e.g. GLFW_MOUSE_BUTTON_1.
     */
    bool mouse_button_pressed(int button) const;

private:

    Sketch* _sketch;

    Vec2 _mouse_position;
    std::map<int, bool> _button_pressed;

};

}

#endif
