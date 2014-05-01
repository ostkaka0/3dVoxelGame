#pragma once
#include "GL.h"

struct Vertex2
{
	GLfloat UV[3];
	GLfloat position[3];
	//GLfloat normal[3];

	Vertex2(GLfloat x, GLfloat y, GLfloat z, GLfloat UVX, GLfloat UVY)
	{
		position[0] = x;
		position[1] = y;
		position[2] = z;

		UV[0] = UVX;
		UV[1] = UVY;
		//color[3] = a;
	}
};

