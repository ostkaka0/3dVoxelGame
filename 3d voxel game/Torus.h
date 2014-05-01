#pragma once
#include "RenderableTerminal.h"
#include "Texture.h"

class Torus : public RenderableTerminal
{
protected:
	
public:
	Texture texture;

	Torus(void);
	virtual ~Torus(void);

	virtual ShaderType getShaderType() const override;
};

