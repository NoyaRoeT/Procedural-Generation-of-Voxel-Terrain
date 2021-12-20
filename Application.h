#pragma once
#include "Window.h"
#include "Render/Renderer.h"
#include "Camera.h"

class Application
{
public:
	Application(int width, int height);

	void RunLoop();
	void ProcessMouseInput(float dt);
	void ProcessKeyInput(float dt);

private:
	Window m_Window;
	Camera m_Camera;
	//Runtime m_Runtime;
	Renderer m_Renderer;
	
};