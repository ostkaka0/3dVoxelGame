#ifdef CLIENT
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <typeinfo>
#include <fstream>
#include <string>
#include <math.h>

#include "OpenglRenderer.h"
#include "Game.h"
#include "MatrixTerminal.h"
#include "VoxelMatrix.h"

OpenglRenderer::OpenglRenderer(Game *game, int width, int height)
{
	glViewport(0, 0, width, height);
	glClearColor(0, 0, 255, 255);

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	glEnableVertexAttribArray(0);
}

OpenglRenderer::~OpenglRenderer()
{
	for (auto i : vertexBuffers)
	{
		DeleteMatrix(i.first, i.second);
	}

	glDeleteVertexArrays(1, &VertexArrayID);
}

GLuint OpenglRenderer::LoadShaders(const char *vertexFilePath, const char *fragmentFilePath)
{
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertexFilePath, std::ios::in);
	if(VertexShaderStream.is_open())
	{
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragmentFilePath, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertexFilePath);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> VertexShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragmentFilePath);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

	// Link the program
	fprintf(stdout, "Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ProgramErrorMessage(std::max(InfoLogLength, int(1)) );
	glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	glUseProgram(ProgramID);

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(ProgramID, "MVP");

	return ProgramID;
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

void OpenglRenderer::RenderMatrix(IMatrix *matrix, glm::mat4 MVP)
{
	GLenum error;

	if (MatrixTerminal *mt = dynamic_cast<MatrixTerminal*>(matrix))
	{
		if (mt->m_changed)
		{
			if (mt->m_vertexBuffer)
				DeleteMatrix(mt->m_vertexBuffer, mt->m_size);

			if (typeid(*mt) == typeid(VoxelMatrix))
			{
				VoxelMatrix *matrix = reinterpret_cast<VoxelMatrix*>(mt);

				error = glGetError();

				GLuint vertexbuffer;
				glGenBuffers(1, &vertexbuffer);
				glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
				error = glGetError();

				std::vector<GLfloat> g_vertex_buffer_data;
				g_vertex_buffer_data.reserve(matrix->m_width*matrix->m_height*matrix->m_depth*9*6);


				for (int x = 0; x < matrix->m_width; x++)
				{
					for (int y = 0; y < matrix->m_height; y++)
					{
						for (int z = 0; z < matrix->m_depth; z++)
						{
							if (x!=1 || y!= 0 || z != 0)
								continue;
							if (matrix->getVoxel(x, y, z) == 0 && false)
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

				error = glGetError();
				// Give our vertices to OpenGL.
				glBufferData(GL_ARRAY_BUFFER, g_vertex_buffer_data.size(), &g_vertex_buffer_data[0], GL_STATIC_DRAW);
				error = glGetError();
				matrix->m_vertexBuffer = vertexbuffer;
				matrix->m_size = g_vertex_buffer_data.size();
				matrix->m_changed = false;

				vertexBuffers.push_back(std::pair<GLuint, GLuint>(vertexbuffer, g_vertex_buffer_data.size()));

			}
		}

		std::cout << mt->m_vertexBuffer << mt->m_changed << std::endl;

		//glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		error = glGetError();
		glEnableVertexAttribArray(0);
		error = glGetError();
		
		
		glBindBuffer(GL_ARRAY_BUFFER, mt->m_vertexBuffer);
		error = glGetError();
		glVertexAttribPointer(
			0,				// attribute 0, must match the shader
			mt->m_size,		// size
			GL_FLOAT,		// type
			GL_FALSE,		// normalized?
			0,				// stride
			(void*)0		// array buffer offset
			);

		error = glGetError();
		//Draws the triangles
		//glDrawArrays(GL_TRIANGLES, 0, mt->m_size);

		error = glGetError();
		glDisableVertexAttribArray(0);
		error = glGetError();
	}
	else
	{
		matrix->Render(this, MVP);
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

void OpenglRenderer::Clear(GLFWwindow *window)
{

	float ratio;
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float) height;
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

}

void OpenglRenderer::Render(GLFWwindow *window)
{
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();


	glRotatef((float) glfwGetTime() * 500.f, 0.f, 1.f, 0.f);
	//glTranslatef(0.f, 0.f, 1.125f);

	glBegin(GL_TRIANGLES);
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-0.6f, -0.4f, 0.f);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.4f, 0.f);
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.6f, 0.f);
	glEnd();

	/*float ratio;
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
	glEnd();*/
	/////////
	glfwSwapBuffers(window);
	/////

	////
	glfwPollEvents();
}
#endif