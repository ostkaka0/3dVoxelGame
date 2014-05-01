#pragma once

#include "GL.h"
#include "ShaderType.h"

class IRenderer;

class IRenderable
{
public:
	virtual ~IRenderable() {}
	virtual void Render(IRenderer *renderer, glm::mat4 MVP)=0;
	virtual ShaderType getShaderType() const=0;
};