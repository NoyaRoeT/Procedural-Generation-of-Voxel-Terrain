#include "BlockData.h"
#include "Texture/TextureAtlas.h"
#include <vector>

class BlockDB
{
public:
	BlockDB(const BlockDB&) = delete;
	static BlockDB& GetDatabase();
	static BlockDB& SetupDatabase(const char* filepath, int texture_size);
	std::vector<BlockData> Database;
	TextureAtlas Atlas;
	static BlockDB s_Instance;
private:
	BlockDB(const char* filepath, int texture_size);

};