#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stb_image.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "shader.h"

using namespace std;

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "Failed to load shader file : " << e.what() << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	int success;
	char infoLog[512];

	vertexID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexID, 1, &vShaderCode, NULL);
	glCompileShader(vertexID);

	glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);
	if (!success) 
	{
		glGetShaderInfoLog(vertexID, 512, NULL, infoLog);
		std::cout << "ERROR::VERTEX SHADER\n" << infoLog << std::endl;
	}

	fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentID, 1, &fShaderCode, NULL);
	glCompileShader(fragmentID);

	glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
	if (!success) 
	{
		glGetShaderInfoLog(vertexID, 512, NULL, infoLog);
		std::cout << "ERROR::FRAGMENT SHADER\n" << infoLog << std::endl;
	}

	this->CreateProgram();
	this->DeleteShaders();
};

void Shader::UseProgram()
{
	glUseProgram(programID);
};

void Shader::CreateProgram()
{
	int success;
	char infoLog[512];

	programID = glCreateProgram();

	glAttachShader(programID, vertexID);
	glAttachShader(programID, fragmentID);
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &success);

	if (!success) 
	{
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM\n" << infoLog << std::endl;
	}
};

void Shader::DeleteProgram()
{
	glDeleteProgram(programID);
};

void Shader::DeleteShaders()
{
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
};

void Shader::SetInt(const char* name, int val)
{
	glUniform1i(glGetUniformLocation(programID, name), val);
};

void Shader::SetVec3(const char* name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(programID, name), x, y, z);
};

void Shader::SetVec3(const char* name, glm::vec3 vec)
{
	glUniform3f(glGetUniformLocation(programID, name), vec.x, vec.y, vec.z);
};

void Shader::SetMat4(const char* name, glm::mat4 &matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(programID, name), 1, GL_FALSE, &matrix[0][0]);
};

void Shader::SetTexture(const char* name, const int index)
{
	glUniform1i(glGetUniformLocation(programID, name), index);
};

Shader::~Shader()
{
	this->DeleteProgram();
};

