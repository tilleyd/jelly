#include "demo.hpp"

#include <iostream>

using namespace jelly;


Demo::Demo() {}


Demo::~Demo() {}


void Demo::init() {
    printf("Window size: (%d, %d)\n", window_width(), window_height());
}


void Demo::tick(double delta) {
    Vec2 size = window_size();
    clear_rgb(0.8f, 0.9f, 1.0f);
    set_stroke_size(3);
    set_color(1.0f);
    fill_rectangle(10, 10, size.x() - 10, size.y() - 10);
    set_color(0.0f);
    draw_rectangle(10, 10, size.x() - 10, size.y() - 10);
    set_color(1.0f, 0.0f, 0.0f);
    fill_ellipse(size.x() / 2, size.y() / 2, size.y() - 40, size.y() - 40);
    set_color(0.5f, 0.0f, 0.0f);
    draw_ellipse(size.x() / 2, size.y() / 2, size.y() - 40, size.y() - 40);
}
