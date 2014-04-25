#include <iostream>
#include <typeinfo>
#include "MatrixTerminal.h"

MatrixTerminal::MatrixTerminal()
	: m_vertexBuffer(0)
	, m_size(0)
	, m_changed(true)
	, renderer(nullptr)
{
}

MatrixTerminal::~MatrixTerminal()
{
	if (renderer && m_vertexBuffer)
	{
		renderer->DeleteMatrix(m_vertexBuffer, m_size);
	}
}

void MatrixTerminal::Render(IRenderer *renderer, glm::mat4 MVP)
{
	std::cout << "Unhandeld drawable terminal: " << typeid(*this).name() << std::endl;
}