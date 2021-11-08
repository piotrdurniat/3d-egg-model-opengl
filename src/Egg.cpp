// #ifdef _WIN32
// #include <windows.h>
// #endif

// #include <iostream>
// #include <ctime>
// #include <string>
// #include <math.h>
// #include <GL/gl.h>
// #include <GL/glut.h>
// #define _USE_MATH_DEFINES

// class Egg
// {
// private:
//     enum class DisplayMode
//     {
//         vertices = 1,
//         mesh = 2,
//         filledTriangles = 3
//     };

//     int n = 20;
//     DisplayMode displayMode = DisplayMode::mesh;
//     bool displayColor = false;

//     class Color
//     {
//     public:
//         int r;
//         int g;
//         int b;

//         Color(int r, int g, int b)
//         {
//             this->r = r;
//             this->g = g;
//             this->b = b;
//         }
//         Color()
//         {
//             r = rand() % 256;
//             g = rand() % 256;
//             b = rand() % 256;
//         }
//     };

//     class Vertex3d
//     {
//     public:
//         float x;
//         float y;
//         float z;
//         Color *color;

//         Vertex3d()
//         {
//             this->x = 0.0f;
//             this->y = 0.0f;
//             this->z = 0.0f;
//             this->color = new Color();
//         }
//         Vertex3d(float x, float y, float z)
//         {
//             this->x = x;
//             this->y = y;
//             this->z = z;
//             this->color = new Color();
//         }
//     };

//     // array holding the vertices of the model
//     Vertex3d **vertices;

// public:
//     Egg()
//     {

//         setupVerticesOnPlane();
//         transformVertices();
//     }

//     // Translate the vertices according to a given formula to form an egg shape
//     void transformVertices()
//     {
//         for (int i = 0; i < n * n; ++i)
//         {
//             Vertex3d *vertex = vertices[i];
//             float u = vertex->x;
//             float v = vertex->y;

//             vertex->x = (-90.0 * pow(u, 5) + 225.0 * pow(u, 4) - 270.0 * pow(u, 3) + 180.0 * pow(u, 2) - 45.0 * u) * cos(M_PI * v);
//             vertex->y = (160.0 * pow(u, 4) - 320.0 * pow(u, 3) + 160.0 * pow(u, 2));
//             vertex->z = (-90.0 * pow(u, 5) + 225.0 * pow(u, 4) - 270.0 * pow(u, 3) + 180.0 * pow(u, 2) - 45.0 * u) * sin(M_PI * v);
//         }
//     }

//     // Sets up a 2d plain consisting of n x n vertices.
//     // Each coordinate (x, y, z) has a value >= 0 and <= 1.
//     void setupVerticesOnPlane()
//     {
//         vertices = new Vertex3d *[n * n];

//         for (int i = 0; i < n; ++i)
//         {
//             for (int j = 0; j < n; ++j)
//             {
//                 int index = i + j * n;
//                 vertices[index] = new Vertex3d((float)i / n, (float)j / n, 0.0f);
//             }
//         }
//     }

//     // prints the position of all the vertices to the standard output
//     void printVertices()
//     {
//         for (int i = 0; i < n * n; ++i)
//         {
//             std::cout << "x: " << vertices[i]->x << ", y: " << vertices[i]->y << ", z: " << vertices[i]->z << "\n";
//         }
//     }

//     void displayVertices()
//     {
//         glBegin(GL_POINTS);

//         glColor3ub(255, 255, 255);

//         for (int i = 0; i < n * n; ++i)
//         {
//             Vertex3d *vertex = vertices[i];
//             glVertex3f(vertex->x, vertex->y, vertex->z);
//         }

//         glEnd();
//     }

//     void addVertex(Vertex3d *v)
//     {
//         if (displayColor)
//         {
//             glColor3ub(v->color->r, v->color->g, v->color->b);
//         }
//         else
//         {
//             glColor3ub(255, 255, 255);
//         }
//         glVertex3f(v->x, v->y, v->z);
//     }

//     void displayMesh(GLenum mode)
//     {
//         for (int i = 0; i < n; ++i)
//         {
//             for (int j = 0; j < n; ++j)
//             {
//                 // this vertex
//                 Vertex3d *vertex1 = vertices[j * n + i];
//                 // top neighbor
//                 Vertex3d *vertex2 = vertices[(j + 1) * n + i];
//                 // top-right neighbor
//                 Vertex3d *vertex3 = vertices[(j + 1) * n + (i + 1) % n];
//                 // right neighbor
//                 Vertex3d *vertex4 = vertices[j * n + (i + 1) % n];

//                 // Skip the top row
//                 if (j < n - 1)
//                 {
//                     glBegin(mode);
//                     addVertex(vertex1);
//                     addVertex(vertex2);
//                     addVertex(vertex3);
//                     addVertex(vertex1);
//                     addVertex(vertex4);
//                     addVertex(vertex3);
//                     glEnd();
//                 }
//                 else
//                 // Fill the missing "ring"
//                 {

//                     // top neighbor
//                     Vertex3d *vertex4 = vertices[(n - i)];
//                     // top-right neighbor
//                     Vertex3d *vertex5 = vertices[(n - i - 1)];
//                     // right neighbor
//                     Vertex3d *vertex6 = vertices[j * n + (i + 1) % n];

//                     // line from this to top neighbor
//                     glBegin(mode);
//                     addVertex(vertex1);
//                     addVertex(vertex4);
//                     addVertex(vertex5);
//                     addVertex(vertex1);
//                     addVertex(vertex6);
//                     addVertex(vertex5);
//                     glEnd();
//                 }
//             }
//         }
//     }

//     void displayEgg()
//     {
//         switch (displayMode)
//         {
//         case DisplayMode::vertices:
//             displayVertices();
//             break;
//         case DisplayMode::mesh:
//             displayColor = false;
//             displayMesh(GL_LINE_STRIP);
//             break;
//         case DisplayMode::filledTriangles:
//             displayColor = true;
//             displayMesh(GL_TRIANGLE_STRIP);
//             break;
//         }
//     }
// };