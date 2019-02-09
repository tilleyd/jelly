#include "demo.h"

#include <cmath>

void Demo::setup()
{
    counter = 0;
}

void Demo::draw()
{
    background(0.184f, 0.204f, 0.247f);
    int w = width() + 200;
    int x = counter - (w / 2);
    int y = sin((x / (double)w) * 2 * M_PI) * 200;
    color(0.322f, 0.58f, 0.886f);
    rect(x, y, 200, 100);
    color(0.886f, 0.322f, 0.58f);
    circle(x, -y, 150);
    counter = (counter + 5) % w;
}
