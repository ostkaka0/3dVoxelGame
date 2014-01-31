#pragma once

#include "GL.h"
#include "Color.h"

class IMatrix;

class IRenderer
{
public:
#pragma region Matrix initializing
	virtual int LoadVoxelMatrix(IMatrix *matrix)=0;
	virtual void DeleteVoxelMatrix(int matrixPtr)=0;
#pragma endregion
#pragma region Matrix rendering
	virtual void PushMatrix()=0;
	virtual void PopMatrix()=0;

	virtual void PushMatrix(int matrixPtr)=0;
	virtual void RenderMatrix(int matrixPtr)=0;
#pragma endregion
#pragma region Matrix modifying
	virtual void Translate(float x, float y, float z)=0;
	virtual void Rotate(float angle, float x, float y, float z)=0;
	virtual void Scale(float x, float y, float z)=0;
	virtual void SetColor(Color color)=0;
#pragma endregion 

	virtual void Clear()=0;
	virtual void Render(GLFWwindow *window)=0;
};