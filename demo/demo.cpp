#include "demo.h"

#include <cmath>

void Demo::setup()
{
    counter = 0;
}

void Demo::draw()
{
    background(0.184f, 0.204f, 0.247f);
    color(1.0f, 0.0f, 0.0f);
    int w = width() + 200;
    int x = counter - (w / 2);
    int y = sin((x / (double)w) * 2 * M_PI) * 200;
    rect(x, y, 100, 100);
    counter = (counter + 5) % w;
}
