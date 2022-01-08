#pragma once
#include "RenderInfo.h"
#include <vector>
#include "Shader/Shader.h"

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
	Shader m_Shader;
};