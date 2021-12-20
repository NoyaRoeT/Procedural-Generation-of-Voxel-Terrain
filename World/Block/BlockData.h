#pragma once
#include <array>
#include <vector>
class TextureAtlas;

enum BlockID {
	GRASS, DIRT, STONE, COUNT
};

struct BlockData
{
	BlockData(BlockID block, const TextureAtlas& atlas);

	std::vector<float> TopVertexAttribs;
	std::vector<float> RightVertexAttribs;
	std::vector<float> LeftVertexAttribs;
	std::vector<float> FrontVertexAttribs;
	std::vector<float> BackVertexAttribs;
	std::vector<float> BottomVertexAttribs;

	// Store subtexture coordinates for ea face in the order xmin ymin xmax ymax
	std::array<float, 4> TopTexCoords; 
	std::array<float, 4> SideTexCoords;
	std::array<float, 4> BottomTexCoords;

private:
	void GenerateVertexAttribVectors();
};

