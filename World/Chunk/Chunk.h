#pragma once
#include <vector>
#include "World/Chunk/BlockTable.h"

class Chunk
{
public:
	Chunk();
	~Chunk();
	unsigned int GenerateVertexArray();
	int m_NumFaces = 0;
	BlockTable m_Table;
private:
	unsigned int m_VAO;
	unsigned int m_VBO;

	void Translate(std::vector<float>& vertices, float x, float y, float z);
};

