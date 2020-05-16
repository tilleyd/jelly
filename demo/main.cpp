#include <iostream>
#include <geli/mesh.hpp>
#include <geli/window.hpp>

int main(int argc, char* argv[])
{
    try {
        geli::Window w("geli demo", geli::Vec2i(1280, 720));
        w.on_draw([&](double p)
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.15f, 0.15f, 0.15f, 1.f);
            geli::Mesh::cube_mesh()->render();
        });
        w.create_windowed();
    } catch (std::runtime_error e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
