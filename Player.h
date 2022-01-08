#pragma once
#include "Camera.h"

class ChunkManager;

class Player
{
public:
	Player(float aspect);
	const glm::vec3& GetPosition() const;
	const glm::vec3& GetFront() const;

	void ProcessMouseButton(const ChunkManager& manager, GLFWwindow* context);
	void ProcessMouseInput(float xoffset, float yoffset, float dt);
	void ProcessKeyboardInput(GLFWwindow* context, float dt);
	void ShootRay(const ChunkManager& manager);
	Camera m_Camera;
private:
};

