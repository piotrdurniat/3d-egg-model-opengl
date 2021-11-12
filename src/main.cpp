#include "Egg.hpp"

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
#include "DisplayMode.hpp"

Egg *egg;

int n = 20;
int windowWidth = 800;
int windowHeight = 800;
static GLfloat theta[] = {0.0, 0.0, 0.0};

void init()
{
	egg = new Egg(n);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);

	egg->display();

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
	{
		egg->setDisplayMode(DisplayMode::vertices);
	}

	else if (key == 'w')
	{
		egg->setDisplayMode(DisplayMode::mesh);
	}

	else if (key == 's')
	{
		egg->setDisplayMode(DisplayMode::filledTriangles);
	}

	display();
}

void spinModel()
{
	const float step = 0.1;

	theta[0] -= step;
	theta[1] -= step;
	theta[2] -= step;

	glutPostRedisplay();
}

int main(int argc, char *argv[])
{
	for (int i = 1; i < argc; ++i)
	{
		std::string flag = argv[i];

		++i;

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
	glutIdleFunc(spinModel);
	glutKeyboardFunc(keys);

	glutMainLoop();

	delete egg;
	exit(0);
}
