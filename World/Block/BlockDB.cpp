#include "BlockDB.h"

BlockDB::BlockDB(const char* filepath, int texture_size) : m_Atlas(filepath, texture_size)
{
	for (int i = 0; i != BlockType::COUNT; ++i)
	{
		BlockData block(static_cast<BlockType>(i), m_Atlas);
		m_Database.push_back(block);
	}
}

BlockDB& BlockDB::GetDatabase()
{
	return SetupDatabase(0, 0);
}

BlockDB& BlockDB::SetupDatabase(const char* filepath, int texture_size)
{
	static BlockDB s_Instance(filepath, texture_size);
	return s_Instance;
}

const BlockData* BlockDB::GetBlock(int idx)
{
	return BlockDB::GetDatabase().GetBlockData(idx);
}

const BlockData* BlockDB::GetBlockData(int idx) const
{
	return &m_Database[idx];
}
