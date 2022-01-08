#include "Renderer.h"
#include "glad/glad.h"
#include "Camera.h"
#include <iostream>



// Temporarily fixed to our shader
Renderer::Renderer() : m_Shader("Shader/shaders/vertexshader.shader", "Shader/shaders/fragshader.shader")
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.1f, 0.5f, 0.9f, 1.0f);
}

// for now, meshes are renderinfo structs and we delegate all to quadrenderer
void Renderer::Draw(const std::vector<RenderInfo>& Meshes, const Camera& camera)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_Shader.Use();
	m_Shader.setMat4("projectionView", camera.GetProjectionViewMatrix());
	for (auto i = Meshes.cbegin(); i != Meshes.cend(); ++i)
	{
		m_Shader.setMat4("model", i->Model);
		unsigned int VAO = i->VAO;
		unsigned int IndicesCount = i->IndicesCount;
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, IndicesCount);
	}
}