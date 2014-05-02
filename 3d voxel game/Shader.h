#pragma once

#include <string>
#include <gl\glew.h>
#include <glm\gtc\matrix_transform.hpp>

class Shader
{
private:
	// vertex shader + fragment shader + geometry shader
	static const unsigned int NUM_SHADERS = 3; 

	//GLint m_matrixId;
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLint *m_uniforms;
	//const ShaderType shaderType;

	Shader(const Shader &other) {};
	Shader &operator=(const Shader &other) {};

	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, GLenum type);

protected:
public:
	Shader(const std::string &fileName, const std::string *uniforms);
	virtual ~Shader(void);

	void Bind();
	void Update(const glm::mat4 &MVP);
	GLint getMatrixId() { return m_uniforms[0]; };
	GLint getUniform(const int index);
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

