#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <ctime>
#include <string>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#define _USE_MATH_DEFINES

int n = 20;
int windowWidth = 800;
int windowHeight = 800;
static GLfloat theta[] = {0.0, 0.0, 0.0};
int displayMode = 2; // 1 - vertices, 2 - mesh, 3 - filled triangles
int displayColor = false;
class Color
{
public:
	int r;
	int g;
	int b;

	Color(int r, int g, int b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}
	Color()
	{
		r = rand() % 256;
		g = rand() % 256;
		b = rand() % 256;
	}
};

class Vertex3d
{
public:
	float x;
	float y;
	float z;
	Color *color;

	Vertex3d()
	{
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
		this->color = new Color();
	}
	Vertex3d(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->color = new Color();
	}
};

void spinEgg()
{

	const float step = 0.1;

	theta[0] -= step;
	if (theta[0] > 360.0)
		theta[0] -= 360.0;

	theta[1] -= step;
	if (theta[1] > 360.0)
		theta[1] -= 360.0;

	theta[2] -= step;
	if (theta[2] > 360.0)
		theta[2] -= 360.0;

	glutPostRedisplay();
}

// array holding the vertices of the model
Vertex3d **vertices;

// Translate the points according to a given formula to form an egg shape
void transformVertices()
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

// Sets up a 2d plain consisting of n x n vertices.
// Each coordinate (x, y, z) has a value >= 0 and <= 1.
void setupVerticesOnPlane()
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

// prints the position of all the vertices to the standard output
void printVertices()
{
	for (int i = 0; i < n * n; ++i)
	{
		std::cout << "x: " << vertices[i]->x << ", y: " << vertices[i]->y << ", z: " << vertices[i]->z << "\n";
	}
}

void init()
{
	setupVerticesOnPlane();
	// printVertices();
	transformVertices();
	// printVertices();
}

void displayVertices()
{
	glBegin(GL_POINTS);

	for (int i = 0; i < n * n; ++i)
	{
		Vertex3d *vertex = vertices[i];
		glVertex3f(vertex->x, vertex->y, vertex->z);
	}

	glEnd();
}

void addVertex(Vertex3d *v)
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

void displayMesh(GLenum mode)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			// this point
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

void displayEgg()
{
	switch (displayMode)
	{
	case 1:
		displayColor = false;
		displayVertices();
		break;
	case 2:
		displayColor = false;
		displayMesh(GL_LINE_STRIP);
		break;
	case 3:
		displayColor = true;
		displayMesh(GL_TRIANGLE_STRIP);
		break;
	}
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);

	displayEgg();

	glFlush();

	glutSwapBuffers();
}

void changeSize(GLsizei horizontal, GLsizei vertical)
{
	GLfloat AspectRatio;

	if (vertical == 0)
		vertical = 1;

	glViewport(0, 0, horizontal, vertical);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;

	float displaySize = 10.0;
	// float displaySize = 1.0;

	if (horizontal <= vertical)
		glOrtho(-displaySize, displaySize, -displaySize / AspectRatio, displaySize / AspectRatio, displaySize, -displaySize);
	else
		glOrtho(-displaySize * AspectRatio, displaySize * AspectRatio, -displaySize, displaySize, displaySize, -displaySize);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keys(unsigned char key, int x, int y)
{
	if (key == 'p')
		displayMode = 1;
	if (key == 'w')
		displayMode = 2;
	if (key == 's')
		displayMode = 3;

	display();
}

int main(int argc, char *argv[])
{
	for (int i = 1; i < argc; ++i)
	{
		std::string flag = argv[i];

		i++;

		if (flag == "-n" || "--n")
		{
			n = std::stoi(argv[i]);
			continue;
		}
		else if (flag == "--help" || flag == "-h")
		{
			std::cout << "Available flags: \n"
					  << "    --n | -n <number> number of points in width and height\n";
			return 0;
		}
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);

	glutCreateWindow("3D Egg model");

	glutDisplayFunc(display);
	glutReshapeFunc(changeSize);

	init();

	glEnable(GL_DEPTH_TEST);
	glutIdleFunc(spinEgg);
	glutKeyboardFunc(keys);

	glutMainLoop();
	exit(0);
}
