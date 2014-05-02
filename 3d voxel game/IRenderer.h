#pragma once
#ifdef CLIENT

#include <vector>
#include <glm\glm.hpp>

#include "GL.h"
#include "Color.h"
#include "ShaderType.h"


class IRenderable;
class Shader;

class IRenderer
{
protected:
	std::vector<std::pair<GLuint,GLuint>> vertexBuffers;

public:
	//virtual GLuint LoadShaders(const char *vertexFilePath, const char *fragmentFilePath, const char *geometryFilePath)=0;
#pragma region Matrix initializing
#pragma endregion
#pragma region Matrix rendering
//	virtual void PushMatrix()=0;
//	virtual void PopMatrix()=0;

	//virtual void PushMatrix(IRenderable *matrix)=0;
	virtual void DeleteMatrix(GLuint matrixPtr, GLuint size)=0;
	virtual void RenderMatrix(IRenderable *matrix, glm::mat4 MVP, ShaderType shaderType)=0;
#pragma endregion
#pragma region Matrix modifying
	/*virtual void Translate(float x, float y, float z)=0;
	virtual void Rotate(float angle, float x, float y, float z)=0;
	virtual void Scale(float x, float y, float z)=0;
	virtual void SetColor(Color color)=0;*/
#pragma endregion 

	virtual void Clear(GLFWwindow *window)=0;
	virtual void Render(GLFWwindow *window)=0;

	virtual Shader *getShader(ShaderType shaderType)=0;
};
#endif