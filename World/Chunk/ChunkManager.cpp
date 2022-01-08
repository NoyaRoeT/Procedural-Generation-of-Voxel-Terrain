#include "ChunkManager.h"
#include <iostream>
#include "ChunkConstants.h"

int RENDER_DISTANCE = 2;
int MAX_LOAD_PER_FRAME = 1;

ChunkManager::ChunkManager()
{
	int Length = RENDER_DISTANCE * 2 + 1;

	std::vector<std::shared_ptr<Chunk>> temp;
	for (int i = 0; i != Length; ++i) temp.push_back(nullptr);
	for (int i = 0; i != Length; ++i) m_LoadedChunks.push_back(temp);
	
		
}

std::shared_ptr<Chunk> ChunkManager::isChunkLoaded(const ChunkPosition& pos, const std::vector<std::vector<std::shared_ptr<Chunk>>>& Cache) const
{
	for (const auto& row : Cache)
	for (const auto& chunk : row)
	{
		if (chunk != nullptr && pos == chunk->m_Position)
			return chunk;
	}
	return nullptr;
}

bool ChunkManager::isChunkInQueue(const ChunkPosition& pos)
{
	return std::find(m_LoadingQueue.cbegin(), m_LoadingQueue.cend(), pos) != m_LoadingQueue.cend();
}


std::vector<RenderInfo> ChunkManager::GetRenderInfoList()
{
	std::vector<RenderInfo> InfoVector;
	for (auto& row : m_LoadedChunks)
	for (auto& chunk : row)
	{
		// check if its a nullptr
		if (chunk)
		{
			if (!chunk->isSetup) chunk->GenerateVertexArray();
			InfoVector.emplace_back(chunk->GetRenderInfo());
		}
	}
	return InfoVector;
}

void ChunkManager::Update(const glm::vec3& pos)
{
	auto Cache = m_LoadedChunks;
	// Get player's chunk coordinate
	const int ChunkX = (pos.x < 0) ? floor(pos.x / CHUNK_WIDTH) : pos.x / CHUNK_WIDTH;
	const int ChunkY = (pos.z > 0) ? ceil(pos.z / CHUNK_WIDTH) : pos.z / CHUNK_WIDTH;

	// Replace chunks with those that are within render distance;
	int MaxLength = RENDER_DISTANCE * 2 + 1;
	for (int x = 0; x != MaxLength; ++x)
	for (int y = 0; y != MaxLength; ++y)
	{
		ChunkPosition temp(ChunkX + x - RENDER_DISTANCE, ChunkY + y - RENDER_DISTANCE);
		auto chunk = isChunkLoaded(temp, Cache);
		if (chunk != nullptr)
			m_LoadedChunks[x][y] = chunk;
		else if (!isChunkInQueue(temp))
			// If chunk is not alr loaded, push into loading queue
			m_LoadingQueue.push_back(ChunkPosition(temp.x, temp.y));
	}

	for (int i = 0; i != MAX_LOAD_PER_FRAME; ++i)
	{
		if (!m_LoadingQueue.empty())
		{
			const ChunkPosition& temp = m_LoadingQueue.front();
			// Check if chunk still needs to be loaded.
			const int DistX = temp.x - ChunkX;
			const int DistY = temp.y - ChunkY;

			if (abs(DistX) <= RENDER_DISTANCE && abs(DistY) <= RENDER_DISTANCE)
			{
				const int XIdx = DistX + RENDER_DISTANCE;
				const int YIdx = DistY + RENDER_DISTANCE;

				m_LoadedChunks[XIdx][YIdx] = std::make_shared<Chunk>(temp.x, temp.y, CHUNK_WIDTH, CHUNK_HEIGHT);
			}
			m_LoadingQueue.pop_front();
		}
	}

}