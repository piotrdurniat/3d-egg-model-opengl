#include "Color.hpp"
#include <iostream>

Color::Color(int r, int g, int b)
{
    this->r = r;
    this->g = g;
    this->b = b;
    srand(1);
}

Color::Color()
{
    r = rand() % 256;
    g = rand() % 256;
    b = rand() % 256;
}
