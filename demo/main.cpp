#include <iostream>
#include <geli/core.h>
#include "demo_sketch.h"

int main(int argc, char* argv[])
{
    try {
        DemoSketch sketch;
        geli::Core core;
        core.execute(sketch, 1280, 720);
    } catch (const char* err) {
        std::cout << "Error: " << err << std::endl;
    }
}
