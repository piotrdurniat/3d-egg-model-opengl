#include "Vertex3d.hpp"

Vertex3d::Vertex3d()
{
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
    this->color = new Color();
}
Vertex3d::Vertex3d(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->color = new Color();
}
