#include "BlockTable.h"

BlockTable::BlockTable(int width, int height) : m_Width(width), m_Height(height), m_WidthSquared(width * width)
{
	m_Table = new int[width * width * height];
}

int BlockTable::GetBlock(int x, int y, int z) const
{
	return *(m_Table + x + y * m_WidthSquared + z * m_Width);
}

void BlockTable::SetBlock(int x, int y, int z, int value)
{
	m_Table[x + y * m_WidthSquared + z * m_Width] = value;
}

BlockTable::~BlockTable()
{
	delete[] m_Table;
}