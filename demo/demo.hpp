#ifndef _DEMO_H_
#define _DEMO_H_

#include <geli/window.hpp>
#include <geli/camera.hpp>

class Demo
{

public:

    void create(geli::Window&);

    void draw(geli::Window&, double p);

    void on_key(geli::Window&, int, int, int, int);

    void on_mouse_move(geli::Window&, const geli::Vec2d&, const geli::Vec2d&);

private:

    int _counter;
    geli::OrbitCamera _camera;

};

#endif
