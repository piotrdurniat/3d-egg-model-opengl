#include "Egg.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <math.h>
#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include "Color.hpp"

Egg::Egg(int n)
{
    this->n = n;

    setupVerticesOnPlane();
    transformVertices();
}

void Egg::transformVertices()
{
    for (int i = 0; i < n * n; ++i)
    {
        Vertex3d *vertex = vertices[i];
        float u = vertex->x;
        float v = vertex->y;

        vertex->x = (-90.0 * pow(u, 5) + 225.0 * pow(u, 4) - 270.0 * pow(u, 3) + 180.0 * pow(u, 2) - 45.0 * u) * cos(M_PI * v);
        vertex->y = (160.0 * pow(u, 4) - 320.0 * pow(u, 3) + 160.0 * pow(u, 2));
        vertex->z = (-90.0 * pow(u, 5) + 225.0 * pow(u, 4) - 270.0 * pow(u, 3) + 180.0 * pow(u, 2) - 45.0 * u) * sin(M_PI * v);
    }
}

void Egg::setupVerticesOnPlane()
{
    vertices = new Vertex3d *[n * n];

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int index = i + j * n;
            vertices[index] = new Vertex3d((float)i / n, (float)j / n, 0.0f);
        }
    }
}

void Egg::printVertices()
{
    for (int i = 0; i < n * n; ++i)
    {
        std::cout << "x: " << vertices[i]->x << ", y: " << vertices[i]->y << ", z: " << vertices[i]->z << "\n";
    }
}

void Egg::displayVertices()
{
    glBegin(GL_POINTS);

    glColor3ub(255, 255, 255);

    for (int i = 0; i < n * n; ++i)
    {
        Vertex3d *vertex = vertices[i];
        glVertex3f(vertex->x, vertex->y, vertex->z);
    }

    glEnd();
}

void Egg::addVertex(Vertex3d *v)
{
    if (displayColor)
    {
        glColor3ub(v->color->r, v->color->g, v->color->b);
    }
    else
    {
        glColor3ub(255, 255, 255);
    }
    glVertex3f(v->x, v->y, v->z);
}

void Egg::displayMesh(GLenum mode)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            // this vertex
            Vertex3d *vertex1 = vertices[j * n + i];
            // top neighbor
            Vertex3d *vertex2 = vertices[(j + 1) * n + i];
            // top-right neighbor
            Vertex3d *vertex3 = vertices[(j + 1) * n + (i + 1) % n];
            // right neighbor
            Vertex3d *vertex4 = vertices[j * n + (i + 1) % n];

            // Skip the top row
            if (j < n - 1)
            {
                glBegin(mode);
                addVertex(vertex1);
                addVertex(vertex2);
                addVertex(vertex3);
                addVertex(vertex1);
                addVertex(vertex4);
                addVertex(vertex3);
                glEnd();
            }
            else
            // Fill the missing "ring"
            {

                // top neighbor
                Vertex3d *vertex4 = vertices[(n - i)];
                // top-right neighbor
                Vertex3d *vertex5 = vertices[(n - i - 1)];
                // right neighbor
                Vertex3d *vertex6 = vertices[j * n + (i + 1) % n];

                // line from this to top neighbor
                glBegin(mode);
                addVertex(vertex1);
                addVertex(vertex4);
                addVertex(vertex5);
                addVertex(vertex1);
                addVertex(vertex6);
                addVertex(vertex5);
                glEnd();
            }
        }
    }
}

void Egg::display()
{
    switch (displayMode)
    {
    case DisplayMode::vertices:
        displayVertices();
        break;
    case DisplayMode::mesh:
        displayColor = false;
        displayMesh(GL_LINE_STRIP);
        break;
    case DisplayMode::filledTriangles:
        displayColor = true;
        displayMesh(GL_TRIANGLE_STRIP);
        break;
    }
}

void Egg::setDisplayMode(DisplayMode mode)
{
    this->displayMode = mode;
}
