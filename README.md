# geli

`geli` (short for Graphical Extensions Library) is a C++ library that allows you to quickly and easily add a rendered window to your program. `geli` can be used for anything from visually debuggin complex software, creating visualisations or developing a game.

## Installation

The following will install the archive library to `/usr/local/lib` or `/usr/local/lib64` and the header files to `/usr/local/include` by default:

```
git clone https://github.com/tilleyd/geli.git
cd geli
mkdir build
cd build
cmake ..
sudo make install
```
Make sure that `/usr/local/lib64` is in the library path if that is the installation destination, as it is not included on all systems by default.

## Documentation

Online documentation is not supported at the moment. You can have a look at the `include/` folder as most header files contain thorough documentation. Alternatively you can do the following, provided that you have Doxygen installed:

```
git clone https://github.com/tilleyd/geli.git
cd orchestral
doxygen
```

You can then open `doc/html/index.html` with your favourite browser.
