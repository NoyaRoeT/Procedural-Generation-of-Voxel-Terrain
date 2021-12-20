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

	GenerateVertexAttribVectors();
}

void BlockData::GenerateVertexAttribVectors()
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
