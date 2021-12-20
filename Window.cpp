#include "Window.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

Window::Window(int width, int height)
{
	//Window creation
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3.0);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3.0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Context = glfwCreateWindow(width, height, "Minecraft", NULL, NULL);
	if (!m_Context)
	{
		std::cout << "WINDOW::ERROR: Failed to create window." << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(m_Context);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) std::cout << "WINDOW::ERROR: Failed to initialize GLAD" << std::endl;
	glViewport(0, 0, width, height);

	glfwSetInputMode(m_Context, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(m_Context, FrameResizeCallback);
	
}

FrameDim Window::GetFrameDims()
{
	int width, height;
	glfwGetFramebufferSize(m_Context, &width, &height);
	return FrameDim{ width, height };
}

void Window::FrameResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Window::~Window()
{
	glfwTerminate();
}