#pragma once
/*
* GLFW Window abstraction class.
*/
struct FrameDim
{
	int width;
	int height;
};

class GLFWwindow;

class Window
{
public:
	Window(int width, int height);
	~Window();
	FrameDim GetFrameDims();

	GLFWwindow* m_Context = nullptr;
private:
	static void FrameResizeCallback(GLFWwindow* window, int width, int height);
};