#include <iostream>
#include <geli/window.hpp>

int main(int argc, char* argv[])
{
    try {
        geli::Window w("geli demo", geli::Vec2i(1280, 720));
        w.on_draw([&](double p)
        {
            std::cout << p << std::endl;
        });
        w.create_windowed();
    } catch (std::runtime_error e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
