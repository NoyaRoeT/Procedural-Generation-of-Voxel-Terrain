#include "BlockData.h"
#include "Texture/TextureAtlas.h"
#include <vector>


BlockData::BlockData(BlockID block, const TextureAtlas& atlas)
{
	if (block == BlockID::GRASS)
	{
		TopTexCoords = atlas.GetSubtexture(0, 0);
		SideTexCoords = atlas.GetSubtexture(0, 1);
		BottomTexCoords = atlas.GetSubtexture(0, 2);
	}
	else if (block == BlockID::DIRT)
	{
		TopTexCoords = atlas.GetSubtexture(0, 2);
		SideTexCoords = TopTexCoords;
		BottomTexCoords = SideTexCoords;
	}
	else if (block == BlockID::STONE)
	{
		TopTexCoords = atlas.GetSubtexture(2, 1);
		SideTexCoords = TopTexCoords;
		BottomTexCoords = TopTexCoords;
	}
}
