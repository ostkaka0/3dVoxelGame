#pragma once

#include <string>
#include <gl\glew.h>

class Shader
{
private:
	// vertex shader + fragment shader
	static const unsigned int NUM_SHADERS = 2; 

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];

	Shader(const Shader &other) {};
	Shader &operator=(const Shader &other) {};

	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);

protected:
public:
	Shader(const std::string &fileName);
	virtual ~Shader(void);

	void Bind();
};




// bra kod att ta:
// https://github.com/BennyQBD/ModernOpenGLTutorial
/*
#ifndef SHADER_INCLUDED_H
#define SHADER_INCLUDED_H

#include <string>
#include <GL/glew.h>
#include "transform.h"

class Shader
{
public:
	Shader(const std::string& fileName);

	void Bind();
	void Update(const Transform& transform, const Camera& camera);

	virtual ~Shader();
protected:
private:
	static const unsigned int NUM_SHADERS = 2;
	static const unsigned int NUM_UNIFORMS = 3;
	void operator=(const Shader& shader) {}
	Shader(const Shader& shader) {}

	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};

#endif*/
