#include "BlockDB.h"

BlockDB::BlockDB(const char* filepath, int texture_size) : Atlas(filepath, texture_size)
{
	for (int i = BlockID::GRASS; i != BlockID::COUNT; ++i)
	{
		BlockData block(static_cast<BlockID>(i), Atlas);
		Database.push_back(block);
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

BlockData& BlockDB::GetBlockData(int idx)
{
	return Database[idx];
}
