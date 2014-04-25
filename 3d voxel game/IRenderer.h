#pragma once
#ifdef CLIENT

#include <vector>

#include "GL.h"
#include "Color.h"

class IMatrix;

class IRenderer
{
protected:
	std::vector<std::pair<GLuint,GLuint>> vertexBuffers;

public:
	virtual GLuint LoadShaders(const char *vertexFilePath, const char *fragmentFilePath)=0;
#pragma region Matrix initializing
#pragma endregion
#pragma region Matrix rendering
	virtual void PushMatrix()=0;
	virtual void PopMatrix()=0;

	//virtual void PushMatrix(IMatrix *matrix)=0;
	virtual void DeleteMatrix(GLuint matrixPtr, GLuint size)=0;
	virtual void RenderMatrix(IMatrix* matrix, glm::mat4 MVP)=0;
#pragma endregion
#pragma region Matrix modifying
	virtual void Translate(float x, float y, float z)=0;
	virtual void Rotate(float angle, float x, float y, float z)=0;
	virtual void Scale(float x, float y, float z)=0;
	virtual void SetColor(Color color)=0;
#pragma endregion 

	virtual void Clear(GLFWwindow *window)=0;
	virtual void Render(GLFWwindow *window)=0;
};
#endif