#include "BlockData.h"
#include "Texture/TextureAtlas.h"
#include <vector>

class BlockDB
{
public:
	BlockDB(const BlockDB&) = delete;

	static BlockDB& GetDatabase();
	static BlockDB& SetupDatabase(const char* filepath, int texture_size);

	BlockData& GetBlockData(int idx);

	std::vector<BlockData> Database;
	TextureAtlas Atlas;
private:
	BlockDB(const char* filepath, int texture_size);

};