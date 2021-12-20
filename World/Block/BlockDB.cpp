#include "BlockDB.h"

BlockDB& BlockDB::GetDatabase()
{
	return s_Instance;
}

BlockDB& BlockDB::SetupDatabase(const char* filepath, int texture_size)
{
	s_Instance = BlockDB(filepath, texture_size);
}

BlockDB::BlockDB(const char* filepath, int texture_size) : Atlas(filepath, texture_size)
{
	for (int i = BlockID::GRASS; i != BlockID::COUNT; ++i)
	{
		BlockData block(static_cast<BlockID>(i), Atlas);
	}
}