#include "Application.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "Render/RenderInfo.h"
#include "Texture/TextureAtlas.h"
#include "Timer.h"
#include "World/Block/BlockDB.h"
#include "World/Chunk/Chunk.h"
#include "World/Chunk/ChunkManager.h"
#include <cstdlib>

std::ostream& Print(const std::ostream&, std::array<float, 4> Subtexture);

Application::Application(int width, int height) : m_Window(width, height), m_Player((float)width/height)
{
	// To be extracted to world class or sth like that
	BlockDB::SetupDatabase("res/textures/blocks.png", 64);
}

void Application::RunLoop()
{
	BlockDB& BlockDatabase = BlockDB::GetDatabase();
	BlockDatabase.m_Atlas.Bind();

	Timer PerFrameTimer;
	while (!glfwWindowShouldClose(m_Window.m_Context))
	{
		PerFrameTimer.StartTime();
		ProcessMouseInput(PerFrameTimer.m_DeltaTime);
		ProcessKeyInput(PerFrameTimer.m_DeltaTime);
		m_Player.ProcessMouseButton(m_ChunkManager, m_Window.m_Context);
		m_ChunkManager.Update(m_Player.GetPosition());

		m_Renderer.Draw(m_ChunkManager.GetRenderInfoList(), m_Player.m_Camera);
		glfwSwapBuffers(m_Window.m_Context);
		glfwPollEvents();

		PerFrameTimer.StopTime();
	
	}
	std::cout << "Average duration between each frame for " << PerFrameTimer.m_FrameCount << " frames: " << PerFrameTimer.GetMSPerFrame() << "ms" << std::endl;
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
	m_Player.ProcessMouseInput(xoffset, yoffset, dt);

	lastX = xpos;
	lastY = ypos;
}

void Application::ProcessKeyInput(float dt)
{
	GLFWwindow* Context = m_Window.m_Context;
	if (glfwGetKey(Context, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(Context, true);
	if (glfwGetKey(Context, GLFW_KEY_1) == GLFW_PRESS) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(Context, GLFW_KEY_2) == GLFW_PRESS) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	m_Player.ProcessKeyboardInput(Context, dt);
}

// Function for debugging
std::ostream& Print(const std::ostream&, std::array<float, 4> Subtexture)
{
	return std::cout << "Xmin: " << Subtexture[0] << "Ymin: " << Subtexture[1] << "Xmax: " << Subtexture[2] << "Ymax: " << Subtexture[3] << std::endl;
}