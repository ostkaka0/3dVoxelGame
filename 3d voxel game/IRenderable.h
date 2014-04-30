#pragma once

#include "GL.h"

class IRenderer;

class IMatrix
{
public:
	virtual void Render(IRenderer *renderer, glm::mat4 MVP)=0;
};