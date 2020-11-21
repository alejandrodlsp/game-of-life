#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexSource;
	std::string fragmentSource;
	std::ifstream vertexFile;
	std::ifstream fragmentFile;

	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vertexFile.open(vertexPath);
		fragmentFile.open(fragmentPath);

		std::stringstream vertexStream, fragmentStream;
		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();

		vertexFile.close();
		fragmentFile.close();

		vertexSource = vertexStream.str();
		fragmentSource = fragmentStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR: Shader file not succesfully read" << std::endl;
	}
	const char* vShaderCode = vertexSource.c_str();
	const char* fShaderCode = fragmentSource.c_str();

	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "Error: shader vertex compilation failure: " << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "Error: shader fragment compilation failure: " << infoLog << std::endl;
	}

	mId = glCreateProgram();
	glAttachShader(mId, vertex);
	glAttachShader(mId, fragment);
	glLinkProgram(mId);

	glGetProgramiv(mId, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(mId, 512, NULL, infoLog);
		std::cout << "Error: shader program linking failure: " << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader()
{
	glDeleteProgram(mId);
}

void Shader::Bind()
{
	glUseProgram(mId);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

void Shader::SetUniformB(const std::string &name, bool value)
{
	glUniform1i(GetUniformLocation(name), (int)value);
}

void Shader::SetUniformI(const std::string &name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniformF(const std::string &name, float value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniformVec3(const std::string & name, glm::vec3 vec)
{
	glUniform3f(GetUniformLocation(name), vec.x, vec.y, vec.z);
}

void Shader::SetUniformVec4(const std::string & name, glm::vec4 vec)
{
	glUniform4f(GetUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
}

void Shader::SetUniformMat4(const std::string & name, glm::mat4 values)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(values));
}

int Shader::GetUniformLocation(const std::string &name)
{
	return glGetUniformLocation(mId, name.c_str());
}