#pragma once
#include "Chunk.h"
#include <memory>
#include <deque>


class ChunkManager
{
public:
	ChunkManager();
	void Update(const glm::vec3& pos);
	std::vector<RenderInfo> GetRenderInfoList();
	std::shared_ptr<Chunk> isChunkLoaded(const ChunkPosition& pos, const std::vector<std::vector<std::shared_ptr<Chunk>>>& Cache) const;

	std::deque<ChunkPosition> m_LoadingQueue;
	std::vector<std::vector<std::shared_ptr<Chunk>>> m_LoadedChunks;

private:
	bool isChunkInQueue(const ChunkPosition& pos);
};

