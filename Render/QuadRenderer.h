#pragma once
#include <vector>
#include "RenderInfo.h"
#include "Shader/Shader.h"
/*
In charge of drawing quads just for testing
*/
class Camera;

class QuadRenderer
{
public:
	void Add(const RenderInfo& quad);
	void DrawQuads(const Shader& shader, const Camera& camera);
private:
	std::vector<RenderInfo> m_Quads;

};