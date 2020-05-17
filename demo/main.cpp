#include <iostream>

#include <geli/window.hpp>

#include "demo.h"

int main(int argc, char* argv[])
{
    try {
        geli::Window w("geli demo", geli::Vec2i(1280, 720));
        Demo d;
        w.on_create([&d](geli::Window& w)
        {
            d.create(w);
        });
        w.on_draw([&d](geli::Window& w, double p)
        {
            d.draw(w, p);
        });
        w.create_windowed();
    } catch (std::runtime_error e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
