#include "DrawableVertexBuffer.h"

DrawableVertexBuffer::DrawableVertexBuffer(GLuint id, GLuint vertices)
	: m_id(id)
	, m_vertices(vertices)
{
}

DrawableVertexBuffer::~DrawableVertexBuffer()
{
	glDeleteBuffers(m_vertices, &m_id);
}

void DrawableVertexBuffer::RenderMatrix(IRenderer *renderer)
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glVertexAttribPointer(
		0,				// attribute 0, must match the shader
		m_vertices,		// size
		GL_FLOAT,		// type
		GL_FALSE,		// normalized?
		0,				// stride
		(void*)0		// array buffer offset
	);

	//Draws the triangles
	glDrawArrays(GL_TRIANGLES, 0, m_vertices);

	glDisableVertexAttribArray(0);
}