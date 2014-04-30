#pragma once

#include "GL.h"

class IRenderer;

class IRenderable
{
public:
	virtual ~IRenderable() {}
	virtual void Render(IRenderer *renderer, glm::mat4 MVP)=0;
};