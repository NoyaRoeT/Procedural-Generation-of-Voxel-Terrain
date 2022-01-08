#include "Chunk.h"
#include "World/Block/BlockData.h"
#include "World/Block/BlockDB.h"
#include "glad/glad.h"
#include <iostream>
#include "glm/gtc/noise.hpp"
#include "ChunkConstants.h"
#include <cstdlib>


struct Offset
{
	int x, y, z;
};

Offset DirectionOffsets[] = { {0, 0, -1}, {0, 0, 1}, {-1, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, -1, 0} };

Chunk::Chunk(int x, int y, int width, int height) : m_ChunkData(width, height), m_NumVertices(0), m_VAO(0), m_VBO(0), m_Position(x, y)
{
	m_Model = glm::mat4(1.0f);
	m_Model = glm::translate(m_Model, glm::vec3(x * width, 0.0f, y * width));
	// For now set block type of all blocks in chunk to be random
	GenerateTerrain();
}

Chunk::~Chunk()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteVertexArrays(1, &m_VAO);
}

unsigned int Chunk::GenerateVertexArray()
{
	// Create Vertex Attribute Vector
	std::vector<float> vertices;

	for (int x = 0; x != m_ChunkData.m_Width; ++x)
	for (int z = 0; z != m_ChunkData.m_Width; ++z)
	for (int y = 0; y != m_ChunkData.m_Height; ++y)
	{

		int BlockType = m_ChunkData.GetBlockType(x, y, z);
		const BlockData* Block = BlockDB::GetBlock(BlockType);

		if (Block->isOpaque)
		{
			std::vector<float> BlockVertices;
			int NumVertices = 0;

			const BlockData* Front = GetAdjBlock(x, y, z, Direction::FRONT);
			const BlockData* Back = GetAdjBlock(x, y, z, Direction::BACK);
			const BlockData* Left = GetAdjBlock(x, y, z, Direction::LEFT);
			const BlockData* Right = GetAdjBlock(x, y, z, Direction::RIGHT);
			const BlockData* Top = GetAdjBlock(x, y, z, Direction::TOP);
			const BlockData* Bottom = GetAdjBlock(x, y, z, Direction::BOTTOM);

			if (Front == nullptr || !Front->isOpaque)
			{
				BlockVertices.insert(BlockVertices.cend(), Block->FrontVertexAttribs.cbegin(), Block->FrontVertexAttribs.cend());
				NumVertices += 6;
			}
			if (Back == nullptr || !Back->isOpaque)
			{
				BlockVertices.insert(BlockVertices.cend(), Block->BackVertexAttribs.cbegin(), Block->BackVertexAttribs.cend());
				NumVertices += 6;
			}
			if (Left == nullptr || !Left->isOpaque)
			{
				BlockVertices.insert(BlockVertices.cend(), Block->LeftVertexAttribs.cbegin(), Block->LeftVertexAttribs.cend());
				NumVertices += 6;
			}
			if (Right == nullptr || !Right->isOpaque)
			{
				BlockVertices.insert(BlockVertices.cend(), Block->RightVertexAttribs.cbegin(), Block->RightVertexAttribs.cend());
				NumVertices += 6;
			}

			if (Top == nullptr || !Top->isOpaque)
			{
				BlockVertices.insert(BlockVertices.cend(), Block->TopVertexAttribs.cbegin(), Block->TopVertexAttribs.cend());
				NumVertices += 6;
			}
			if (Bottom == nullptr || !Bottom->isOpaque)
			{
				BlockVertices.insert(BlockVertices.cend(), Block->BottomVertexAttribs.cbegin(), Block->BottomVertexAttribs.cend());
				NumVertices += 6;
			}

			Translate(BlockVertices, x, y, -z, NumVertices);

			m_NumVertices += NumVertices;
			vertices.insert(vertices.cend(), BlockVertices.cbegin(), BlockVertices.cend());
		}
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

	isSetup = true;
	return m_VAO;
}

void Chunk::Translate(std::vector<float>& vertices, float x, float y, float z, int numVertices)
{
	int iter = 0;
	for (int i = 0; i < numVertices; ++i)
	{
		vertices[iter] += x;
		vertices[iter + 1] += y;
		vertices[iter + 2] += z;
		iter += 5;
	}
}

const BlockData* Chunk::GetAdjBlock(int x, int y, int z, Direction dir) const
{
	const Offset& offset = DirectionOffsets[(int)dir];
	Offset AdjCoords = { x + offset.x ,  y + offset.y, z + offset.z };
	if (AdjCoords.x < 0 || AdjCoords.x >= m_ChunkData.m_Width || AdjCoords.y < 0 || AdjCoords.y >= m_ChunkData.m_Height
		|| AdjCoords.z < 0 || AdjCoords.z >= m_ChunkData.m_Width) return nullptr;
	else
	{
		int BlockType = m_ChunkData.GetBlockType(AdjCoords.x, AdjCoords.y, AdjCoords.z);
 		return BlockDB::GetBlock(BlockType);
	}

}

const glm::mat4& Chunk::GetModelMatrix() const
{
	return m_Model;
}

bool Chunk::operator==(const Chunk& OtherChunk)
{
	return this->m_Position.x == OtherChunk.m_Position.x && this->m_Position.y == OtherChunk.m_Position.y;
}

RenderInfo Chunk::GetRenderInfo() const
{
	RenderInfo info = { m_VAO, m_NumVertices, m_Model };
	return info;
}

void Chunk::GenerateTerrain()
{
	// Generate Height Map
	std::array<int, 1024> HeightMap;
	for (int z = 0; z < CHUNK_WIDTH; ++z)
	for (int x = 0; x < CHUNK_WIDTH; ++x)
	{
		int BlockX = x + m_Position.x * CHUNK_WIDTH;
		int BlockZ = -z + m_Position.y * CHUNK_WIDTH;

		int offset = rand() % 3 - 1;
		float value1 = glm::simplex(glm::vec2(BlockX/100.0f, BlockZ/100.0f));
		float value2 = glm::simplex(glm::vec2((BlockX + offset)/ 100.0f, (BlockZ + offset)/ 100.0f));
		

		float value = ((value1 * value2) + 1.0f) / 2.0f;

		value *= 56;

		HeightMap[z * CHUNK_WIDTH + x] = static_cast<int>(value);
	}

	// Apply Height Map

	for (int x = 0; x != m_ChunkData.m_Width; ++x)
	for (int z = 0; z != m_ChunkData.m_Width; ++z)
	{
		int Height = HeightMap[z * CHUNK_WIDTH + x];
		for (int y = 0; y != m_ChunkData.m_Height; ++y)
		{
			if (y > Height)
			{
				m_ChunkData.SetBlockType(x, y, z, BlockType::AIR);
			}
			else if (y == Height)
			{
				m_ChunkData.SetBlockType(x, y, z, BlockType::GRASS);
			}
			else if (y >= Height - 3)
			{
				m_ChunkData.SetBlockType(x, y, z, BlockType::DIRT);
			}
			else
			{
				m_ChunkData.SetBlockType(x, y, z, BlockType::STONE);
			}

		}
		
	}

	for (int x = 0; x != m_ChunkData.m_Width; ++x)
	for (int z = 0; z != m_ChunkData.m_Width; ++z)
	{
		int Height = HeightMap[z * CHUNK_WIDTH + x];
		int Random = rand() % 100;
		if (CHUNK_HEIGHT - Height > 6 && Random < 1 && x > 1 && x < CHUNK_WIDTH - 2 && z > 1 && z < CHUNK_WIDTH - 2)
		{

			// Trunk
			m_ChunkData.SetBlockType(x, Height + 1, z, BlockType::WOOD);
			m_ChunkData.SetBlockType(x, Height + 2, z, BlockType::WOOD);
			m_ChunkData.SetBlockType(x, Height + 3, z, BlockType::WOOD);
			m_ChunkData.SetBlockType(x, Height + 4, z, BlockType::WOOD);
			m_ChunkData.SetBlockType(x, Height + 5, z, BlockType::WOOD);

			// Leaves
			m_ChunkData.SetBlockType(x, Height + 6, z, BlockType::STONE);

			m_ChunkData.SetBlockType(x + 1, Height + 5, z - 1, BlockType::STONE);
			m_ChunkData.SetBlockType(x + 1, Height + 5, z, BlockType::STONE);
			m_ChunkData.SetBlockType(x + 1, Height + 5, z + 1, BlockType::STONE);
			m_ChunkData.SetBlockType(x, Height + 5, z + 1, BlockType::STONE);
			m_ChunkData.SetBlockType(x - 1, Height + 5, z - 1, BlockType::STONE);
			m_ChunkData.SetBlockType(x - 1, Height + 5, z, BlockType::STONE);
			m_ChunkData.SetBlockType(x - 1, Height + 5, z + 1, BlockType::STONE);
			m_ChunkData.SetBlockType(x, Height + 5, z - 1, BlockType::STONE);


		}
	}
}
