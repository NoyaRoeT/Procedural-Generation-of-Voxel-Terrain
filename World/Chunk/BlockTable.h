#pragma once
#include <memory>
struct BlockTable
{
	BlockTable(int width, int height);
	int GetBlockType(int x, int y, int z) const;
	void SetBlockType(int x, int y, int z, int value);
	~BlockTable();

	int m_Width, m_Height;
	int m_WidthSquared;
	int* m_Table = nullptr;
};

