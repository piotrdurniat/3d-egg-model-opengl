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

// int n = 20;
// int windowWidth = 800;
// int windowHeight = 800;

// static GLfloat theta[] = {0.0, 0.0, 0.0};

// void spinEgg()
// {

// 	theta[0] -= 0.5;
// 	if (theta[0] > 360.0)
// 		theta[0] -= 360.0;

// 	theta[1] -= 0.5;
// 	if (theta[1] > 360.0)
// 		theta[1] -= 360.0;

// 	theta[2] -= 0.5;
// 	if (theta[2] > 360.0)
// 		theta[2] -= 360.0;

// 	glutPostRedisplay(); //odświeżenie zawartości aktualnego okna
// }
// // array holding the vertices of the model
// float **vertices;

// // Translate the points to form an egg shape
// void transformVertices()
// {
// 	for (int i = 0; i < n; ++i)
// 	{
// 		float u = float(i) / n;
// 		for (int j = 0; j < n; ++j)
// 		{
// 			float v = float(j) / n;

// 			double pi = 2 * acos(0.0);

// 			int index = i * n + j;
// 			vertices[index][0] = (-90.0 * pow(u, 5) + 225.0 * pow(u, 4) - 270.0 * pow(u, 3) + 180.0 * pow(u, 2) - 45.0 * u) * cos(M_PI * v);
// 			vertices[index][1] = (160.0 * pow(u, 4) - 320.0 * pow(u, 3) + 160.0 * pow(u, 2));
// 			vertices[index][2] = (-90.0 * pow(u, 5) + 225.0 * pow(u, 4) - 270.0 * pow(u, 3) + 180.0 * pow(u, 2) - 45.0 * u) * sin(M_PI * v);
// 		}
// 	}
// }

// // Sets up a 2d plain consisting of n x n points. 0 <= x <= 1 and 0 <= y <= 1, z = 0;
// void setupVerticesOnPlane()
// {

// 	vertices = new float *[n * n];

// 	for (int i = 0; i < n; i++)
// 	{
// 		for (int j = 0; j < n; j++)
// 		{
// 			int index = i * n + j;
// 			vertices[index] = new float[3];

// 			vertices[index][0] = (float)i / n;
// 			vertices[index][1] = (float)j / n;
// 			vertices[index][2] = 0.0f;
// 		}
// 	}
// }

// // prints the position of all the vertices to the standard output
// void printVertices()
// {
// 	for (int i = 0; i < n * n; i++)
// 	{
// 		std::cout << "x: " << vertices[i][0] << ", y: " << vertices[i][1] << ", z: " << vertices[i][2] << "\n";
// 	}
// }

// void init()
// {
// 	setupVerticesOnPlane();
// 	printVertices();
// 	transformVertices();
// 	printVertices();
// }

// void displayEgg()
// {

// 	// glRotated(30.0, 1.0, 1.0, 1.0);

// 	glBegin(GL_POINTS);

// 	for (int i = 0; i < n * n; ++i)
// 	{
// 		float *vertex = vertices[i];
// 		glVertex3fv(vertex);
// 	}

// 	glEnd();
// }

// void display(void)
// {
// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 	glLoadIdentity();

// 	displayEgg();

// 	glFlush();

// 	glutSwapBuffers();
// }

// void changeSize(GLsizei horizontal, GLsizei vertical)
// {
// 	GLfloat AspectRatio;

// 	if (vertical == 0)
// 		vertical = 1;

// 	glViewport(0, 0, horizontal, vertical);

// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();

// 	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;

// 	float displaySize = 10.0;

// 	if (horizontal <= vertical)
// 		glOrtho(-displaySize, displaySize, -displaySize / AspectRatio, displaySize / AspectRatio, displaySize, -displaySize);
// 	else
// 		glOrtho(-displaySize * AspectRatio, displaySize * AspectRatio, -displaySize, displaySize, displaySize, -displaySize);

// 	glMatrixMode(GL_MODELVIEW);
// 	glLoadIdentity();
// }

// int main(int argc, char *argv[])
// {
// 	for (int i = 1; i < argc; ++i)
// 	{
// 		std::string flag = argv[i];

// 		i++;

// 		if (flag == "-n" || "--n")
// 		{
// 			n = std::stoi(argv[i]);
// 			continue;
// 		}
// 		else if (flag == "--help" || flag == "-h")
// 		{
// 			std::cout << "Available flags: \n"
// 					  << "    --n | -n <number> number of points in width and height\n";
// 			return 0;
// 		}
// 	}

// 	glutInit(&argc, argv);
// 	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
// 	glutInitWindowSize(windowWidth, windowHeight);

// 	glutCreateWindow("3D Egg model");

// 	glutDisplayFunc(display);
// 	glutReshapeFunc(changeSize);

// 	init();

// 	glEnable(GL_DEPTH_TEST);

// 	glutMainLoop();
// 	exit(0);
// }
