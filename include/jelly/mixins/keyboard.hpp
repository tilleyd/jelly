#ifndef _JELLY_MIXINS_KEYBOARD_HPP_
#define _JELLY_MIXINS_KEYBOARD_HPP_

#include <map>

namespace jelly
{

class Sketch;

/**
 * Sketch mixin that provides queryable keyboard button states.
 */
class KeyboardMixin
{

public:

    virtual ~KeyboardMixin() = default;

protected:

    KeyboardMixin(Sketch* sketch): _sketch(sketch) {};

    /**
     * Initializes the key states and registers window event callbacks. Should
     * only be called by the Sketch base class.
     */
    void init();

    /**
     * Returns true if the given key is currently pressed.
     *
     * \param key
     *     A GLFW key code, e.g. GLFW_KEY_SPACE.
     */
    bool key_pressed(int key) const;

private:

    Sketch* _sketch;

    std::map<int, bool> _key_pressed;

};

}

#endif
