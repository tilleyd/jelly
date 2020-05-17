#ifndef _DEMO_H_
#define _DEMO_H_

#include <geli/window.hpp>

class Demo
{

public:

    void create(geli::Window&);

    void draw(geli::Window&, double p);

private:

    int _counter;

};

#endif
