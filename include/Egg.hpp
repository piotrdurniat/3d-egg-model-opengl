#ifndef EGG_H
#define EGG_H
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>

#include "Vertex3d.hpp"
#include "DisplayMode.hpp"

class Egg
{
private:
    int n = 20;
    DisplayMode displayMode = DisplayMode::mesh;
    bool displayColor = false;
    // array holding the vertices of the model
    Vertex3d **vertices;

public:
    Egg(int n);
    // Translate the vertices according to a given formula to form an egg shape
    void transformVertices();
    // Sets up a 2d plain consisting of n x n vertices.
    // Each coordinate (x, y, z) has a value >= 0 and <= 1.
    void setupVerticesOnPlane();
    // prints the position of all the vertices to the standard output
    void printVertices();
    void displayVertices();
    void addVertex(Vertex3d *v);
    void displayMesh(GLenum mode);
    void display();
    void setDisplayMode(DisplayMode mode);
};

#endif