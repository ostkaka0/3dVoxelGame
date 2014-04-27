#pragma once
struct Vertex
{
public:
	Vertex(GLfloat x, GLfloat y, GLfloat z) { position[0] = x; position[1] = y; position[2] = z; };

	GLfloat position[3];
	GLfloat normal[3];
	GLubyte color[4];

	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) { color[0] = r; color[1] = g; color[2] = b; color[3] = a; };
};

