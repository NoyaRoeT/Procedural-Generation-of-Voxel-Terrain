#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GLFWwindow;

class Camera
{
public:
	glm::vec3 m_Position;
	glm::vec3 m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_WorldUp;
	glm::vec3 m_Up;
	glm::vec3 m_Right;

	float m_FOV;
	float m_AspectRatio;

	float m_Yaw = -90.0f;
	float m_Pitch = 0.0f;
	float m_Sensitivity = 20.0f;
	float m_Speed = 10.0f;

	glm::mat4 m_Projection;

	Camera(float aspectRatio, float fov = 90.0f, const glm::vec3& pos = glm::vec3(0.0f),
		const glm::vec3& worldup = glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 GetViewMatrix() const;
	const glm::mat4& GetPerspectiveMatrix() const;
	glm::mat4 GetProjectionViewMatrix() const;
	void ProcessMouseInput(float xoffset, float yoffset, float dt);
	void ProcessKeyboardInput(GLFWwindow* context, float dt);

private:

	void UpdateCameraVectors();
};

