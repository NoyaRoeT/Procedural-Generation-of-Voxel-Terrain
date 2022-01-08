#pragma once
#include <array>
#include <vector>
class TextureAtlas;

enum BlockType {
	AIR, GRASS, DIRT, WOOD, STONE, COUNT
};

struct BlockData
{
	BlockData(BlockType block, const TextureAtlas& atlas);

	std::vector<float> TopVertexAttribs;
	std::vector<float> RightVertexAttribs;
	std::vector<float> LeftVertexAttribs;
	std::vector<float> FrontVertexAttribs;
	std::vector<float> BackVertexAttribs;
	std::vector<float> BottomVertexAttribs;
	bool isOpaque;

};

