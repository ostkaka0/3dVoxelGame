#ifdef _WIN32
#include <Windows.h>
#elif defined linux

#endif

#include <iostream>

#include <GL\GL.h>
#include <GL\GLU.h>
#include <GL\glut.h>

#include "Octree.h"

int main(int argc, char **argv)
{
	Octree<int,16> octree;

	//for (int i = 0; i < 64; i++)
	//	std::cout << i << ": " << octree[i] << std::endl;

	octree[1] = &octree;

	std::cin.get();

	for (int i = 0; i < 64; i++)
		std::cout << i << ": " << octree[i].element << std::endl;

	std::cout << octree[1337].element;
	std::cin.get();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Voxicron?");

    glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(Display);
	glutIdleFunc(Idle);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);

	glClearColor(0.125, 0.125, 0.125, 1.0);
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION,  lightposition);
	glLightfv(GL_LIGHT0, GL_AMBIENT,  muljus);

	return 0;
}