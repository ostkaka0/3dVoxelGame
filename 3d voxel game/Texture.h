#pragma once

#include <iostream>
#include <string>
#include "GL.h"

class Texture
{
protected:
	GLuint textureID;

	unsigned int height;
	unsigned int width;
	unsigned int linearSize;
	unsigned int mipMapCount;
	unsigned int fourCC;

 
	//unsigned char * buffer;
	//unsigned int bufsize;
public:
	Texture(std::string name);
	virtual ~Texture(void);

	unsigned int getWidth();
	unsigned int getHeight();
	GLuint getTextureId();
};

