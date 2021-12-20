#pragma once
class ChunkLayer
{
public:
	ChunkLayer();
	~ChunkLayer();


private:
	unsigned int m_ChunkLayerSize;
	unsigned int* m_ChunkTable;
};

