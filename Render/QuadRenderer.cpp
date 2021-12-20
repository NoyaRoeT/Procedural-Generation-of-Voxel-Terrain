#include "QuadRenderer.h"
#include "glad/glad.h"
#include "Camera.h"

// temporarily here for projection matrix
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void QuadRenderer::Add(const RenderInfo& info)
{
	m_Quads.push_back(info);
}

void QuadRenderer::DrawQuads(const Shader& shader, const Camera& camera)
{
	shader.Use();
	shader.setMat4("projection", camera.GetPerspectiveMatrix());
	shader.setMat4("view", camera.GetViewMatrix());

	for (auto i = m_Quads.cbegin(); i != m_Quads.cend(); ++i)
	{
		unsigned int VAO = i->VAO;
		unsigned int IndicesCount = i->IndicesCount;
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}