#ifndef _GELI_CORE_VIEW_H_
#define _GELI_CORE_VIEW_H_

#include <glm/gtc/matrix_transform.hpp>

namespace geli
{

    namespace core
    {

        class Shader;

        /**
         * Represents the camera used to view the rendering environment.
         *
         * \author
         *     Duncan Tilley
         **/
        class View
        {

            public:

                View() = delete;
                View(const View&) = delete;
                View& operator=(const View&) = delete;

                /**
                 * Creates a default view in the normalized device coordinates
                 * (i.e. orthographic range [-1,1] on all axes).
                 *
                 * \param shader
                 *     The Shader used in the current environment.
                 **/
                View(Shader&);

                /**
                 * Sets the projection to an orthographic projection.
                 *
                 * \param l
                 *     The minimum (left) x-coordinate visible.
                 * \param r
                 *     The maximum (right) x-coordinate visible.
                 * \param b
                 *     The minimum (bottom) y-coordinate visible.
                 * \param t
                 *     The maximum (top) y-coordinate visible.
                 * \param n
                 *     The minimum (nearest) z-coordinate visible.
                 * \param f
                 *     The maximum (farthest) z-coordinate visible.
                 **/
                void orthographic(float l,
                                  float r,
                                  float b,
                                  float t,
                                  float n,
                                  float f);

            private:

                glm::mat4 _vMatrix;
                glm::mat4 _pMatrix;
                Shader&   _shader;

        };

    };

};

#endif
