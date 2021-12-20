#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragPath);
	void Use() const;

	void setMat4(const std::string& name, const glm::mat4 &value) const;

private:

	unsigned int m_ID;
};

