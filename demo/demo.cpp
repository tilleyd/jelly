#include "demo.hpp"

#include <iostream>

using namespace jelly;


Demo::Demo() {}


Demo::~Demo() {}


void Demo::init() {
    printf("Window size: (%d, %d)\n", window_width(), window_height());
}


void Demo::tick(double delta) {
    printf("Key pressed: %d\n", key_pressed(GLFW_KEY_W));
}
