#ifndef _SKETCH_H_
#define _SKETCH_H_

#include <geli/sketch.h>
#include <geli/renderer.h>

class DemoSketch: public geli::Sketch
{

    public:

        void init();

        void draw(const geli::Renderer&);

};

void DemoSketch::init()
{}

void DemoSketch::draw(const geli::Renderer& r)
{
    r.renderSquare();
}

#endif
