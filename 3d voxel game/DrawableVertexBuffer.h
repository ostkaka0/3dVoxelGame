#include "IDrawable.h"
#include "GL.h"

class DrawableVertexBuffer : public IDrawable
{
	GLuint m_id;
	GLuint m_vertices;
public:
	DrawableVertexBuffer(GLuint id, GLuint vertices);
	~DrawableVertexBuffer();
	virtual void RenderMatrix(IRenderer *renderer);
};