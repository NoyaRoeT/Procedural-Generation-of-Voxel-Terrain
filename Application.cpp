#include "Application.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "Render/RenderInfo.h"
#include "Texture/TextureAtlas.h"
#include "Timer.h"
#include "World/Block/BlockDB.h"

std::ostream& Print(const std::ostream&, std::array<float, 4> Subtexture);

Application::Application(int width, int height) : m_Window(width, height), m_Camera((float)width / height, 105.0f)
{

}

void Application::RunLoop()
{
	BlockDB::s_Instance = BlockDB::SetupDatabase("res/texture/block.png", 64);

	float vertices[] = {
		// Front face
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.25f, 0.0f,
		1.0f, 1.0f, 0.0f, 0.25f, 0.333f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 0.25f, 0.333f, 
		0.0f, 1.0f, 0.0f, 0.0f, 0.333f,


		//Right Face
		1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, -1.0f, 0.25f, 0.0f,
		1.0f, 1.0f, -1.0f, 0.25f, 0.333f,
		1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, -1.0f, 0.25f, 0.333f,
		1.0f, 1.0f, 0.0f, 0.0f, 0.333f,

	};

	

	glEnable(GL_DEPTH_TEST);

	unsigned int VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	TextureAtlas Atlas("res/textures/blocks.png", 64);
	Atlas.Bind();

	Print(std::cout, Atlas.GetSubtexture(0, 1));


	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

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
		

		RenderInfo info = { VAO, 36 };
		std::vector<RenderInfo> ToDraw;
		ToDraw.push_back(info);
		m_Renderer.Draw(ToDraw, m_Camera);

		glfwSwapBuffers(m_Window.m_Context);
		glfwPollEvents();

		float ElapsedTime = PerFrameTimer.GetElapsedTime();
		DeltaTime = ElapsedTime; // in seconds
		TotalElapsedTime += ElapsedTime * 0.001;
	}
	std::cout << "Average duration between each frame for " << FrameCount << " frames: " << TotalElapsedTime / (float)FrameCount << "ms" << std::endl;
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