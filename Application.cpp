#include "Application.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "Render/RenderInfo.h"
#include "Texture/TextureAtlas.h"
#include "Timer.h"
#include "World/Block/BlockDB.h"
#include "World/Chunk/Chunk.h"
#include <cstdlib>

std::ostream& Print(const std::ostream&, std::array<float, 4> Subtexture);

Application::Application(int width, int height) : m_Window(width, height), m_Camera((float)width / height, 90.0f)
{
	BlockDB::SetupDatabase("res/textures/blocks.png", 64);
}

void Application::RunLoop()
{
	BlockDB& BlockDatabase = BlockDB::GetDatabase();
	BlockDatabase.m_Atlas.Bind();

	Chunk chunk;
	RenderInfo info;
	info.VAO = chunk.GenerateVertexArray();
	info.IndicesCount = chunk.m_NumFaces * 6;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.1f, 0.5f, 0.9f, 1.0f);

	unsigned int FrameCount = 0;
	unsigned int TotalElapsedTime = 0;
	float DeltaTime = 0.0f;

	while (!glfwWindowShouldClose(m_Window.m_Context))
	{

		++FrameCount;
		Timer PerFrameTimer;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ProcessMouseInput(DeltaTime);
		ProcessKeyInput(DeltaTime);
		

		std::vector<RenderInfo> ToDraw;
		ToDraw.push_back(info);
		m_Renderer.Draw(ToDraw, m_Camera);

		glfwSwapBuffers(m_Window.m_Context);
		glfwPollEvents();

		float ElapsedTime = PerFrameTimer.GetElapsedTime();
		DeltaTime = ElapsedTime; // in seconds
		TotalElapsedTime += ElapsedTime * 1000;
	}
	std::cout << "Average duration between each frame for " << FrameCount << " frames: " << (float)TotalElapsedTime / FrameCount << "ms" << std::endl;
}

void Application::ProcessMouseInput(float dt)
{

	static bool firstMouse = true;
	static double lastX = 0.0f;
	static double lastY = 0.0f;

	double xpos, ypos;
	glfwGetCursorPos(m_Window.m_Context, &xpos, &ypos);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	
	double xoffset = xpos - lastX;
	double yoffset = ypos - lastY;

	m_Camera.ProcessMouseInput(xoffset, yoffset, dt);

	lastX = xpos;
	lastY = ypos;
}

void Application::ProcessKeyInput(float dt)
{
	GLFWwindow* Context = m_Window.m_Context;
	if (glfwGetKey(Context, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(Context, true);

	m_Camera.ProcessKeyboardInput(Context, dt);
}

// Function for debugging
std::ostream& Print(const std::ostream&, std::array<float, 4> Subtexture)
{
	return std::cout << "Xmin: " << Subtexture[0] << "Ymin: " << Subtexture[1] << "Xmax: " << Subtexture[2] << "Ymax: " << Subtexture[3] << std::endl;
}