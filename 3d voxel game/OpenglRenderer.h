#pragma once

#include "GL.h"
#include "IRenderer.h"
#include "Color.h"

class Game;

class OpenglRenderer : public IRenderer
{
public:
	OpenglRenderer(Game *game, int width, int height);
	~OpenglRenderer();
#pragma region Matrix initializing
	virtual int LoadVoxelMatrix(IMatrix *matrix);
	virtual void DeleteVoxelMatrix(int matrixPtr);
#pragma endregion
#pragma region Matrix rendering
	virtual void PushMatrix();
	virtual void PopMatrix();

	virtual void PushMatrix(int matrixPtr);
	virtual void RenderMatrix(int matrixPtr);
#pragma endregion
#pragma region Matrix modifying
	virtual void Translate(float x, float y, float z);
	virtual void Rotate(float angle, float x, float y, float z);
	virtual void Scale(float x, float y, float z);
	virtual void SetColor(Color color);
#pragma endregion 

	virtual void Clear();
	virtual void Render(GLFWwindow *window);
};