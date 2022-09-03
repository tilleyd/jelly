#include <iostream>

#include <jelly/window.hpp>

#include "demo.hpp"

int main(int argc, char* argv[])
{
    try {
        jelly::Window w("jelly demo", 1280, 720);
        Demo d;
        w.set_on_create([&d](jelly::Window& w, jelly::Context& c)
        {
            d.create(w, c);
        });
        w.set_on_draw([&d](jelly::Window& w, jelly::Context& c, double p)
        {
            d.draw(w, c, p);
        });
        w.add_on_key([&d](jelly::Window& w, int k, int sc, int a, int m)
        {
            d.on_key(w, k, sc, a, m);
        });
        w.add_on_mouse_move([&d](jelly::Window& w, const jelly::Vec2& p, const jelly::Vec2& r)
        {
            d.on_mouse_move(w, p, r);
        });
        w.create_windowed();
    } catch (std::runtime_error e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
