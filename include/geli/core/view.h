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

            private:

                glm::mat4 _vMatrix;
                glm::mat4 _pMatrix;
                Shader&   _shader;

        };

    };

};

#endif
