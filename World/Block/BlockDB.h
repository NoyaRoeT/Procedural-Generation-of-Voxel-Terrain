#include "BlockData.h"
#include "Texture/TextureAtlas.h"
#include <vector>

class BlockDB
{
public:
	BlockDB(const BlockDB&) = delete;

	static BlockDB& GetDatabase();
	static BlockDB& SetupDatabase(const char* filepath, int texture_size);
	static const BlockData* GetBlock(int idx);

	std::vector<BlockData> m_Database;
	TextureAtlas m_Atlas;
private:
	BlockDB(const char* filepath, int texture_size);
	const BlockData* GetBlockData(int idx) const;

};