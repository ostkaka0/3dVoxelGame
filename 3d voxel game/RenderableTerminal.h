#pragma once
#include "IRenderable.h"
#include "IRenderer.h"

class RenderableTerminal : public IRenderable
{
public:
	GLuint m_colorVertexbuffer;
	GLuint m_vertexBuffer;
	GLuint m_size;
	bool m_changed;
	IRenderer *renderer;

	//friend void IRenderer::RenderMatrix(IRenderable *matrix);
//public:
	//friend class IRenderer;

	RenderableTerminal();
	virtual ~RenderableTerminal() override;
	virtual void Render(IRenderer *renderer, glm::mat4 MVP);
};