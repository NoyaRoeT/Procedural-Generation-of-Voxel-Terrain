#include "TextureAtlas.h"
#include "stb_image.h"
#include "glad/glad.h"
#include <iostream>

TextureAtlas::TextureAtlas(const char* filepath, int texture_size): m_SubtextSize(texture_size)
{
	int nrComponents;
	unsigned char* data = stbi_load(filepath, &m_Width, &m_Height, &nrComponents, 0);

	if (data)
	{
		GLenum format;
		if (nrComponents == 1) format = GL_RED;
		else if (nrComponents == 3) format = GL_RGB;
		else if (nrComponents == 4) format = GL_RGBA;

		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);

		glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		stbi_image_free(data);
	}
	else
	{
		stbi_image_free(data);
	}

	XStep = texture_size / (float)m_Width;
	YStep = texture_size / (float)m_Height;
}

std::array<float, 4> TextureAtlas::GetSubtexture(int x, int y) const
{
	float ymax = 1 - YStep * y;
	float xmin = XStep * x;
	float xmax = xmin + XStep;
	float ymin = ymax - YStep;

	return { xmin, ymin, xmax, ymax };
}

void TextureAtlas::Bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_ID);
}