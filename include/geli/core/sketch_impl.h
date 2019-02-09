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
         * For brevity of documentation, the methods of SketchImpl have no
         * descriptions. Simply refer to the method of the same name in
         * Sketch for information.
         *
         * \author
         *     Duncan Tilley
         **/
        class SketchImpl
        {

            public:

                SketchImpl(SketchImpl&) = delete;
                SketchImpl& operator=(const SketchImpl&) = delete;

                SketchImpl();

                ~SketchImpl();

                void execute(Sketch& sketch, unsigned int, unsigned int);

                void rect(float, float, float, float);

                void stop();

                void ortho();

                void ortho(float, float, float, float, float, float);

                unsigned int height() const;

                unsigned int width() const;

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
