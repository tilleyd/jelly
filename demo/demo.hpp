#ifndef _DEMO_H_
#define _DEMO_H_

#include <jelly/jelly.hpp>

class Demo : public jelly::Sketch
{

public:

    Demo();

    virtual ~Demo();

    virtual void init() override;

    virtual void tick(double d) override;

};

#endif
