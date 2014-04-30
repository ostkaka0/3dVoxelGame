#include <iostream>
#include <fstream>

#include "Shader.h"


static GLuint CreateShader(const std::string &text, GLenum shaderType);

// private:

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
			output.append(line + "\n");
        }
    }
    else
    {
		std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

    return output;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
    GLchar error[1024] = { 0 };

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << "Error: " << errorMessage << ": '" << error << "'" << std::endl;
    }
}

GLuint Shader::CreateShader(const std::string& text, unsigned int type)
{
	GLuint shader = glCreateShader(type);

	if (shader == 0)
		std::cerr << "Error: Shader creation failed!" << std::endl;

	const GLchar *shaderSourceStrings;
	GLint shaderSourceStringLengths;

	shaderSourceStrings = text.c_str();
	shaderSourceStringLengths = text.length();

	glShaderSource(shader, 1, &shaderSourceStrings, NULL);
	glCompileShader(shader);

	CheckShaderError(shader, GL_LINK_STATUS, false, "Shader compilation failed");

	return shader;
}

// private cpp-only:

// public:

Shader::Shader(const std::string &fileName)
{
	m_program = glCreateProgram();

	/*m_shaders[0] = CreateShader(LoadShader(fileName + ".vertexshader"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fragmentshader"), GL_VERTEX_SHADER);
	m_shaders[2] = CreateShader(LoadShader(fileName + ".geometryshader"), GL_GEOMETRY_SHADER);*/
	m_shaders[0] = CreateShader(LoadShader("vertexshader.glsl"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader("fragmenshader.glsl"), GL_FRAGMENT_SHADER);
	m_shaders[2] = CreateShader(LoadShader("geometryshader.glsl"), GL_GEOMETRY_SHADER);

	for (auto shader : m_shaders)
		glAttachShader(m_program, shader);

	//glBindAttribLocation(m_program, 0, "position");

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Program linking failed");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Program is invalid");
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
	glUniformMatrix4fv(m_program, 1, GL_FALSE, &MVP[0][0]);
}