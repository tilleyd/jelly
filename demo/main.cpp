#include <iostream>

#include <geli/window.hpp>

#include "demo.hpp"

int main(int argc, char* argv[])
{
    try {
        geli::Window w("geli demo", geli::Vec2i(1280, 720));
        Demo d;
        w.set_on_create([&d](geli::Window& w)
        {
            d.create(w);
        });
        w.set_on_draw([&d](geli::Window& w, double p)
        {
            d.draw(w, p);
        });
        w.add_on_key([&d](geli::Window& w, int k, int sc, int a, int m)
        {
            d.on_key(w, k, sc, a, m);
        });
        w.add_on_mouse_move([&d](geli::Window& w, const geli::Vec2d& p, const geli::Vec2d& r)
        {
            d.on_mouse_move(w, p, r);
        });
        w.create_windowed();
    } catch (std::runtime_error e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
