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
//	virtual void PushMatrix() override;
//	virtual void PopMatrix() override;

	//virtual void PushMatrix(int matrixPtr);
	virtual void DeleteMatrix(GLuint matrixPtr, GLuint size) override;
	virtual void RenderMatrix(IRenderable *matrix, glm::mat4 MVP) override;
#pragma endregion
#pragma region Matrix modifying
	/*virtual void Translate(float x, float y, float z) override;
	virtual void Rotate(float angle, float x, float y, float z) override;
	virtual void Scale(float x, float y, float z) override;
	virtual void SetColor(Color color) override;*/
#pragma endregion 

	virtual void Clear(GLFWwindow *window) override;
	virtual void Render(GLFWwindow *window) override;
};
#endif