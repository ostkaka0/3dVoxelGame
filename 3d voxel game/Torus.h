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

	virtual bool Render(IRenderer *renderer, glm::mat4 MVP, ShaderType shaderType) override;
	virtual ShaderType getShaderType() const;
};

