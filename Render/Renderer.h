#pragma once
#include "QuadRenderer.h"
#include "RenderInfo.h"
/*
* In charge of organising data received from runtime, generating and packaging vertex arrays in RenderInfo
* and sending them to the appropriate renderer.
*/

class Camera;

class Renderer
{
public:
	Renderer();
	void Draw(const std::vector<RenderInfo>& Meshes, const Camera& camera);

private:
	QuadRenderer m_QuadRenderer;
	Shader m_Shader;
};