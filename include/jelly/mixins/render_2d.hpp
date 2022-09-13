#ifndef _JELLY_MIXINS_RENDER_2D_HPP_
#define _JELLY_MIXINS_RENDER_2D_HPP_

#include <map>
#include <jelly/math/vec4.hpp>

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

    Render2DMixin(Sketch* sketch);

    /**
     * Initializes the various shaders, meshes, etc. required to perform 2D
     * rendering. Should only be called by the Sketch base class.
     */
    void init();

    void set_color(float r, float g, float b);

    void set_color(float r, float g, float b, float a);

    void set_color(float value);

    void set_stroke_size(int stroke);

    void fill_rectangle(int x1, int y1, int x2, int y2);

    void draw_rectangle(int x1, int y1, int x2, int y2);

    void fill_ellipse(int x, int y, int w, int h);

    void draw_ellipse(int x, int y, int w, int h);

private:

    Sketch* _sketch;

    Shader* _fill_rectangle_shader;
    Shader* _fill_ellipse_shader;
    Shader* _draw_rectangle_shader;
    Shader* _draw_ellipse_shader;
    Mesh*   _quad_mesh;

    Vec4 _color;
    int _stroke_size;

};

}

#endif
