#include <iostream>
#include "demo.h"

int main(int argc, char* argv[])
{
    try {
        Demo demo;
        demo.execute(1280, 720);
    } catch (const char* err) {
        std::cout << "Error: " << err << std::endl;
    }
}
