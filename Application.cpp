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
	BlockDB& BlockDatabase = BlockDB::SetupDatabase("res/textures/blocks.png", 64);

	int BlockTable[] = { 2 };

	std::vector<float> vertices;

	BlockData& Block = BlockDatabase.GetBlockData(BlockTable[0]);
	std::vector<float>& FrontVertices = Block.FrontVertexAttribs;
	std::vector<float>& RightVertices = Block.RightVertexAttribs;
	std::vector<float>& LeftVertices = Block.LeftVertexAttribs;
	std::vector<float>& BackVertices = Block.BackVertexAttribs;
	std::vector<float>& TopVertices = Block.TopVertexAttribs;
	std::vector<float>& BottomVertices = Block.BottomVertexAttribs;

	vertices.insert(vertices.begin(), FrontVertices.begin(), FrontVertices.end());
	vertices.insert(vertices.end(), RightVertices.begin(), RightVertices.end());
	vertices.insert(vertices.end(), LeftVertices.begin(), LeftVertices.end());
	vertices.insert(vertices.end(), BackVertices.begin(), BackVertices.end());
	vertices.insert(vertices.end(), TopVertices.begin(), TopVertices.end());
	vertices.insert(vertices.end(), BottomVertices.begin(), BottomVertices.end());

	glEnable(GL_DEPTH_TEST);

	unsigned int VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	BlockDatabase.Atlas.Bind();

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
		

		RenderInfo info = { VAO, vertices.size() };
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