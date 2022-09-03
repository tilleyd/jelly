#include <iostream>

#include <jelly/window.hpp>

#include "demo.hpp"

int main(int argc, char* argv[])
{
    Demo d;
    try {
        d.run();
    } catch (std::runtime_error e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
