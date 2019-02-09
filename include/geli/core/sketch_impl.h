#ifndef _GELI_CORE_SKETCH_IMPL_H_
#define _GELI_CORE_SKETCH_IMPL_H_

#include <memory>

namespace geli
{

    class Sketch;

    namespace core
    {

        class Window;
        class Shader;
        class Renderer;
        class View;

        /**
         * A PIMPL implementation of the Sketch object.
         *
         * \author
         *     Duncan Tilley
         **/
        class SketchImpl
        {

            public:

                SketchImpl(SketchImpl&) = delete;
                SketchImpl& operator=(const SketchImpl&) = delete;

                /**
                 * See Sketch::Sketch().
                 **/
                SketchImpl();

                /**
                 * See Sketch::~Sketch().
                 **/
                ~SketchImpl();

                /**
                 * See Sketch::execute().
                 **/
                void execute(Sketch& sketch,
                             unsigned int width,
                             unsigned int height);

                /**
                 * See Sketch::rect().
                 **/
                void rect();

                /**
                 * See Sketch::stop().
                 **/
                void stop();

            private:

                bool                      _executing;
                std::unique_ptr<Window>   _window;
                std::unique_ptr<Shader>   _shader;
                std::unique_ptr<Renderer> _renderer;
                std::unique_ptr<View>     _view;

        };
    };
};

#endif
