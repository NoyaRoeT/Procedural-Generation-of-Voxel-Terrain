#pragma once
#include <vector>
#include "World/Chunk/BlockTable.h"
#include "Render/RenderInfo.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class BlockData;

enum Direction
{
	FRONT, BACK, LEFT, RIGHT, TOP, BOTTOM
};

struct ChunkPosition
{
	ChunkPosition(int _x, int _y) : x(_x), y(_y) {}
	int x, y;
	bool operator==(const ChunkPosition& b) const 
	{ 
		return b.x == this->x && b.y == this->y; 
	}
};

class Chunk
{
public:
	Chunk(int x, int y, int width, int height);
	~Chunk();

	bool operator==(const Chunk& OtherChunk);

	unsigned int GenerateVertexArray();
	const glm::mat4& GetModelMatrix() const;
	RenderInfo GetRenderInfo() const;

	int m_NumVertices;
	BlockTable m_ChunkData;
	ChunkPosition m_Position;
	bool isSetup = false;

private:
	unsigned int m_VAO;
	unsigned int m_VBO;
	glm::mat4 m_Model;

	void Translate(std::vector<float>& vertices, float x, float y, float z, int numVertices);
	const BlockData* GetAdjBlock(int x, int y, int z, Direction dir) const;

	void GenerateTerrain();
};

