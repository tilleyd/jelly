#include <geli/core.h>
#include "demo_sketch.h"

int main(int argc, char* argv[])
{
    DemoSketch sketch;
    geli::Core core;
    core.execute(sketch, 1280, 720);
}
