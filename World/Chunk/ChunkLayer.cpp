#include "ChunkLayer.h"

ChunkLayer::ChunkLayer() : m_ChunkLayerSize(16 * 16), m_ChunkTable(new unsigned int[16*16])
{
}

ChunkLayer::~ChunkLayer()
{
	delete[] m_ChunkTable;
}

