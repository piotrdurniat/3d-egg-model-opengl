#ifndef VERTEX_3D_H
#define VERTEX_3D_H

#include "Color.hpp"

class Vertex3d
{
public:
    float x;
    float y;
    float z;
    Color* color;

    Vertex3d();
    Vertex3d(float x, float y, float z);
};

#endif