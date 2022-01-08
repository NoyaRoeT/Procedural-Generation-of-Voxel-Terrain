#pragma once
#include "Window.h"
#include "Render/Renderer.h"
#include "Player.h"
#include "World/Chunk/ChunkManager.h"

class Application
{
public:
	Application(int width, int height);

	void RunLoop();
	void ProcessMouseInput(float dt);
	void ProcessKeyInput(float dt);

private:
	Window m_Window;
	Player m_Player;
	ChunkManager m_ChunkManager;
	Renderer m_Renderer;
	
};