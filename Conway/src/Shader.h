#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void Bind();
	void Unbind();
	
	void SetUniformB(const std::string &name, bool value);
	void SetUniformI(const std::string &name, int value);
	void SetUniformF(const std::string &name, float value);

	void SetUniformVec4(const std::string &name, glm::vec4 vec);
	void SetUniformMat4(const std::string &name, glm::mat4 mat);
	void SetUniformVec3(const std::string &name, glm::vec3 vec);

	int GetUniformLocation(const std::string &name);

	inline unsigned int GetId() const { return mId; }

private:
	unsigned int mId;
};

