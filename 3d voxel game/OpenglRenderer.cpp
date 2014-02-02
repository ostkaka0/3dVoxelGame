#ifdef CLIENT
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <typeinfo>

#include "OpenglRenderer.h"
#include "Game.h"
#include "MatrixTerminal.h"
#include "VoxelMatrix.h"

OpenglRenderer::OpenglRenderer(Game *game, int width, int height)
{
	glViewport(0, 0, width, height);
}

OpenglRenderer::~OpenglRenderer()
{
	for (auto i : vertexBuffers)
	{
		DeleteMatrix(i.first, i.second);
	}
}

#pragma region Matrix initializing

#pragma endregion
#pragma region Matrix rendering
void OpenglRenderer::PushMatrix()
{

}

void OpenglRenderer::PopMatrix()
{

}


/*void OpenglRenderer::PushMatrix(int matrixPtr)
{

}*/

void OpenglRenderer::DeleteMatrix(GLuint matrixPtr, GLuint size)
{
	for (auto i = vertexBuffers.begin(); i < vertexBuffers.end(); ++i)
	{
		if (i->first = matrixPtr)
		{
			vertexBuffers.erase(i);
			break;
		}
	}

	glDeleteBuffers(size, &matrixPtr);
}

void OpenglRenderer::RenderMatrix(IMatrix *matrix)
{
	if (MatrixTerminal *mt = dynamic_cast<MatrixTerminal*>(matrix))
	{
		if (mt->m_changed)
		{
			if (mt->m_vertexBuffer)
				DeleteMatrix(mt->m_vertexBuffer, mt->m_size);

			if (typeid(*mt) == typeid(VoxelMatrix))
			{
				VoxelMatrix *matrix = reinterpret_cast<VoxelMatrix*>(mt);

				GLuint vertexbuffer;

				// Generate 1 buffer, put the resulting identifier in vertexbuffer
				glGenBuffers(1, &vertexbuffer);

				// The following commands will talk about our 'vertexbuffer' buffer
				glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

				std::vector<GLfloat> g_vertex_buffer_data;
				g_vertex_buffer_data.reserve(matrix->m_width*matrix->m_height*matrix->m_depth*9*6);


				for (int x = 0; x < matrix->m_width; x++)
				{
					for (int y = 0; y < matrix->m_height; y++)
					{
						for (int z = 0; z < matrix->m_depth; z++)
						{
							if (matrix->getVoxel(x, y, z) == 0)
								continue;
#pragma region cube
							g_vertex_buffer_data.push_back(x-0.5F);
							g_vertex_buffer_data.push_back(y-0.5F);
							g_vertex_buffer_data.push_back(z-0.5F);

							g_vertex_buffer_data.push_back(x-0.5F);
							g_vertex_buffer_data.push_back(y+0.5F);
							g_vertex_buffer_data.push_back(z-0.5F);

							g_vertex_buffer_data.push_back(x-0.5F);
							g_vertex_buffer_data.push_back(y-0.5F);
							g_vertex_buffer_data.push_back(z+0.5F);
							///
							g_vertex_buffer_data.push_back(x-0.5F);
							g_vertex_buffer_data.push_back(y-0.5F);
							g_vertex_buffer_data.push_back(z-0.5F);

							g_vertex_buffer_data.push_back(x-0.5F);
							g_vertex_buffer_data.push_back(y-0.5F);
							g_vertex_buffer_data.push_back(z+0.5F);

							g_vertex_buffer_data.push_back(x-0.5F);
							g_vertex_buffer_data.push_back(y+0.5F);
							g_vertex_buffer_data.push_back(z-0.5F);



							g_vertex_buffer_data.push_back(x-0.5F);
							g_vertex_buffer_data.push_back(y-0.5F);
							g_vertex_buffer_data.push_back(z-0.5F);

							g_vertex_buffer_data.push_back(x+0.5F);
							g_vertex_buffer_data.push_back(y-0.5F);
							g_vertex_buffer_data.push_back(z-0.5F);

							g_vertex_buffer_data.push_back(x-0.5F);
							g_vertex_buffer_data.push_back(y-0.5F);
							g_vertex_buffer_data.push_back(z+0.5F);
							///
							g_vertex_buffer_data.push_back(x-0.5F);
							g_vertex_buffer_data.push_back(y-0.5F);
							g_vertex_buffer_data.push_back(z-0.5F);

							g_vertex_buffer_data.push_back(x-0.5F);
							g_vertex_buffer_data.push_back(y-0.5F);
							g_vertex_buffer_data.push_back(z+0.5F);

							g_vertex_buffer_data.push_back(x+0.5F);
							g_vertex_buffer_data.push_back(y-0.5F);
							g_vertex_buffer_data.push_back(z-0.5F);



							g_vertex_buffer_data.push_back(x-0.5F);
							g_vertex_buffer_data.push_back(y-0.5F);
							g_vertex_buffer_data.push_back(z-0.5F);

							g_vertex_buffer_data.push_back(x+0.5F);
							g_vertex_buffer_data.push_back(y-0.5F);
							g_vertex_buffer_data.push_back(z-0.5F);

							g_vertex_buffer_data.push_back(x-0.5F);
							g_vertex_buffer_data.push_back(y+0.5F);
							g_vertex_buffer_data.push_back(z-0.5F);
							///
							g_vertex_buffer_data.push_back(x-0.5F);
							g_vertex_buffer_data.push_back(y-0.5F);
							g_vertex_buffer_data.push_back(z-0.5F);

							g_vertex_buffer_data.push_back(x-0.5F);
							g_vertex_buffer_data.push_back(y+0.5F);
							g_vertex_buffer_data.push_back(z-0.5F);

							g_vertex_buffer_data.push_back(x-0.5F);
							g_vertex_buffer_data.push_back(y-0.5F);
							g_vertex_buffer_data.push_back(z+0.5F);

							////////////

							g_vertex_buffer_data.push_back(x+0.5F);
							g_vertex_buffer_data.push_back(y+0.5F);
							g_vertex_buffer_data.push_back(z+0.5F);

							g_vertex_buffer_data.push_back(x+0.5F);
							g_vertex_buffer_data.push_back(y-0.5F);
							g_vertex_buffer_data.push_back(z+0.5F);

							g_vertex_buffer_data.push_back(x+0.5F);
							g_vertex_buffer_data.push_back(y+0.5F);
							g_vertex_buffer_data.push_back(z-0.5F);
							///
							g_vertex_buffer_data.push_back(x+0.5F);
							g_vertex_buffer_data.push_back(y+0.5F);
							g_vertex_buffer_data.push_back(z+0.5F);

							g_vertex_buffer_data.push_back(x+0.5F);
							g_vertex_buffer_data.push_back(y+0.5F);
							g_vertex_buffer_data.push_back(z-0.5F);

							g_vertex_buffer_data.push_back(x+0.5F);
							g_vertex_buffer_data.push_back(y-0.5F);
							g_vertex_buffer_data.push_back(z+0.5F);



							g_vertex_buffer_data.push_back(x+0.5F);
							g_vertex_buffer_data.push_back(y+0.5F);
							g_vertex_buffer_data.push_back(z+0.5F);

							g_vertex_buffer_data.push_back(x-0.5F);
							g_vertex_buffer_data.push_back(y+0.5F);
							g_vertex_buffer_data.push_back(z+0.5F);

							g_vertex_buffer_data.push_back(x+0.5F);
							g_vertex_buffer_data.push_back(y+0.5F);
							g_vertex_buffer_data.push_back(z-0.5F);
							///
							g_vertex_buffer_data.push_back(x+0.5F);
							g_vertex_buffer_data.push_back(y+0.5F);
							g_vertex_buffer_data.push_back(z+0.5F);

							g_vertex_buffer_data.push_back(x+0.5F);
							g_vertex_buffer_data.push_back(y+0.5F);
							g_vertex_buffer_data.push_back(z-0.5F);

							g_vertex_buffer_data.push_back(x-0.5F);
							g_vertex_buffer_data.push_back(y+0.5F);
							g_vertex_buffer_data.push_back(z+0.5F);



							g_vertex_buffer_data.push_back(x+0.5F);
							g_vertex_buffer_data.push_back(y+0.5F);
							g_vertex_buffer_data.push_back(z+0.5F);

							g_vertex_buffer_data.push_back(x-0.5F);
							g_vertex_buffer_data.push_back(y+0.5F);
							g_vertex_buffer_data.push_back(z+0.5F);

							g_vertex_buffer_data.push_back(x+0.5F);
							g_vertex_buffer_data.push_back(y-0.5F);
							g_vertex_buffer_data.push_back(z+0.5F);
							///
							g_vertex_buffer_data.push_back(x+0.5F);
							g_vertex_buffer_data.push_back(y+0.5F);
							g_vertex_buffer_data.push_back(z+0.5F);

							g_vertex_buffer_data.push_back(x+0.5F);
							g_vertex_buffer_data.push_back(y-0.5F);
							g_vertex_buffer_data.push_back(z+0.5F);

							g_vertex_buffer_data.push_back(x-0.5F);
							g_vertex_buffer_data.push_back(y+0.5F);
							g_vertex_buffer_data.push_back(z+0.5F);
#pragma endregion
						}
					}
				}


				// Give our vertices to OpenGL.
				glBufferData(GL_ARRAY_BUFFER, g_vertex_buffer_data.size(), &g_vertex_buffer_data[0], GL_STATIC_DRAW);

				matrix->m_vertexBuffer = vertexbuffer;
				matrix->m_size = g_vertex_buffer_data.size();
				matrix->m_changed = false;

				vertexBuffers.push_back(std::pair<GLuint, GLuint>(vertexbuffer, g_vertex_buffer_data.size()));

			}
		}

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, mt->m_vertexBuffer);
		glVertexAttribPointer(
			0,				// attribute 0, must match the shader
			mt->m_size,		// size
			GL_FLOAT,		// type
			GL_FALSE,		// normalized?
			0,				// stride
			(void*)0		// array buffer offset
			);

		//Draws the triangles
		glDrawArrays(GL_TRIANGLES, 0, mt->m_size);

		glDisableVertexAttribArray(0);
	}
	else
	{
		matrix->Render(this);
	}
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
#endif