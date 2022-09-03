#ifndef _JELLY_WINDOW_HPP_
#define _JELLY_WINDOW_HPP_

#include <functional>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <jelly/gl/framebuffer.hpp>
#include <jelly/gl/context.hpp>
#include <jelly/math.hpp>

namespace jelly
{


class Window;


/**
 * A window create callback function.
 *
 * \param Window
 *     The window that triggered the event.
 * \param Context
 *     The rendering context associated with the window.
 */
typedef std::function<void(Window&, Context&)> create_callback_t;


/**
 * A draw loop callback function.
 *
 * \param Window
 *     The window that triggered the event.
 * \param Context
 *     The rendering context associated with the window.
 * \param double
 *     The time passed since the previous draw call.
 */
typedef std::function<void(Window&, Context&, double)> draw_callback_t;


/**
 * A window close callback function. Should return true to allow the window
 * to exit, or false to override and block the close.
 */
typedef std::function<bool(Window&)> close_callback_t;


/**
 * A window exit callback function.
 */
typedef std::function<void(Window&)> exit_callback_t;


/**
 * A keyboard event callback function.
 *
 * \param int
 *     The key token of the key pressed.
 * \param int
 *     The unique scancode of the key.
 * \param int
 *     The action performed, GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE.
 * \param int
 *     Modifier key state bits.
 */
typedef std::function<void(Window&, int, int, int, int)> key_callback_t;


/**
 * A mouse button event callback function.
 *
 * \param int
 *     The token of the mouse button pressed.
 * \param int
 *     The action performed, GLFW_PRESS or GLFW_RELEASE.
 * \param int
 *     Modifier key state bits.
 */
typedef std::function<void(Window&, int, int, int)> mouse_button_callback_t;


/**
 * A mouse move event callback function.
 *
 * \param Vec2d
 *     The current position of the mouse in pixel coordinates.
 * \param Vec2d
 *     The position of the mouse relative to the previous position.
 */
typedef std::function<void(Window&, const Vec2&, const Vec2&)> mouse_move_callback_t;


/**
 * A mouse drag event callback function.
 *
 * \param Vec2d
 *     The current position of the mouse in pixel coordinates.
 * \param Vec2d
 *     The position of the mouse relative to the previous position.
 * \param int
 *     The token of the mouse button being held.
 */
typedef std::function<void(Window&, const Vec2&, const Vec2&, int)> mouse_drag_callback_t;


/**
 * Defines a window used for the rendering environment.
 *
 * \note All callback functions run in the same thread in which the window
 * was created.
 */
class Window
{

public:

    Window() = delete;
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    /**
     * Creates a window with a given title. The window
     *
     * \param title
     *     The title of the window.
     * \param width
     *     The pixel width of the window.
     * \param height
     *     The pixel height of the window.
     */
    Window(const std::string& title, int width, int height);

    /**
     * Closes and discards the window.
     */
    ~Window();

    /**
     * Creates and shows the window with a fixed size. This passes control to
     * the window's draw loop.
     *
     * \throw std::runtime_error if creation of the window failed.
     */
    void create_windowed();

    /**
     * Creates and shows the window in borderless fullscreen mode. This passes
     * control to the window's draw loop.
     *
     * \throw std::runtime_error if creation of the window failed.
     */
    void create_borderless();

    /**
     * Creates and shows the window in fullscreen mode. This passes control to
     * the window's draw loop.
     *
     * \throw std::runtime_error if creation of the window failed.
     */
    void create_fullscreen();

    /**
     * Marks the window to exit after completion of the current draw step.
     */
    void exit();

    /**
     * Sets the callback function to be called when the window is created.
     */
    void set_on_create(create_callback_t);

    /**
     * Sets the callback function to be called at each draw step.
     */
    void set_on_draw(draw_callback_t);

    /**
     * Sets the callback function to be called when the window is closed by the
     * user or system, allowing to optionally bypass the decision.
     */
    void set_on_close(close_callback_t);

    /**
     * Sets the callback function to be called when the window is exited.
     */
    void set_on_exit(exit_callback_t);

    /**
     * Adds a keyboard event callback.
     */
    void add_on_key(key_callback_t);

    /**
     * Adds a callback for mouse button events.
     */
    void add_on_mouse_button(mouse_button_callback_t);

    /**
     * Adds a callback for mouse move events.
     */
    void add_on_mouse_move(mouse_move_callback_t);

    /**
     * Adds a callback for mouse drag events.
     */
    void add_on_mouse_drag(mouse_drag_callback_t);

    /**
     * Hides and captures the mouse to allow unrestricted mouse movement.
     */
    void capture_mouse();

    /**
     * Hides the mouse if it is over the window, but does not capture its
     * position.
     */
    void hide_mouse();

    /**
     * Undoes the effects of capture_mouse() and hide_mouse().
     */
    void restore_mouse();

    /**
     * Returns the width of the window in pixels.
     */
    int get_width() const { return _width; }

    /**
     * Returns the height of the window in pixels.
     */
    int get_height() const { return _height; }

    /**
     * Returns the size of the window in pixels.
     */
    Vec2 get_size() const { return Vec2(_width, _height); }

    /**
     * Returns true if the window will exit at the end of the current draw step.
     */
    bool will_exit() const
    {
        return _willExit;
    }

    /**
     * Returns true if the window is currently executing the draw loop.
     */
    bool is_active() const
    {
        return _isActive;
    }

    /**
     * Returns the raw GLFW window handle.
     */
    GLFWwindow* get_glfw_handle()
    {
        return _windowHandle;
    }

private:

    GLFWwindow*  _windowHandle;
    std::string  _title;
    int          _width, _height;
    Vec2         _mousePos;
    int          _mouseButton;

    bool _willExit, _isActive;

    create_callback_t _createCallback;
    draw_callback_t   _drawCallback;
    close_callback_t  _closeCallback;
    exit_callback_t   _exitCallback;

    std::vector<key_callback_t>          _keyCallbacks;
    std::vector<mouse_button_callback_t> _mouseButtonCallbacks;
    std::vector<mouse_move_callback_t>   _mouseMoveCallbacks;
    std::vector<mouse_drag_callback_t>   _mouseDragCallbacks;

    Context* _context;

    void _start_glfw();

    void _end_glfw();

    void _start_glew();

    void _setup_events();

    void _draw_loop();

    void _exit();

    static void _glfw_key_callback(GLFWwindow*, int, int, int, int);

    static void _glfw_mouse_button_callback(GLFWwindow*, int, int, int);

    static void _glfw_mouse_move_callback(GLFWwindow*, double, double);

};

};

#endif
