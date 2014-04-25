#include "IDrawable.h"
#include <gl\glew.h>

class DrawableVertexBuffer : public IDrawable
{
	GLuint m_id;
	GLuint m_vertices;
public:
	DrawableVertexBuffer(GLuint id, GLuint vertices);
	~DrawableVertexBuffer();
	virtual void RenderMatrix(IRenderer *renderer);
};