#pragma once
#include <array>



class TextureAtlas
{
public:
	TextureAtlas(const char* filepath, int texture_size);
	std::array<float, 4> GetSubtexture(int x, int  y) const;
	void Bind();


private:
	unsigned int m_ID;
	int m_Width;
	int m_Height;
	int m_SubtextSize;
	float XStep;
	float YStep;
};

