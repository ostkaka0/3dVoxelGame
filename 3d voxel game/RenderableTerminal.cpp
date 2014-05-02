#include <iostream>
#include <typeinfo>
#include "RenderableTerminal.h"

RenderableTerminal::RenderableTerminal()
	: m_vertexBuffer(0)
	, m_size(0)
	, m_changed(true)
	, renderer(nullptr)
{
}

RenderableTerminal::~RenderableTerminal()
{
	if (renderer && m_vertexBuffer)
	{
		renderer->DeleteMatrix(m_vertexBuffer, m_size);
	}
}

bool RenderableTerminal::isChanged()
{
	return m_changed;
}

/*void RenderableTerminal::Render(IRenderer *renderer, glm::mat4 MVP, ShaderType shaderType)
{
	std::cout << "Unhandeld drawable terminal: " << typeid(*this).name() << std::endl;
}*/