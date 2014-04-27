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
#include "Vertex.h"

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

GLuint OpenglRenderer::LoadShaders(const char *vertexFilePath, const char *fragmentFilePath, const char *geometryFilePath)
{
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint GeometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);

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

	// Read the Geometry Shader code from the file
	std::string GeometryShaderCode;
	std::ifstream GeometryShaderStream(geometryFilePath, std::ios::in);
	if(GeometryShaderStream.is_open()){
		std::string Line = "";
		while(getline(GeometryShaderStream, Line))
			GeometryShaderCode += "\n" + Line;
		GeometryShaderStream.close();
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

	// Compile Geometry Shader
	printf("Compiling shader : %s\n", geometryFilePath);
	char const * GeometrySourcePointer = GeometryShaderCode.c_str();
	glShaderSource(GeometryShaderID, 1, &GeometrySourcePointer , NULL);
	glCompileShader(GeometryShaderID);

	// Check Geometry Shader
	glGetShaderiv(GeometryShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(GeometryShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> GeometryShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(GeometryShaderID, InfoLogLength, NULL, &GeometryShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &GeometryShaderErrorMessage[0]);

	// Link the program
	fprintf(stdout, "Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glAttachShader(ProgramID, GeometryShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ProgramErrorMessage(std::max(InfoLogLength, int(1)) );
	glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	glDeleteShader(GeometryShaderID);

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(ProgramID, "MVP");

	glUseProgram(ProgramID);

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

				GLuint vertexbuffer;
				glGenBuffers(1, &vertexbuffer);
				glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

				//GLuint colorVertexbuffer;
				//glGenBuffers(1, &colorVertexbuffer);
				//glBindBuffer(GL_ARRAY_BUFFER, colorVertexbuffer);

				std::vector<Vertex> g_vertex_buffer_data;
				g_vertex_buffer_data.reserve(3*2*6 * matrix->m_width*matrix->m_height*matrix->m_depth); // för att snabba på!
				//g_vertex_buffer_data.reserve(3);
				//g_vertex_buffer_data.reserve(matrix->m_width*matrix->m_height*matrix->m_depth*9*6);


				for (int x = 0; x < matrix->m_width; x++)
				{
					for (int y = 0; y < matrix->m_height; y++)
					{
						for (int z = 0; z < matrix->m_depth; z++)
						{
							//if (x!=0 || y!= 0 || z != 0)
							//continue;
							if (matrix->getVoxel(x, y, z) == 0)
								continue;
#pragma region cube
							///////////////////////////////////////////////////////////////
							//// skrev denna kod helt manuellt efter att jag bytte till Vertex-object
							///////////////////////////////////////////////////////////////


							//mittentriangel för att se ungefär var (0, 0, 0) är
							/*g_vertex_buffer_data.push_back(Vertex(x-0.1F, y-0.1F, z-0.0F));
							g_vertex_buffer_data.push_back(Vertex(x+0.1F, y-0.0F, z-0.0F));
							g_vertex_buffer_data.push_back(Vertex(x-0.0F, y+0.1F, z-0.0F));*/

							g_vertex_buffer_data.push_back(Vertex(x, y, z));

							/*g_vertex_buffer_data.push_back(Vertex(x-0.5F, y-0.5F, z-0.5F));
							g_vertex_buffer_data.push_back(Vertex(x-0.5F, y+0.5F, z-0.5F));
							g_vertex_buffer_data.push_back(Vertex(x+0.5F, y-0.5F, z-0.5F));

							g_vertex_buffer_data.push_back(Vertex(x+0.5F, y+0.5F, z-0.5F));
							g_vertex_buffer_data.push_back(Vertex(x-0.5F, y+0.5F, z-0.5F));
							g_vertex_buffer_data.push_back(Vertex(x+0.5F, y-0.5F, z-0.5F));


							g_vertex_buffer_data.push_back(Vertex(x-0.5F, y-0.5F, z+0.5F));
							g_vertex_buffer_data.push_back(Vertex(x-0.5F, y+0.5F, z+0.5F));
							g_vertex_buffer_data.push_back(Vertex(x+0.5F, y-0.5F, z+0.5F));

							g_vertex_buffer_data.push_back(Vertex(x+0.5F, y+0.5F, z+0.5F));
							g_vertex_buffer_data.push_back(Vertex(x-0.5F, y+0.5F, z+0.5F));
							g_vertex_buffer_data.push_back(Vertex(x+0.5F, y-0.5F, z+0.5F));




							g_vertex_buffer_data.push_back(Vertex(x-0.5F, y-0.5F, z-0.5F));
							g_vertex_buffer_data.push_back(Vertex(x-0.5F, y-0.5F, z+0.5F));
							g_vertex_buffer_data.push_back(Vertex(x-0.5F, y+0.5F, z-0.5F));

							g_vertex_buffer_data.push_back(Vertex(x-0.5F, y+0.5F, z+0.5F));
							g_vertex_buffer_data.push_back(Vertex(x-0.5F, y-0.5F, z+0.5F));
							g_vertex_buffer_data.push_back(Vertex(x-0.5F, y+0.5F, z-0.5F));


							g_vertex_buffer_data.push_back(Vertex(x+0.5F, y-0.5F, z-0.5F));
							g_vertex_buffer_data.push_back(Vertex(x+0.5F, y-0.5F, z+0.5F));
							g_vertex_buffer_data.push_back(Vertex(x+0.5F, y+0.5F, z-0.5F));

							g_vertex_buffer_data.push_back(Vertex(x+0.5F, y+0.5F, z+0.5F));
							g_vertex_buffer_data.push_back(Vertex(x+0.5F, y-0.5F, z+0.5F));
							g_vertex_buffer_data.push_back(Vertex(x+0.5F, y+0.5F, z-0.5F));





							g_vertex_buffer_data.push_back(Vertex(x-0.5F, y-0.5F, z-0.5F));
							g_vertex_buffer_data.push_back(Vertex(x+0.5F, y-0.5F, z-0.5F));
							g_vertex_buffer_data.push_back(Vertex(x-0.5F, y-0.5F, z+0.5F));

							g_vertex_buffer_data.push_back(Vertex(x+0.5F, y-0.5F, z+0.5F));
							g_vertex_buffer_data.push_back(Vertex(x+0.5F, y-0.5F, z-0.5F));
							g_vertex_buffer_data.push_back(Vertex(x-0.5F, y-0.5F, z+0.5F));


							g_vertex_buffer_data.push_back(Vertex(x-0.5F, y+0.5F, z-0.5F));
							g_vertex_buffer_data.push_back(Vertex(x+0.5F, y+0.5F, z-0.5F));
							g_vertex_buffer_data.push_back(Vertex(x-0.5F, y+0.5F, z+0.5F));

							g_vertex_buffer_data.push_back(Vertex(x+0.5F, y+0.5F, z+0.5F));
							g_vertex_buffer_data.push_back(Vertex(x+0.5F, y+0.5F, z-0.5F));
							g_vertex_buffer_data.push_back(Vertex(x-0.5F, y+0.5F, z+0.5F));*/


#pragma endregion
						}
					}
				}

				for(Vertex &v : g_vertex_buffer_data)
				{
					//v.SetColor(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
					GLfloat r,g,b;
					r = (float)(rand()%256)/256.f;
					g = (float)(rand()%256)/256.f;
					b = (float)(rand()%256)/256.f;

					v.SetColor(r, g, b, 1.0f);
				}

				// Give our vertices to OpenGL.
				glBufferData(GL_ARRAY_BUFFER, g_vertex_buffer_data.size() * sizeof(Vertex), g_vertex_buffer_data.data(), GL_STATIC_DRAW);
				matrix->m_vertexBuffer = vertexbuffer;
				//matrix->m_colorVertexbuffer = colorVertexbuffer;
				matrix->m_size = g_vertex_buffer_data.size();
				matrix->m_changed = false;

				vertexBuffers.push_back(std::pair<GLuint, GLuint>(vertexbuffer, g_vertex_buffer_data.size()));

			}
		}

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, mt->m_vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position))); //0, position

		//glEnableVertexAttribArray(1);       ////normal-saker kan man skita i just nu
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(baseOffset + offsetof(Vertex, normal)));       ////normal-saker kan man skita i just nu

		//glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color)));//glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color))); //1, färg

		glDrawArrays(GL_TRIANGLES, 0, mt->m_size);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
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

	//float ratio;
	//int width, height;
	//glfwGetFramebufferSize(window, &width, &height);
	//ratio = width / (float) height;
	//glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

}

