#ifndef _JELLY_MIXINS_RENDER_2D_HPP_
#define _JELLY_MIXINS_RENDER_2D_HPP_

#include <map>

namespace jelly
{

class Sketch;
class Shader;
class Mesh;

/**
 * Sketch mixin that provides basic 2D rendering capabilities.
 */
class Render2DMixin
{

public:

    virtual ~Render2DMixin();

protected:

    Render2DMixin(Sketch* sketch): _sketch(sketch) {};

    /**
     * Initializes the various shaders, meshes, etc. required to perform 2D
     * rendering. Should only be called by the Sketch base class.
     */
    void init();

    void set_fill_rgb(float r, float g, float b);

    void set_fill_rgba(float r, float g, float b, float a);

    void set_fill_value(float value);

    void fill_rectangle(int x1, int y1, int x2, int y2);

    void fill_ellipse(int x, int y, int w, int h);

private:

    Sketch* _sketch;

    Shader* _rectangle_shader;
    Shader* _ellipse_shader;
    Mesh*   _quad_mesh;

};

}

#endif
