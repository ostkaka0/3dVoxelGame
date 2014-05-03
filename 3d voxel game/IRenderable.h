#pragma once

#include "GL.h"
#include "ShaderType.h"

class IRenderer;

class IRenderable
{
public:
	virtual ~IRenderable() {}
	virtual bool Render(IRenderer *renderer, glm::mat4 MVP, ShaderType shaderType)=0;
	//virtual ShaderType getShaderType() const=0;
};