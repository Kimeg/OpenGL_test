#pragma once

class Texture 
{
public:
	unsigned int ID;

	Texture(const char* texturePath);
	Texture(std::vector<std::string> &cubemap);
	~Texture();
};
