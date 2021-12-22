#include "Chunk.h"
#include "World/Block/BlockData.h"
#include "World/Block/BlockDB.h"
#include "glad/glad.h"
#include <iostream>
#include "Timer.h"


int CHUNK_WIDTH = 16*5;
int CHUNK_HEIGHT = 1;
int NUM_CHUNK_BLOCKS = CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT;

Chunk::Chunk() : m_Table(CHUNK_WIDTH, CHUNK_HEIGHT)
{
	// For now set block type of all blocks in chunk to be random

	for (int i = 0; i != NUM_CHUNK_BLOCKS; ++i)
	{
		m_Table.m_Table[i] = rand() % 3;
	}
}

Chunk::~Chunk()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteVertexArrays(1, &m_VAO);
}

unsigned int Chunk::GenerateVertexArray()
{
	Timer timer;
	// Get block database
	const BlockDB& Database = BlockDB::GetDatabase();

	// Create Vertex Attribute Vector
	std::vector<float> vertices;

	for (int x = 0; x != CHUNK_WIDTH; ++x)
	for (int z = 0; z != CHUNK_WIDTH; ++z)
	for (int y = 0; y != CHUNK_HEIGHT; ++y)
	{
		int BlockType = m_Table.GetBlock(x, y, z);
		const BlockData& Block = Database.GetBlockData(BlockType);

		std::vector<float> FrontVertices = Block.FrontVertexAttribs;
		std::vector<float> RightVertices = Block.RightVertexAttribs;
		std::vector<float> LeftVertices = Block.LeftVertexAttribs;
		std::vector<float> BackVertices = Block.BackVertexAttribs;
		std::vector<float> TopVertices = Block.TopVertexAttribs;
		std::vector<float> BottomVertices = Block.BottomVertexAttribs;
		
		Translate(FrontVertices, x, y, -z);
		Translate(RightVertices, x, y, -z);
		Translate(LeftVertices, x, y, -z);
		Translate(BackVertices, x, y, -z);
		Translate(TopVertices, x, y, -z);
		Translate(BottomVertices, x, y, -z);

		vertices.insert(vertices.end(), FrontVertices.begin(), FrontVertices.end());
		vertices.insert(vertices.end(), RightVertices.begin(), RightVertices.end());
		vertices.insert(vertices.end(), LeftVertices.begin(), LeftVertices.end());
		vertices.insert(vertices.end(), BackVertices.begin(), BackVertices.end());
		vertices.insert(vertices.end(), TopVertices.begin(), TopVertices.end());
		vertices.insert(vertices.end(), BottomVertices.begin(), BottomVertices.end());

		m_NumFaces += 6;

	}
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));

	std::cout << timer.GetElapsedTime() * 1000.0f << std::endl;
	return m_VAO;
}

void Chunk::Translate(std::vector<float>& vertices, float x, float y, float z)
{
	int iter = 0;
	for (int i = 0; i < 6; ++i)
	{
		vertices[iter] += x;
		vertices[iter + 1] += y;
		vertices[iter + 2] += z;
		iter += 5;
	}
}
