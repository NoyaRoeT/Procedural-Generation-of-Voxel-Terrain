#include "Texture.h"
#include "stb_image.h"
#include "glad/glad.h"
#include <iostream>

Texture::Texture(const char* filepath)
{
	int width, height, nrComponents;
	unsigned char* data = stbi_load(filepath, &width, &height, &nrComponents, 0);

	if (data)
	{
		GLenum format;
		if (nrComponents == 1) format = GL_RED;
		else if (nrComponents == 3) format = GL_RGB;
		else if (nrComponents == 4) format = GL_RGBA;

		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "TEXTURE::ERROR: Failed to load texture at path: " << filepath << std::endl;
		stbi_image_free(data);
	}
	
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_ID);
}
