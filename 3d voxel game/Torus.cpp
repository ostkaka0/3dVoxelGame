#include "Torus.h"


Torus::Torus(void)
	:texture("Jellyfish.bmp")
{
}


Torus::~Torus(void)
{
}

ShaderType Torus::getShaderType() const
{
	return SHADER_SPACE;
}
