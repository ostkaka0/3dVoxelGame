#pragma once
#include "IRenderable.h"
#include "IRenderer.h"

class RenderableTerminal : public IRenderable
{
protected:
	GLuint m_colorVertexbuffer;
	GLuint m_vertexBuffer;
	GLuint m_size;
	bool m_changed;
	IRenderer *renderer;

public:

	//friend void IRenderer::RenderMatrix(IRenderable *matrix);
//public:
	//friend class IRenderer;

	RenderableTerminal();

	virtual ~RenderableTerminal() override;

	bool isChanged();

	//virtual void Render(IRenderer *renderer, glm::mat4 MVP, ShaderType shaderType);
};