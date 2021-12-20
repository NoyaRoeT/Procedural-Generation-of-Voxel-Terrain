#include "Shader.h"
#include "glad/glad.h"

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>


Shader::Shader(const char* vertexPath, const char* fragPath)
{
	std::ifstream vShaderFile(vertexPath);
	std::ifstream fShaderFile(fragPath);

	if (!vShaderFile.is_open() || !fShaderFile.is_open())
	{
		std::cout << "SHADER::ERROR: Failed to open shader files" << std::endl;
	}

	std::string line;
	std::stringstream vStream;
	std::stringstream fStream;

	while (std::getline(vShaderFile, line))
	{
		vStream << line << "\n";
	}
	while (std::getline(fShaderFile, line))
	{
		fStream << line << "\n";
	}

	std::string VertexShaderCode = vStream.str();
	std::string FragShaderCode = fStream.str();

	const char* vsrc = VertexShaderCode.c_str();
	const char* fsrc = FragShaderCode.c_str();

	unsigned int VertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int FragShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(VertexShader, 1, &vsrc, NULL);
	glShaderSource(FragShader, 1, &fsrc, NULL);

	int Success;
	char InfoLog[512];
	
	glCompileShader(VertexShader);
	glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &Success);

	if (!Success)
	{
		glGetShaderInfoLog(VertexShader, 512, NULL, InfoLog);
		std::cout << "SHADER::COMPILATION::VERTEX::ERROR: " << InfoLog << std::endl;
	}

	glCompileShader(FragShader);
	glGetShaderiv(FragShader, GL_COMPILE_STATUS, &Success);

	if (!Success)
	{
		glGetShaderInfoLog(FragShader, 512, NULL, InfoLog);
		std::cout << "SHADER::COMPILATION::FRAGMENT::ERROR: " << InfoLog << std::endl;
	}

	m_ID = glCreateProgram();
	glAttachShader(m_ID, VertexShader);
	glAttachShader(m_ID, FragShader);

	glLinkProgram(m_ID);
	glGetProgramiv(m_ID, GL_LINK_STATUS, &Success);

	if (!Success)
	{
		glGetProgramInfoLog(m_ID, 512, NULL, InfoLog);
		std::cout << "SHADER::LINK::PROGRAM::ERROR: " << InfoLog << std::endl;
	}

	glDeleteShader(VertexShader);
	glDeleteShader(FragShader);
}

void Shader::Use() const
{
	glUseProgram(m_ID);
}

void Shader::setMat4(const std::string& name, const glm::mat4& value) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
