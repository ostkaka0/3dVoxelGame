#include <iostream>
#include <fstream>

#include "Shader.h"
#include <vector>


std::string Shader::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if(file.is_open())
	{
		while(file.good())
		{
			getline(file, line);
			output.append("\n" + line);
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void Shader::CheckShaderError(GLuint shader, const std::string& errorMessage)
{
	GLint result = GL_FALSE;
	int errorLength;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorLength);

	std::vector<char> error(errorLength);
	glGetShaderInfoLog(shader, errorLength, NULL, &error[0]);
	fprintf(stdout, "%s\n", &error[0]);
}

GLuint Shader::CreateShader(const std::string& source, GLenum type)
{
	GLuint shaderId = glCreateShader(type);

	if (shaderId == 0)
		std::cerr << "Error: Shader creation failed!" << std::endl;

	// Compile Shader
	std::cout << "Compiling Shader: " << type << std::endl;
	char const * ShaderSourcePointer = source.c_str();
	glShaderSource(shaderId, 1, &ShaderSourcePointer , NULL);
	glCompileShader(shaderId);

	CheckShaderError(shaderId, "Shader compilation failed");

	return shaderId;
}

Shader::Shader(const std::string &fileName, const std::string *uniforms)
{
	GLint error = glGetError();
	m_shaders[0] = CreateShader(LoadShader("shaders\\" + fileName + ".vertexshader"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader("shaders\\" + fileName + ".fragmentshader"), GL_FRAGMENT_SHADER);
	m_shaders[2] = CreateShader(LoadShader("shaders\\" + fileName + ".geometryshader"), GL_GEOMETRY_SHADER);
	//m_shaders[0] = CreateShader(LoadShader("vertexshader.glsl"), GL_VERTEX_SHADER);
	//m_shaders[1] = CreateShader(LoadShader("fragmentshader.glsl"), GL_FRAGMENT_SHADER);
	//m_shaders[2] = CreateShader(LoadShader("geometryshader.glsl"), GL_GEOMETRY_SHADER);
	error = glGetError();

	m_program = glCreateProgram();
	error = glGetError();

	for (auto shader : m_shaders)
		glAttachShader(m_program, shader);
	error = glGetError();

	//glBindAttribLocation(m_program, 0, "position");

	// Link Program
	glLinkProgram(m_program);
	error = glGetError();

	// Check Program
	GLint Result = GL_FALSE;
	int InfoLogLength;
	glGetProgramiv(m_program, GL_LINK_STATUS, &Result);
	glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ProgramErrorMessage(std::max(InfoLogLength, int(1)) );
	glGetProgramInfoLog(m_program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
	error = glGetError();

	for (auto shader : m_shaders)
		glDeleteShader(shader);

	//m_matrixId = glGetUniformLocation(m_program, "MVP");

	m_uniforms = new GLint[sizeof(*uniforms)/sizeof(std::string)];

	for (int i = 0; i < sizeof(*uniforms)/sizeof(std::string); i++)
	{
		const char *str = uniforms[i].c_str();
		m_uniforms[i] = glGetUniformLocation(m_program, str);
	}

}

Shader::~Shader(void)
{
	for (auto shader : m_shaders)
	{
		glDetachShader(m_program, shader);
		glDeleteShader(shader);
	}

	glDeleteProgram(m_program);
}

void Shader::Bind()
{
	glUseProgram(m_program);
}

void Shader::Update(const glm::mat4 &MVP)
{
	glUniformMatrix4fv(m_uniforms[0], 1, GL_FALSE, &MVP[0][0]);
	//glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
}

GLint Shader::getUniform(const int index)
{
	return m_uniforms[index];
}