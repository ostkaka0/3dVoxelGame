#include <cassert>
#include <iostream>
#include <stdexcept>
#include <typeinfo>

#include "OpenglRenderer.h"
#include "Game.h"

OpenglRenderer::OpenglRenderer(Game *game, int width, int height)
{
	glViewport(0, 0, width, height);
}

OpenglRenderer::~OpenglRenderer()
{

}

#pragma region Matrix initializing
int OpenglRenderer::LoadVoxelMatrix(IMatrix *matrix)
{
	return NULL;
}

void OpenglRenderer::DeleteVoxelMatrix(int matrixPtr)
{

}

#pragma endregion
#pragma region Matrix rendering
void OpenglRenderer::PushMatrix()
{

}

void OpenglRenderer::PopMatrix()
{

}


void OpenglRenderer::PushMatrix(int matrixPtr)
{

}

void OpenglRenderer::RenderMatrix(int matrixPtr)
{

}

#pragma endregion
#pragma region Matrix modifying
void OpenglRenderer::Translate(float x, float y, float z)
{
	glTranslatef(x, y, z);
}

void OpenglRenderer::Rotate(float angle, float x, float y, float z)
{
	glRotatef(angle, x, y, z);
}

void OpenglRenderer::Scale(float x, float y, float z)
{
	glScalef(x, y, z);
}

void OpenglRenderer::SetColor(Color color)
{
	glColor4b(color.red,color.green, color.blue, color.opacity);
}

#pragma endregion 

void OpenglRenderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void OpenglRenderer::Render(GLFWwindow *window)
{
	float ratio;
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float) height;
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
	glBegin(GL_TRIANGLES);
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-0.6f, -0.4f, 0.f);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.4f, 0.f);
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.6f, 0.f);
	glEnd();
	/////////
	glfwSwapBuffers(window);
	/////

	////
	glfwPollEvents();
}