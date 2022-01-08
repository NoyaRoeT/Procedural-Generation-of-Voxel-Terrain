#include "BlockData.h"
#include "Texture/TextureAtlas.h"
#include <vector>




BlockData::BlockData(BlockType block, const TextureAtlas& atlas)
{
	std::array<float, 4> TopTexCoords;
	std::array<float, 4> SideTexCoords;
	std::array<float, 4> BottomTexCoords;

	if (block == BlockType::GRASS)
	{
		TopTexCoords = atlas.GetSubtexture(0, 0);
		SideTexCoords = atlas.GetSubtexture(0, 1);
		BottomTexCoords = atlas.GetSubtexture(0, 2);
		isOpaque = true;
	}
	else if (block == BlockType::DIRT)
	{
		TopTexCoords = atlas.GetSubtexture(0, 2);
		SideTexCoords = TopTexCoords;
		BottomTexCoords = SideTexCoords;
		isOpaque = true;
	}
	else if (block == BlockType::STONE)
	{
		TopTexCoords = atlas.GetSubtexture(2, 1);
		SideTexCoords = TopTexCoords;
		BottomTexCoords = TopTexCoords;
		isOpaque = true;
	}
	else if (block == BlockType::AIR)
	{
		isOpaque = false;
	}
	else if (block == BlockType::WOOD)
	{
		TopTexCoords = atlas.GetSubtexture(3, 1);
		SideTexCoords = TopTexCoords;
		BottomTexCoords = TopTexCoords;
		isOpaque = true;
	}

	if (block != BlockType::AIR)
	{
		// Reserve memory
		TopVertexAttribs.reserve(30);
		BottomVertexAttribs.reserve(30);
		FrontVertexAttribs.reserve(30);
		BackVertexAttribs.reserve(30);
		LeftVertexAttribs.reserve(30);
		RightVertexAttribs.reserve(30);

		FrontVertexAttribs = {
			0.0f, 0.0f, 0.0f, SideTexCoords[0], SideTexCoords[1],
			1.0f, 0.0f, 0.0f, SideTexCoords[2], SideTexCoords[1],
			1.0f, 1.0f, 0.0f, SideTexCoords[2], SideTexCoords[3],
			0.0f, 0.0f, 0.0f, SideTexCoords[0], SideTexCoords[1],
			1.0f, 1.0f, 0.0f, SideTexCoords[2], SideTexCoords[3],
			0.0f, 1.0f, 0.0f, SideTexCoords[0], SideTexCoords[3]
		};

		RightVertexAttribs = {
			1.0f, 0.0f, 0.0f, SideTexCoords[0], SideTexCoords[1],
			1.0f, 0.0f, -1.0f, SideTexCoords[2], SideTexCoords[1],
			1.0f, 1.0f, -1.0f, SideTexCoords[2], SideTexCoords[3],
			1.0f, 0.0f, 0.0f, SideTexCoords[0], SideTexCoords[1],
			1.0f, 1.0f, -1.0f, SideTexCoords[2], SideTexCoords[3],
			1.0f, 1.0f, 0.0f, SideTexCoords[0], SideTexCoords[3]
		};

		LeftVertexAttribs = {
			0.0f, 0.0f, -1.0f, SideTexCoords[0], SideTexCoords[1],
			0.0f, 0.0f, 0.0f, SideTexCoords[2], SideTexCoords[1],
			0.0f, 1.0f, 0.0f, SideTexCoords[2], SideTexCoords[3],
			0.0f, 0.0f, -1.0f, SideTexCoords[0], SideTexCoords[1],
			0.0f, 1.0f, 0.0f, SideTexCoords[2], SideTexCoords[3],
			0.0f, 1.0f, -1.0f, SideTexCoords[0], SideTexCoords[3]
		};

		BackVertexAttribs = {
			1.0f, 0.0f, -1.0f, SideTexCoords[0], SideTexCoords[1],
			0.0f, 0.0f, -1.0f, SideTexCoords[2], SideTexCoords[1],
			0.0f, 1.0f, -1.0f, SideTexCoords[2], SideTexCoords[3],
			1.0f, 0.0f, -1.0f, SideTexCoords[0], SideTexCoords[1],
			0.0f, 1.0f, -1.0f, SideTexCoords[2], SideTexCoords[3],
			1.0f, 1.0f, -1.0f, SideTexCoords[0], SideTexCoords[3]
		};

		BottomVertexAttribs = {
			0.0f, 0.0f, -1.0f, BottomTexCoords[0], BottomTexCoords[1],
			1.0f, 0.0f, -1.0f, BottomTexCoords[2], BottomTexCoords[1],
			1.0f, 0.0f, 0.0f, BottomTexCoords[2], BottomTexCoords[3],
			0.0f, 0.0f, -1.0f, BottomTexCoords[0], BottomTexCoords[1],
			1.0f, 0.0f, 0.0f, BottomTexCoords[2], BottomTexCoords[3],
			0.0f, 0.0f, 0.0f, BottomTexCoords[0], BottomTexCoords[3]
		};

		TopVertexAttribs = {
			0.0f, 1.0f, 0.0f, TopTexCoords[0], TopTexCoords[1],
			1.0f, 1.0f, 0.0f, TopTexCoords[2], TopTexCoords[1],
			1.0f, 1.0f, -1.0f, TopTexCoords[2], TopTexCoords[3],
			0.0f, 1.0f, 0.0f, TopTexCoords[0], TopTexCoords[1],
			1.0f, 1.0f, -1.0f, TopTexCoords[2], TopTexCoords[3],
			0.0f, 1.0f, -1.0f, TopTexCoords[0], TopTexCoords[3]
		};
	}

}
