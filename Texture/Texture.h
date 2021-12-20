#pragma once

class Texture
{
public:
	Texture(const char* filepath);
	void Bind();
	~Texture();

private:
	unsigned int m_ID;
};

