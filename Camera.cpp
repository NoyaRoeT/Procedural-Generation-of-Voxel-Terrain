#include "Camera.h"
#include "GLFW/glfw3.h"
#include <iostream>

Camera::Camera(float aspectRatio, float fov, const glm::vec3& pos, const glm::vec3& worldup) :
	m_AspectRatio(aspectRatio), m_Position(pos), m_WorldUp(worldup), m_FOV(fov)
{
	UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(m_Position, m_Position + m_Front, m_WorldUp);
}

glm::mat4 Camera::GetPerspectiveMatrix() const
{
	return glm::perspective(glm::radians(m_FOV), m_AspectRatio, 0.1f, 1000.0f);
}

void Camera::ProcessMouseInput(float xoffset, float yoffset, float dt)
{
	xoffset *= m_Sensitivity * dt;
	yoffset *= m_Sensitivity * dt;

	m_Yaw += xoffset;
	m_Pitch -= yoffset;

	if (m_Pitch > 89.0f) m_Pitch = 89.0f;
	else if (m_Pitch < -89.0f) m_Pitch = -89.0f;


	UpdateCameraVectors();
}

void Camera::ProcessKeyboardInput(GLFWwindow* context, float dt)
{
	float speed = m_Speed * dt;
	if (glfwGetKey(context, GLFW_KEY_W) == GLFW_PRESS)  m_Position += m_Front * speed;
	if (glfwGetKey(context, GLFW_KEY_S) == GLFW_PRESS)  m_Position -= m_Front * speed;
	if (glfwGetKey(context, GLFW_KEY_A) == GLFW_PRESS)  m_Position -= m_Right * speed;
	if (glfwGetKey(context, GLFW_KEY_D) == GLFW_PRESS)  m_Position += m_Right * speed;
}

void Camera::UpdateCameraVectors()
{
	glm::vec3 front(cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch)),
					sin(glm::radians(m_Pitch)),
					sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch)));

	m_Front = glm::normalize(front);
	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
	m_Up = glm::cross(m_Right, m_Front);
	
}
