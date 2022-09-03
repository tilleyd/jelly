# Jelly

Jelly is a C++ library that allows you to quickly and easily add a window to
your program complete with OpenGL rendering capabilities.

## Features

- Simple C++11 API for creating an OpenGL rendering environment.
- Window management that wraps GLFW, complete with event and input system.
- Vector, matrix and quaternion math library.
- Easy 2D/3D primitive rendering with single function calls.
- 2D/3D camera controls.
- Create and render custom meshes.
- Load and work with your own GLSL shaders.

## Installation

#### Dependencies

The following dependencies are required for Jelly to build and run:

- [GLFW 3](https://www.glfw.org/)
- [GLEW](http://glew.sourceforge.net/)
- [stb_image](https://github.com/nothings/stb)

On Ubuntu (last tested on 22.04), these can be installed as follows:

```
sudo apt-get update
sudo apt-get install libglfw3-dev libglew-dev libstb-dev
```

#### Installing

The following will install the archive library to `/usr/local/lib` or
`/usr/local/lib64` and the header files to `/usr/local/include` by default:

```
git clone https://github.com/tilleyd/jelly.git
mkdir jelly/build
cd jelly/build
cmake ..
sudo make install
```

Make sure that `/usr/local/lib64` is in the library path if that is the
installation destination, as it is not included on all systems by default.

## Documentation

Online documentation is not available at the moment. You can have a look at the
`include/` folder as most header files contain thorough documentation.
Alternatively you can do the generate documentation, provided that you have
Doxygen installed:

```
git clone https://github.com/tilleyd/jelly.git
cd jelly
doxygen
```

You can then open `doc/html/index.html` with your favourite browser.
