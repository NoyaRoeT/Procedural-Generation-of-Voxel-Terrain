#pragma once
#include <array>
class TextureAtlas;

enum BlockID {
	GRASS, DIRT, STONE, COUNT
};

struct BlockData
{
	BlockData(BlockID block, const TextureAtlas& atlas);

	// Store subtexture coordinates for ea face in the order xmin ymin xmax ymax
	std::array<float, 4> TopTexCoords; 
	std::array<float, 4> SideTexCoords;
	std::array<float, 4> BottomTexCoords;

};

