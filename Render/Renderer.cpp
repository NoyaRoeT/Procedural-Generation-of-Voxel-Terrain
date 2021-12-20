#include "Renderer.h"
#include <iostream>


// Temporarily fixed to our shader
Renderer::Renderer() : m_Shader("Shader/shaders/vertexshader.shader", "Shader/shaders/fragshader.shader")
{

}

// for now, meshes are renderinfo structs and we delegate all to quadrenderer
void Renderer::Draw(const std::vector<RenderInfo>& Meshes, const Camera& camera)
{
	for (auto i = Meshes.begin(); i != Meshes.end(); ++i)
	{
		m_QuadRenderer.Add(*i);
	}

	m_QuadRenderer.DrawQuads(m_Shader, camera);
}