void OpenglRenderer::Render(GLFWwindow *window)
{
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();


	//glRotatef((float) glfwGetTime() * 50.f, 0.f, 1.f, 1.f);
	//glTranslatef(0.f, 0.f, 1.125f);
	/*glBegin(GL_TRIANGLES);
	glColor3f(1.f, 0.f, 0.f);
	//glVertex3f(-0.6f, -0.4f, 0.f);
	glColor3f(0.f, 1.f, 0.f);
	//glVertex3f(0.6f, -0.4f, 0.f);
	glColor3f(0.f, 0.f, 1.f);
	//glVertex3f(0.f, 0.6f, 0.f);
	glEnd();

	glRotatef((float) glfwGetTime() * 500.f, 0.f, 1.f, 0.f);
	glTranslatef(0.f, 0.f, 1.125f);*/

	/*glBegin(GL_TRIANGLES);
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-0.06f, -0.04f, 0.f);
	glColor3f(0.f, 0.1f, 0.f);
	glVertex3f(0.06f, -0.04f, 0.f);
	glColor3f(0.f, 0.f, 0.1f);
	glVertex3f(0.f, 0.06f, 0.f);
	glEnd();*/
	/*	GLfloat error;
	error = glGetError();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	error = glGetError();
	float ratio;
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float) height;
	/*glViewport(0, 0, width, height);*/
	//glClear(GL_COLOR_BUFFER_BIT);
	//glMatrixMode(GL_PROJECTION);
	/*glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	float angle = (float) glfwGetTime() * 50.f;
	glRotatef(angle, 0.f, 0.f, +1.f);
	error = glGetError();

	glBegin(GL_TRIANGLES);
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-0.6f, -0.4f, 0.f);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.4f, 0.f);
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.6f, 0.f);
	glEnd();
	error = glGetError();*/
	/////////
	glfwSwapBuffers(window);
	/////

	////
	glfwPollEvents();
}
#endif