#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct RenderInfo
{
	unsigned int VAO = 0;
	unsigned int IndicesCount = 0;
	glm::mat4 Model;

};