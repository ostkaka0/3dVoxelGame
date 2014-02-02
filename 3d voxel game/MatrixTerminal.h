#pragma once
#include "IMatrix.h"
#include "IRenderer.h"

class MatrixTerminal : public IMatrix
{
public:
	GLuint m_vertexBuffer;
	GLuint m_size;
	bool m_changed;
	IRenderer *renderer;

	//friend void IRenderer::RenderMatrix(IMatrix *matrix);
//public:
	//friend class IRenderer;

	MatrixTerminal();
	~MatrixTerminal();
	virtual void Render(IRenderer *renderer);
};