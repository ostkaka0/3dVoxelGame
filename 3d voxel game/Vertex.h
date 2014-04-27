#pragma once
struct Vertex
{
	GLfloat color[3];
	GLfloat position[3];
	//GLfloat normal[3];
	
	Vertex(GLfloat x, GLfloat y, GLfloat z)
	{
		position[0] = x;
		position[1] = y;
		position[2] = z;

		color[0] = 1.f;
		color[1] = 0.f;
		color[2] = 0.f;
	}

		Vertex(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.f)
	{
		position[0] = x;
		position[1] = y;
		position[2] = z;

		color[0] = r;
		color[1] = g;
		color[2] = b;
		//color[3] = a;
	}

	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
	{
		color[0] = r;
		color[1] = g;
		color[2] = b;
		//color[3] = a;
	}
};

