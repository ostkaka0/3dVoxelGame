#pragma once
#ifdef CLIENT

#include "GL.h"
#include "IRenderer.h"
#include "Color.h"

class Game;

class OpenglRenderer : public IRenderer
{
	GLuint MatrixID;
	GLuint VertexArrayID;
public:
	OpenglRenderer(Game *game, int width, int height);
	~OpenglRenderer();

	virtual GLuint LoadShaders(const char *vertexFilePath, const char *fragmentFilePath, const char *geometryFilePath);
#pragma region Matrix initializing
#pragma endregion
#pragma region Matrix rendering
	virtual void PushMatrix();
	virtual void PopMatrix();

	//virtual void PushMatrix(int matrixPtr);
	virtual void DeleteMatrix(GLuint matrixPtr, GLuint size);
	virtual void RenderMatrix(IMatrix* matrix, glm::mat4 MVP) override;
#pragma endregion
#pragma region Matrix modifying
	virtual void Translate(float x, float y, float z);
	virtual void Rotate(float angle, float x, float y, float z);
	virtual void Scale(float x, float y, float z);
	virtual void SetColor(Color color);
#pragma endregion 

	virtual void Clear(GLFWwindow *window);
	virtual void Render(GLFWwindow *window);
};
#endif